#include <Windows.h> //zawsze dolaczany do aplikacji windowsowej
#include "res.h"
#include <math.h>
#include <string>
#include <dsound.h>
#include <winuser.h>

#define PI 3.141592

#define fC 261.626
#define fD 277.183
#define fE 329.628
#define fF 349.228
#define fG 391.995
#define fA 444.000
#define fB 493.883
#define fH 523.234

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dsound.lib")

using namespace std;

//zad dom
string sNotes = "E E E C G E C G E B B B C G E C G E";
string sTime = "16 16 16 8 4 16 8 4 16 16 16 16 8 4 16 8 4 16";

int Note(BYTE* pBufferForAudio, int iStart, int iDuration, float fNote, float fDiv)
{
  int i;
  for(i = iStart; i < iStart+iDuration -100; i++)
  {
    float t = i / fDiv;
    pBufferForAudio[i] = (128 * sin(2 * PI * fNote * t) + 128
                        + 128*sin(2 * PI*fNote * 1.0/2.0 *t) + 128)/2; // dzielenie prez dwa, zeby nie przebic zakresu
  }
  for (; i < iStart + iDuration; i++)
  {
    float t = i / fDiv;
    pBufferForAudio[i] = 128;
  }
  return i;
}

int Echo(BYTE* pBufferForAudio, int iStart, int iDuration, int iDelay, float fAttenuate, int iDelay2, float fAttenuate2, int iDelay3, float fAttenuate3)
{
  BYTE* tmp = new BYTE[iDuration]; //tymczasowy bufor zawierajacy probki echa
  memcpy(tmp, pBufferForAudio, iDuration);

  for(int i = 0; i < iDuration; i++)
  {
    int iSample = 0, iSample2 = 0, iSample3 = 0;

    if (i - iDelay > 0) iSample = tmp[i - iDelay] - 128;
    if (i - iDelay2 > 0) iSample2 = tmp[i - iDelay2] - 128;
    if (i - iDelay3 > 0) iSample3 = tmp[i - iDelay3] - 128;

    pBufferForAudio[i] = ((tmp[i] - 128.0) + iSample*fAttenuate + iSample2*fAttenuate2 + iSample3*fAttenuate3) 
                          / (1.0 + fAttenuate + fAttenuate2 + fAttenuate3) + 128;
    //else pBufferForAudio[i] = tmp[i];
  }

  delete[] tmp;
  return 0;
}

INT_PTR CALLBACK DialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  switch (uMsg)
  {
  case WM_COMMAND:
    switch (HIWORD(wParam))
    {
    case EN_CHANGE:
      switch (LOWORD(wParam))
      {
      case IDC_EDIT1:
      {HWND hwndEditBox = GetDlgItem(hwndDlg, IDC_EDIT1); //pobranie uchwytu kontrolki idc_edit1
      return TRUE; }
      default: ;
      }
    case BN_CLICKED:
      switch (LOWORD(wParam))
      {
      case IDC_BUTTON1:
        return TRUE;
      default: ;
      }
    default: ;
    }
    return FALSE;
  case WM_CLOSE:
    DestroyWindow(hwndDlg); //zniszczenie okienka
    PostQuitMessage(0); //umieszczenie w petli komunikatow polecenia zakonczenia aplkkacji
    return TRUE;
  default: ;
  }
  return FALSE;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow) //dla aplikacji win zamiast main jest WinMain
{
  HWND hwndMainWindow = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_MAINVIEW), NULL, DialogProc);
  ShowWindow(hwndMainWindow, iCmdShow);

  WAVEFORMATEX pcmWaveFormat; // definicja formatu probek
  pcmWaveFormat.wFormatTag = WAVE_FORMAT_PCM;
  pcmWaveFormat.nChannels = 1;
  pcmWaveFormat.nSamplesPerSec = 44100L;
  pcmWaveFormat.wBitsPerSample = 8;
  pcmWaveFormat.nAvgBytesPerSec = pcmWaveFormat.nSamplesPerSec * pcmWaveFormat.wBitsPerSample / 8;
  pcmWaveFormat.nBlockAlign = 1;
  pcmWaveFormat.cbSize = 0; // koniec definicji
