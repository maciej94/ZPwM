#include <Windows.h> //zawsze dolaczany do aplikacji windowsowej
#include "res.h"

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
        HWND hwndEditBox = GetDlgItem(hwndDlg, IDC_EDIT1); //pobranie uchwytu kontrolki idc_edit1
        int iTextLength = GetWindowTextLength(hwndEditBox); //pobranie dlugosci tekstu
        CHAR szText[500];
        GetWindowText(hwndEditBox, szText, iTextLength + 1);//pobranie tekstu
        HWND hwndButton = GetDlgItem(hwndDlg, IDC_BUTTON1); //pobranie uchwytu kontrolki idc_button1
        SetWindowText(hwndButton, szText); // przypisanie go do przycisku

        return TRUE;
      }
    case BN_CLICKED:
      switch (LOWORD(wParam))
      {
      case IDC_BUTTON1:
        MessageBox(hwndDlg, TEXT("Test"), TEXT("Klikniecie"), MB_OK);
        //zmiana tekstu na przycisku na tekst z editboxa
        HWND hwndEditBox = GetDlgItem(hwndDlg, IDC_EDIT1); //pobranie uchwytu kontrolki idc_edit1
        int iTextLength = GetWindowTextLength(hwndEditBox); //pobranie dlugosci tekstu
        CHAR szText[500];
        GetWindowText(hwndEditBox, szText, iTextLength + 1);//pobranie tekstu

        SetWindowText((HWND)lParam, szText); // przypisanie go do przycisku

        return TRUE;
      }
    }
    return FALSE;
  case WM_LBUTTONDOWN:
    CHAR szText[200];
    wsprintf(szText, "Kliknales myszka x = %d, y = %d", LOWORD(lParam), HIWORD(lParam));
    MessageBox(hwndDlg, szText, TEXT("Klikniecie"), MB_OK);
    return TRUE;
  case WM_CLOSE:
    DestroyWindow(hwndDlg); //zniszczenie okienka
    PostQuitMessage(0); //umieszczenie w petli komunikatow polecenia zakonczenia aplkkacji
    return TRUE;
  }
  return FALSE;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow) //dla aplikacji win zamiast main jest WinMain
{
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
