#include <Windows.h> //zawsze dolaczany do aplikacji windowsowej
#include "res.h"
#include <time.h>

int proba = 0;
int liczba = 0;

INT_PTR CALLBACK DialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  switch (uMsg)
  {
  case WM_COMMAND:
    switch (HIWORD(wParam))
    {
    case BN_CLICKED:
      switch (LOWORD(wParam))
      {
      case IDC_BUTTON1:
        HWND hwndEditBox = GetDlgItem(hwndDlg, IDC_EDIT1); //pobranie uchwytu kontrolki idc_edit1
        HWND hwndStatic1Box = GetDlgItem(hwndDlg, IDC_STATIC1); //pobranie uchwytu kontrolki idc_static1
        HWND hwndStatic2Box = GetDlgItem(hwndDlg, IDC_STATIC2); //pobranie uchwytu kontrolki idc_static2
        CHAR cStrzal[3];
        int iTextLength = GetWindowTextLength(hwndEditBox); //pobranie dlugosci tekstu
        if (iTextLength < 3 && iTextLength >= 0)
        {
          GetWindowText(hwndEditBox, cStrzal, iTextLength + 1);//pobranie tekstu
          CHAR szText[200];
          int iStrzal = atoi(cStrzal);
          if (iStrzal > 0 && iStrzal < 41)
          {
            if (liczba > iStrzal)
            {
              wsprintf(szText, "Za ma³a liczba.");
              SetWindowText(hwndStatic1Box, szText); // przypisanie go do statictext
              proba++;
              wsprintf(szText, "Liczba prób: %d", proba);
              SetWindowText(hwndStatic2Box, szText);
            }
            else if (liczba < iStrzal)
            {
              wsprintf(szText, "Za du¿a liczba");
              SetWindowText(hwndStatic1Box, szText); // przypisanie go do statictext
              proba++;
              wsprintf(szText, "Liczba prób: %d", proba);
              SetWindowText(hwndStatic2Box, szText);
            }
            else
            {
              wsprintf(szText, "Bingo!");
              SetWindowText(hwndStatic1Box, szText); // przypisanie go do statictext
              proba++;
              wsprintf(szText, "Liczba prób: %d", proba);
              SetWindowText(hwndStatic2Box, szText);
              wsprintf(szText, "Wygrana! Liczba prób: %d", proba);
              MessageBox(hwndDlg, szText, TEXT("Koniec gry"), MB_OK);
              DestroyWindow(hwndDlg); //zniszczenie okienka
              PostQuitMessage(0); //umieszczenie w petli komunikatow polecenia zakonczenia aplkkacji
              return TRUE;
            }
          }
          else MessageBox(hwndDlg, "Nieprawidlowe dane!", TEXT("B£¥D"), MB_OK);
          return TRUE;
        }
        else MessageBox(hwndDlg, "Nieprawidlowe dane!", TEXT("B£¥D"), MB_OK);
      }
    }
    return FALSE;
  case WM_CLOSE:
    DestroyWindow(hwndDlg); //zniszczenie okienka
    PostQuitMessage(0); //umieszczenie w petli komunikatow polecenia zakonczenia aplkkacji
    return TRUE;
  }
  return FALSE;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow) //dla aplikacji win zamiast main jest WinMain
{
  srand(time(NULL));
  int los = (rand() % 40) + 1;
  liczba = los;
  HWND hwndMainWindow = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_MAINVIEW), NULL, DialogProc);
  ShowWindow(hwndMainWindow, iCmdShow);

  MSG msg = {};
  while (GetMessage(&msg, NULL, 0, 0))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  return 0;
}