//!!! klasa directsound!!!
  IDirectSound8 *DS8 = NULL;
  DirectSoundCreate8(NULL, &DS8, NULL);
  if (DS8 == NULL) MessageBox(0, TEXT("Nie mozna utworzyc!"), TEXT("ERROR"), MB_OK); // jesli sie cos nie udalo

  if(DS8->SetCooperativeLevel(hwndMainWindow, DSSCL_NORMAL) != DS_OK) // ustawienie trybow wspolpracy
  {
    MessageBox(0, TEXT("Nie mozna ustawic trybu!"), TEXT("ERROR"), MB_OK);
    return 0;
  }

  MMRESULT mmResult = 0;
  HWAVEOUT hwo = nullptr;

  /*for (UINT devId = 0; devId < waveOutGetNumDevs(); devId++) //petla po zainstalowanych kartach dzwiekowych i sprawdzenie 
  {// ktore moze obsluzyc nasz format
    mmResult = waveOutOpen(&hwo, devId, &pcmWaveFormat, 0, 0, CALLBACK_NULL);
    if (mmResult == MMSYSERR_NOERROR) break;
  }*/ // wykomentowane dla directsound

  /*if (mmResult != MMSYSERR_NOERROR) // gdy sei nie udalo
  {
    MessageBox(hwndMainWindow, TEXT("Nie znaleziono karty!"), TEXT("Error"), MB_OK);
    return mmResult;
  }*/ // wykomentowane dla directsound

  BYTE* pBufferForAudio = new BYTE[8 * pcmWaveFormat.nAvgBytesPerSec]; // rozmiar -> sredenia ilosc bitow na sek razy ilosc sekund dzwieku

  //float f = 440;
  int i = 0;
  
  float S = pcmWaveFormat.nAvgBytesPerSec;
  //int i = 0;
  /*for(int j = 0; j < sNotes.length() - 2; j = j+2)
  {
    i = Note(pBufferForAudio, i, 0.5*S, sNotes[j], pcmWaveFormat.nSamplesPerSec);
  }*/
  i = Note(pBufferForAudio, i, 0.5*S, fE, pcmWaveFormat.nSamplesPerSec);
  i = Note(pBufferForAudio, i, 0.5*S, fE, pcmWaveFormat.nSamplesPerSec);
  i = Note(pBufferForAudio, i, 0.5*S, fE, pcmWaveFormat.nSamplesPerSec);
  i = Note(pBufferForAudio, i, 0.25*S, fC, pcmWaveFormat.nSamplesPerSec);
  i = Note(pBufferForAudio, i, 0.125*S, fG, pcmWaveFormat.nSamplesPerSec);
  i = Note(pBufferForAudio, i, 0.5*S, fE, pcmWaveFormat.nSamplesPerSec);
  i = Note(pBufferForAudio, i, 0.25*S, fC, pcmWaveFormat.nSamplesPerSec);
  i = Note(pBufferForAudio, i, 0.125*S, fG, pcmWaveFormat.nSamplesPerSec);
  i = Note(pBufferForAudio, i, 0.5*S, fE, pcmWaveFormat.nSamplesPerSec);
  i = Note(pBufferForAudio, i, 0.5*S, fB, pcmWaveFormat.nSamplesPerSec);
  i = Note(pBufferForAudio, i, 0.5*S, fB, pcmWaveFormat.nSamplesPerSec);
  i = Note(pBufferForAudio, i, 0.5*S, fB, pcmWaveFormat.nSamplesPerSec);
  i = Note(pBufferForAudio, i, 0.25*S, fC, pcmWaveFormat.nSamplesPerSec);
  i = Note(pBufferForAudio, i, 0.125*S, fG, pcmWaveFormat.nSamplesPerSec);
  i = Note(pBufferForAudio, i, 0.5*S, fE, pcmWaveFormat.nSamplesPerSec);
  i = Note(pBufferForAudio, i, 0.25*S, fC, pcmWaveFormat.nSamplesPerSec);
  i = Note(pBufferForAudio, i, 0.5*S, fE, pcmWaveFormat.nSamplesPerSec);
  
  
  /*
  for (; i < 0.5 * pcmWaveFormat.nAvgBytesPerSec; i++)
  {
    float t = i / static_cast<float>(pcmWaveFormat.nAvgBytesPerSec);
    float f = fC;  
    pBufferForAudio[i] = 128 * sin(2 * PI * f * t) + 128;
  }

  for (; i < 1.0 * pcmWaveFormat.nAvgBytesPerSec; i++)
  {
    float t = i / static_cast<float>(pcmWaveFormat.nAvgBytesPerSec);
    float f = fD;
    pBufferForAudio[i] = 128 * sin(2 * PI * f * t) + 128;
  }

  for (; i < 1.5 * pcmWaveFormat.nAvgBytesPerSec; i++)
  {
    float t = i / static_cast<float>(pcmWaveFormat.nAvgBytesPerSec);
    float f = fE;
    pBufferForAudio[i] = 128 * sin(2 * PI * f * t) + 128;
  }

  for (; i < 2.0 * pcmWaveFormat.nAvgBytesPerSec; i++)
  {
    float t = i / static_cast<float>(pcmWaveFormat.nAvgBytesPerSec);
    float f = fF;
    pBufferForAudio[i] = 128 * sin(2 * PI * f * t) + 128;
  }
  for (; i < 2.5 * pcmWaveFormat.nAvgBytesPerSec; i++)
  {
    float t = i / static_cast<float>(pcmWaveFormat.nAvgBytesPerSec);
    float f = fG;
    pBufferForAudio[i] = 128 * sin(2 * PI * f * t) + 128;
  }
  for (; i < 3.0 * pcmWaveFormat.nAvgBytesPerSec; i++)
  {
    float t = i / static_cast<float>(pcmWaveFormat.nAvgBytesPerSec);
    float f = fA;
    pBufferForAudio[i] = 128 * sin(2 * PI * f * t) + 128;
  }
  for (; i < 3.5 * pcmWaveFormat.nAvgBytesPerSec; i++)
  {
    float t = i / static_cast<float>(pcmWaveFormat.nAvgBytesPerSec);
    float f = fB;
    pBufferForAudio[i] = 128 * sin(2 * PI * f * t) + 128;
  }
  for (; i < 4.0 * pcmWaveFormat.nAvgBytesPerSec; i++)
  {
    float t = i / static_cast<float>(pcmWaveFormat.nAvgBytesPerSec);
    float f = fH;
    pBufferForAudio[i] = 128 * sin(2 * PI * f * t) + 128;
  }*/
  WAVEHDR whdr; // naglowek dzwieku
  ZeroMemory(&whdr, sizeof(WAVEHDR));
  whdr.lpData = reinterpret_cast<LPSTR>(pBufferForAudio);
  whdr.dwBufferLength = 8 * pcmWaveFormat.nAvgBytesPerSec;

