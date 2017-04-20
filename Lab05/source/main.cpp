#include <Windows.h> //zawsze dolaczany do aplikacji windowsowej
#include "res.h"

bool isGameOn = false;
bool isFirstPlayerTurn = true;
bool isTie = false;
int iLicznik = 0, iMiejsce = 0;
char iBoard[3][3] = { {'0', '1', '2'},
                      {'3', '4', '5'},
                      {'6', '7', '8'} };
bool isFieldOccupiedByFirstPlayer[3][3];
bool isFieldOccupiedBySecondPlayer[3][3];

void DrawBoard(HDC hdc)
{
  MoveToEx(hdc, 60, 10, NULL);
  LineTo(hdc, 60, 160);

  MoveToEx(hdc, 110, 10, NULL);
  LineTo(hdc, 110, 160);

  MoveToEx(hdc, 10, 60, NULL);
  LineTo(hdc, 160, 60);

  MoveToEx(hdc, 10, 110, NULL);
  LineTo(hdc, 160, 110);
}

bool CheckWinningCondition()
{
  if (iBoard[0][0] == iBoard[0][1] && iBoard[0][1] == iBoard[0][2] ||
    iBoard[1][0] == iBoard[1][1] && iBoard[1][1] == iBoard[1][2] ||
    iBoard[2][0] == iBoard[2][1] && iBoard[2][1] == iBoard[2][2] ||
    iBoard[0][0] == iBoard[1][0] && iBoard[1][0] == iBoard[2][0] ||
    iBoard[0][1] == iBoard[1][1] && iBoard[1][1] == iBoard[2][1] ||
    iBoard[0][2] == iBoard[1][2] && iBoard[1][2] == iBoard[2][2] ||
    iBoard[0][0] == iBoard[1][1] && iBoard[1][1] == iBoard[2][2] ||
    iBoard[0][2] == iBoard[1][1] && iBoard[1][1] == iBoard[2][0]) return true;
  else
  {
    iLicznik++;
    if (iLicznik == 9) isTie = true;
    return false;
  }
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
        case IDC_BUTTON10:
          if (isGameOn == false)
          {
            int x = 0;
            isGameOn = true;
            for (int i = 0; i < 3; i++)
              for (int j = 0; j < 3; j++)
                iBoard[i][j] = x++;
            iLicznik = 0;
            isTie = false;
            isFirstPlayerTurn = true;
            CheckRadioButton(hwndDlg, IDC_RADIO1, IDC_RADIO2, IDC_RADIO1);
            HWND hwndStatic1Box = GetDlgItem(hwndDlg, IDC_STATIC1); //pobranie uchwytu kontrolki idc_edit1
            CHAR szText[500];
            wsprintf(szText, "Gra siê rozpoczê³a.");
            SetWindowText(hwndStatic1Box, szText);
            //czyszczenie pol
            HDC hdc = GetDC(hwndDlg);
            for (int i = 10; i < 160; i++)
              for (int j = 10; j < 160; j++)
                SetPixel(hdc, j, i, GetSysColor(COLOR_WINDOW));//RGB(128,128,128));
         
            HWND hwndButton10 = GetDlgItem(hwndDlg, IDC_BUTTON10);
            wsprintf(szText, "STOP");
            SetWindowText(hwndButton10, szText);
            
            DrawBoard(hdc);
    
            for(int i = 0; i < 3; i++)
              for (int j = 0; j < 3; j++)
              {
                isFieldOccupiedByFirstPlayer[i][j] = false;
                isFieldOccupiedBySecondPlayer[i][j] = false;
              }
          }
          else
          {
            isGameOn = false;
            CHAR szText[500];
            HWND hwndStatic1Box = GetDlgItem(hwndDlg, IDC_STATIC1);
            wsprintf(szText, "Koniec gry. Wcisnij START, zeby rozpoczac.");
            SetWindowText(hwndStatic1Box, szText);
            HWND hwndButton10 = GetDlgItem(hwndDlg, IDC_BUTTON10);
            wsprintf(szText, "START");
            SetWindowText(hwndButton10, szText);
          }
        }
      }
      return FALSE;
    case WM_LBUTTONDOWN:
      if (isGameOn == true)
      {
        HDC hdc = GetDC(hwndDlg);
        int x = LOWORD(lParam), y = HIWORD(lParam);
        int filedX = ((x - 10) / 50), filedY = ((y - 10) / 50);
        if ((x > 10 && x < 150) && (y > 10 && y < 150))
        {
          if (isFieldOccupiedByFirstPlayer[filedX][filedY] == false
            && isFieldOccupiedBySecondPlayer[filedX][filedY] == false)
          {
            x = filedX * 50 + 10;
            y = filedY * 50 + 10;
            if (isFirstPlayerTurn == true)
            {
              MoveToEx(hdc, x + 10, y + 10, NULL);
              LineTo(hdc, x + 40, y + 40);
              MoveToEx(hdc, x + 40, y + 10, NULL);
              LineTo(hdc, x + 10, y + 40);
              isFieldOccupiedByFirstPlayer[filedX][filedY] = true;
              iBoard[filedX][filedY] = 'X';
              CheckRadioButton(hwndDlg, IDC_RADIO1, IDC_RADIO2, IDC_RADIO2);
              if (CheckWinningCondition())
              {
                isGameOn = false;
                CHAR szText[500];
                HWND hwndStatic1Box = GetDlgItem(hwndDlg, IDC_STATIC1);
                wsprintf(szText, "wygrana X. Wcisnij START, zeby rozpoczac.");
                SetWindowText(hwndStatic1Box, szText);
                HWND hwndButton10 = GetDlgItem(hwndDlg, IDC_BUTTON10);
                wsprintf(szText, "START");
                SetWindowText(hwndButton10, szText);
              }
              else if(isTie)
              {
                isGameOn = false;
                CHAR szText[500];
                HWND hwndStatic1Box = GetDlgItem(hwndDlg, IDC_STATIC1);
                wsprintf(szText, "remis. Wcisnij START, zeby rozpoczac.");
                SetWindowText(hwndStatic1Box, szText);
                HWND hwndButton10 = GetDlgItem(hwndDlg, IDC_BUTTON10);
                wsprintf(szText, "START");
                SetWindowText(hwndButton10, szText);
              }
            }
            else
            {
              MoveToEx(hdc, x + 10, y + 10, NULL);
              LineTo(hdc, x + 10, y + 40);
              LineTo(hdc, x + 40, y + 40);
              LineTo(hdc, x + 40, y + 10);
              LineTo(hdc, x + 10, y + 10);
              isFieldOccupiedBySecondPlayer[filedX][filedY] = true;
              iBoard[filedX][filedY] = 'O';
              CheckRadioButton(hwndDlg, IDC_RADIO1, IDC_RADIO2, IDC_RADIO1);
              if (CheckWinningCondition())
              {
                isGameOn = false;
                CHAR szText[500];
                HWND hwndStatic1Box = GetDlgItem(hwndDlg, IDC_STATIC1);
                wsprintf(szText, "wygrana O. Wcisnij START, zeby rozpoczac.");
                SetWindowText(hwndStatic1Box, szText);
                HWND hwndButton10 = GetDlgItem(hwndDlg, IDC_BUTTON10);
                wsprintf(szText, "START");
                SetWindowText(hwndButton10, szText);
              }
              else if(isTie)
              {
                isGameOn = false;
                CHAR szText[500];
                HWND hwndStatic1Box = GetDlgItem(hwndDlg, IDC_STATIC1);
                wsprintf(szText, "remis. Wcisnij START, zeby rozpoczac.");
                SetWindowText(hwndStatic1Box, szText);
                HWND hwndButton10 = GetDlgItem(hwndDlg, IDC_BUTTON10);
                wsprintf(szText, "START");
                SetWindowText(hwndButton10, szText);
              }
            }
            ReleaseDC(hwndDlg, hdc);
            isFirstPlayerTurn = !isFirstPlayerTurn;
          }
        }
      }
      return TRUE;
    
    case WM_PAINT:
    {
      if (isGameOn)
      {
        HDC hdc = GetDC(hwndDlg);
        DrawBoard(hdc);
        for (int iFiledX = 0; iFiledX < 3; iFiledX++)
          for (int iFiledY = 0; iFiledY < 3; iFiledY++)
          {
            if (isFieldOccupiedByFirstPlayer[iFiledX][iFiledY] == true)
            {
              //DrawX(hdc, iFiledX, iFieldY);
            }
            if (isFieldOccupiedBySecondPlayer[iFiledX][iFiledY] == true)
            {
              //DrawO(hdc, iFiledX, iFiledY);
            }
          }
        ReleaseDC(hwndDlg, hdc);
      }
    return FALSE;
      }
    
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
