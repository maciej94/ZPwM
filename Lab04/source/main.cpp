#include <Windows.h> //zawsze dolaczany do aplikacji windowsowej
#include "res.h"

bool isGameOn = false;
bool isFirstPlayerTurn = true;

bool CheckWinningCondition()
{

}

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
      case IDC_BUTTON2:
      case IDC_BUTTON3:
      case IDC_BUTTON4:
      case IDC_BUTTON5:
      case IDC_BUTTON6:
      case IDC_BUTTON7:
      case IDC_BUTTON8:
      case IDC_BUTTON9:
        if(isGameOn==true)
      {
        //isFirstPlayerTurn
        HWND hwndButton = (HWND)lParam;
        if (GetWindowTextLength(hwndButton) == 0) 
        {
          CHAR szText[500];
          if (isFirstPlayerTurn == true)
          {
            wsprintf(szText, "X");
            CheckRadioButton(hwndDlg, IDC_RADIO1, IDC_RADIO2, IDC_RADIO2);
          }
          else
          {
            wsprintf(szText, "O");
            CheckRadioButton(hwndDlg, IDC_RADIO1, IDC_RADIO2, IDC_RADIO1);
          }
          SetWindowText(hwndButton, szText);
          isFirstPlayerTurn = !isFirstPlayerTurn;
          
        }
        return TRUE;
      }
        return TRUE;
      case IDC_BUTTON10:
        if (isGameOn == false)
        {
          isGameOn = true;
          CheckRadioButton(hwndDlg, IDC_RADIO1, IDC_RADIO2, IDC_RADIO1);
          HWND hwndStatic1Box = GetDlgItem(hwndDlg, IDC_STATIC1); //pobranie uchwytu kontrolki idc_edit1
          CHAR szText[500];
          wsprintf(szText, "Gra siê rozpoczê³a.");
          SetWindowText(hwndStatic1Box, szText);
          //czyszczenie pol
          for (int i = 0; i < 9; i++)
          {
            HWND hwndButton = GetDlgItem(hwndDlg, IDC_BUTTON1 + i); //pobranie uchwytu kontrolki idc_edit1
            wsprintf(szText, "");
            SetWindowText(hwndButton, szText);
          }
          HWND hwndButton10 = GetDlgItem(hwndDlg, IDC_BUTTON10);
          wsprintf(szText, "STOP");
          SetWindowText(hwndButton10, szText);
        }
        else
        {
          isGameOn = false;
          CHAR szText[500];
          HWND hwndStatic1Box = GetDlgItem(hwndDlg, IDC_STATIC1);
          wsprintf(szText, "Koniec gry.");
          SetWindowText(hwndStatic1Box, szText);
          HWND hwndButton10 = GetDlgItem(hwndDlg, IDC_BUTTON10);
          wsprintf(szText, "START");
          SetWindowText(hwndButton10, szText);
        }

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
