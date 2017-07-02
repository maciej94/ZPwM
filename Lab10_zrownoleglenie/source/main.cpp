#include <Windows.h> //zawsze dolaczany do aplikacji windowsowej
#include "res.h"
#include <winuser.h>
#include <stdio.h>

#define ID_TIMER_REDRAW 10

//zad dom - Techniki SSE i AVX, przyspieszenie tego programu

using namespace std;

HANDLE hFile = 0;
BYTE* ImageBufferY = 0;
BYTE* ImageBufferU = 0;
BYTE* ImageBufferV = 0;

BYTE* ImageBufferRGBA = 0;

__int64 iStart, iEnd;

INT_PTR CALLBACK DialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  switch (uMsg)
  {
  /*case WM_COMMAND:
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
    return FALSE;*/
  case WM_INITDIALOG:
  {
    //fopen() - nieuzywac
    hFile = CreateFile("..\\claire.cif",// uchwyt do pliku
                       GENERIC_READ, // tryb dostepu do pliku
                       0,
                       (LPSECURITY_ATTRIBUTES)0, // bez specjalnych zabezpieczen
                       OPEN_EXISTING, // otwieranie istniejacego pliku
                       FILE_ATTRIBUTE_NORMAL, //sprawdza atrybuty pliku (czy ukryty itp)
                       (HANDLE)NULL); 
    //utworzenie zmiennej przetrzymujacej aktualne probki:
    ImageBufferY = (BYTE*)malloc(352 * 288); //zaalokowanie pamieci na probki luminancji
    ImageBufferU = (BYTE*)malloc(352 * 288/4); //zaalokowanie pamieci na probki chrominancji
    ImageBufferV = (BYTE*)malloc(352 * 288/4); //zaalokowanie pamieci na probki chrominancji

    ImageBufferRGBA = (BYTE*)malloc(352 * 288 * 4);
  }
  return FALSE;
  case WM_TIMER:
    switch(wParam)
    {
    case ID_TIMER_REDRAW:
      if (!hFile) break; // sprawdzenie czy plik zostal otwarty

      DWORD ret;
      ReadFile(hFile, ImageBufferY, 352 * 288, &ret, NULL); //odczytanie z pliku wszystkich probek lumy i chromy
      ReadFile(hFile, ImageBufferU, 352 * 288 / 4, &ret, NULL);
      ReadFile(hFile, ImageBufferV, 352 * 288 / 4, &ret, NULL);

      //konwersja z YUV na RGB
      int tmp_r = 256 * 1.40200;
      int tmp_g1 = 256 * -0.34414;
      int tmp_g2 = 256 * -0.71414;
      int tmp_b = 256 * 1.77200;
      
      //iStart = GetTickCount(); // funkcja pobierajaca czas systemowy do sprawdzenia ile wykonuje sie konwersja, dziala w milisekundach
      QueryPerformanceCounter((_LARGE_INTEGER*)&iStart); //funkcja liczaca cykle procesora, dokladniejsza funkcja liczaca czas
      /*for(int y = 0; y < 288; y++)
        for (int x = 0; x < 352; x++)
        {
          int yy = ImageBufferY[y * 352 + x];
          int uu = ImageBufferU[(y / 2) * (352 / 2) + (x / 2)] - 128;
          int vv = ImageBufferV[(y / 2) * (352 / 2) + (x / 2)] - 128;

          int r = ((256 * 1.40200) * vv + 256 * yy) / 256;
          int g = ((256 * -0.34414) * uu + (256 * -0.71414)* vv + 256 * yy) / 256;
          int b = ((256 * 1.77200) * uu + 256 * yy) / 256;

          ImageBufferRGBA[3 * ((287-y) * 352 + x) + 0] = b; // 0 1 2 to offset
          ImageBufferRGBA[3 * ((287-y) * 352 + x) + 1] = g;
          ImageBufferRGBA[3 * ((287-y) * 352 + x) + 2] = r;//(287-y) wpisywanie danych od konca do pierwszej linii, zeby obraz nie byl
        }                                               */    //odwrocony
      
      //zadanie domowe
      for (int y = 0; y < 288; y++)
        for (int x = 0; x < 352; x++)
        {
          int y_2 = (y / 2) * (352 / 2) + (x / 2);

          int yy = ImageBufferY[y * 352 + x];
          int uu = ImageBufferU[y_2] - 128;
          int vv = ImageBufferV[y_2] - 128;

          int yy_256 = yy * 256;
          int y_287 = 3 * ((287 - y) * 352 + x);

          /*int r = (tmp_r * vv + yy_256) / 256;
          int g = (tmp_g1 * uu + tmp_g2 * vv + yy_256) / 256;
          int b = (tmp_b * uu + yy_256) / 256;*/

          int r = (tmp_r * vv + yy_256) >> 8;
          int g = (tmp_g1 * uu + tmp_g2 * vv + yy_256) >> 8;
          int b = (tmp_b * uu + yy_256) >> 8;

          ImageBufferRGBA[y_287 + 0] = b; // 0 1 2 to offset
          ImageBufferRGBA[y_287 + 1] = g;
          ImageBufferRGBA[y_287 + 2] = r;//(287-y) wpisywanie danych od konca do pierwszej linii, zeby obraz nie byl
        }
      //koniec zadania domowego
      //iEnd = GetTickCount();//zakonczenie pomiaru czasu
      QueryPerformanceCounter((_LARGE_INTEGER*)&iEnd);

      RECT rc; //odmalowanie okienka - uniewaznienie zawartosci obecnej\go okienka
      GetClientRect(hwndDlg, &rc);
      InvalidateRect(hwndDlg, NULL, false);
      RedrawWindow(hwndDlg, &rc, NULL, RDW_ERASE);
      break;
    }
    return FALSE;
  case WM_PAINT:
  {
    HDC hDC = GetDC(hwndDlg);//pobranie kontekstu okienka
    HDC hdcMemDC = CreateCompatibleDC(hDC);
    HBITMAP hBmp = CreateCompatibleBitmap(hDC, 352, 288);

    SelectObject(hdcMemDC, hBmp);//wybranie bitmapy
    BITMAP bmp;
    GetObject(hBmp, sizeof(BITMAP), &bmp);

    BITMAPINFOHEADER bi;
    bi.biSize = sizeof(BITMAPINFOHEADER);
    bi.biWidth = 352;
    bi.biHeight = 288; // moze byc -288, wtedy obrazek nie bedzie do gory nogami
    bi.biPlanes = 1;
    bi.biBitCount = 24;
    bi.biCompression = BI_RGB;
    bi.biSizeImage = 352 * 288;
    bi.biXPelsPerMeter = 0;
    bi.biYPelsPerMeter = 0;
    bi.biClrUsed = 0;
    bi.biClrImportant = 0;

    SetDIBits(hdcMemDC, hBmp, 0, 288, ImageBufferRGBA, (BITMAPINFO*)&bi, DIB_RGB_COLORS);//przypisanie kolorow
    
    BitBlt(hDC, 0, 0, 352, 288, hdcMemDC, 0, 0, SRCCOPY);//wczytanie obrazka

    static int x = 0;
    char text[255];
    sprintf_s(text, "%d", iEnd - iStart);
    //TextOut(hDC, x, 10, "O_O", 3);
    TextOut(hDC, x, 10, text, strlen(text));
    x = x + 1;//przesuwanie o 1 punkt na 200 ms
    ReleaseDC(hwndDlg, hDC);
  }
  return FALSE;
  case WM_CLOSE:
    free(ImageBufferRGBA); //zwolnienie pamieci z buforow
    free(ImageBufferY); //zwolnienie pamieci z buforow
    free(ImageBufferU); //zwolnienie pamieci z buforow
    free(ImageBufferV); //zwolnienie pamieci z buforow
    CloseHandle(hFile); // zamkniecie pliku
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
  ShowWindow(hwndMainWindow, iCmdShow); \

  SetTimer(hwndMainWindow, ID_TIMER_REDRAW, 1, NULL);

  MSG msg = {};
  while (GetMessage(&msg, NULL, 0, 0))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  return 0;
}