//!!!stworzenie bufora directsound!!!
  IDirectSoundBuffer *DSB;
  DSBUFFERDESC DSBD;
  memset(&DSBD, 0, sizeof(DSBUFFERDESC));
  DSBD.dwSize = sizeof(DSBUFFERDESC);
  DSBD.dwFlags = // lista elementow ktore mozna kontrolowac
                DSBCAPS_CTRLPAN //proporcja miedzy lewym a prawym kanalem
                | DSBCAPS_CTRLVOLUME //ustawienie glosnosci
                | DSBCAPS_CTRLFREQUENCY; //ustawienie czestotliwosci
  DSBD.dwBufferBytes = whdr.dwBufferLength;
  DSBD.lpwfxFormat = &pcmWaveFormat;

  if (DS8->CreateSoundBuffer(&DSBD, &DSB, NULL) != DS_OK)
  {
    MessageBox(0, TEXT("Nie mozna stworzyc bufora!"), TEXT("ERROR"), MB_OK);
    return 0;
  }

 /* mmResult = waveOutPrepareHeader(hwo, &whdr, sizeof(WAVEHDR));
  mmResult = waveOutWrite(hwo, &whdr, sizeof(WAVEHDR));

  while ((whdr.dwFlags & WHDR_DONE) != WHDR_DONE) Sleep(100); // czekanie

  mmResult = waveOutUnprepareHeader(hwo, &whdr, sizeof(WAVEHDR));*/ // wykomentowane dla directsound

//!!! odtwarzanie directsound!!!
  DSB->SetVolume(0xFFFF);
  void *ptr1, *ptr2;
  DWORD l1, l2;

  DSB->Lock(0, // zablokowanie pamieci dla bufora od miejsca 0
    whdr.dwBufferLength, //do konca bufora
    &ptr1, 
    &l1, 
    &ptr2, 
    &l2, 
    DSBLOCK_ENTIREBUFFER); //zablokowanie dla calego bufora, nie dla czesci
  //przekopiowanie buforow
  if (ptr1) memcpy(ptr1, pBufferForAudio, l1);
  if (ptr2) memcpy(ptr2, pBufferForAudio + l1, l2);
  DSB->Unlock(ptr1, l1, ptr2, l2);
  // zeby odtworzyc kolejny dzwiek trzeba jeszcze raz zaladowac do bufora, czyli wszystko miedzy DSC->Lock i DSB->Unlock
  Echo(pBufferForAudio, 0, whdr.dwBufferLength, 44000/3, 0.5, 44000/2, 0.4, 44000, 0.3);
  DSB->Play(0, 0, 0);

  MSG msg = {};
  while (GetMessage(&msg, NULL, 0, 0))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  /*float f = 640;

  for (int i = 0; i < 1 * pcmWaveFormat.nAvgBytesPerSec; i++)
  {
    float t = i / static_cast<float>(pcmWaveFormat.nAvgBytesPerSec);
    pBufferForAudio[i] = 128 * sin(2 * PI * f * t) + 128;
  }

  ZeroMemory(&whdr, sizeof(WAVEHDR));
  whdr.lpData = reinterpret_cast<LPSTR>(pBufferForAudio);
  whdr.dwBufferLength = 1 * pcmWaveFormat.nAvgBytesPerSec;

  mmResult = waveOutPrepareHeader(hwo, &whdr, sizeof(WAVEHDR));
  mmResult = waveOutWrite(hwo, &whdr, sizeof(WAVEHDR));

  while ((whdr.dwFlags & WHDR_DONE) != WHDR_DONE) Sleep(100); // czekanie

  mmResult = waveOutUnprepareHeader(hwo, &whdr, sizeof(WAVEHDR));*/

  //mmResult = waveOutClose(hwo);
  DS8->Release();
  delete[] pBufferForAudio;

  return 0;
}
