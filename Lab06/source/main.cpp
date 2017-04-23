#include <Windows.h> //zawsze dolaczany do aplikacji windowsowej
#include "res.h"
#include <time.h>

bool isGameOn = false;
bool isFirstPlayerTurn = true;
bool isTie = false;
int iLicznik = 0;
char iBoard[3][3] = { {2, 3, 4},
                     {5, 6, 7}, 
                     {8, 9, 10} };
bool isFieldOccupiedByFirstPlayer[3][3];
bool isFieldOccupiedBySecondPlayer[3][3];

HBITMAP hBitMapGameBoard;
HBITMAP hBitMapX;
HBITMAP hBitMapO;
HBITMAP hBitMapStart;
HBITMAP hBitMapReset;
HINSTANCE hInst;

LRESULT CALLBACK ButtonWndProc(
  HWND hwnd,
  UINT uMsg,
  WPARAM wParam,
  LPARAM lParam)
{
  switch (uMsg)
  {
  case WM_PAINT:
    //paint area
  {
	HDC hdc = GetDC(hwnd);
	HDC hdcBitmap = CreateCompatibleDC(hdc);
	SelectObject(hdcBitmap, hBitMapStart);
	BitBlt(hdc, 500, 200, 200, 100, hdcBitmap, 0, 0, SRCCOPY);
	DeleteDC(hdcBitmap);
	return 0;
  }
  default:
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
    //return CallWindowProc(wpOrgButtonProc, hwnd, uMsg, wParam, lParam);
  }
}

void DrawBoard(HDC hdc)
{
  HDC hDCBitmap = CreateCompatibleDC(hdc);
  SelectObject(hDCBitmap, hBitMapGameBoard);
  BitBlt(hdc, 0, 0, 500, 321, hDCBitmap, 0, 0, SRCCOPY);
  DeleteDC(hDCBitmap);
}

void DrawX(HDC hdc, int x, int y)
{
  HDC hDCBitmap = CreateCompatibleDC(hdc);
  SelectObject(hDCBitmap, hBitMapX);
  BitBlt(hdc, x, y, 100, 100, hDCBitmap, 0, 0, SRCCOPY);
  DeleteDC(hDCBitmap);
}

void DrawO(HDC hdc, int x, int y)
{
  HDC hDCBitmap = CreateCompatibleDC(hdc);
  SelectObject(hDCBitmap, hBitMapO);
  BitBlt(hdc, x, y, 100, 100, hDCBitmap, 0, 0, SRCCOPY);
  DeleteDC(hDCBitmap);
}

bool CheckWinningCondition(HWND hwndDlg)
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
            isGameOn = true;
            int a = 0;
            for (int i = 0; i < 3; i++)
              for (int j = 0; j < 3; j++)
                iBoard[i][j] = a++;
            iLicznik = 0;
            isTie = false;
            isFirstPlayerTurn = true;
            CheckRadioButton(hwndDlg, IDC_RADIO1, IDC_RADIO2, IDC_RADIO1);
            HWND hwndStatic1Box = GetDlgItem(hwndDlg, IDC_STATIC1); //pobranie uchwytu kontrolki idc_edit1
            CHAR szText[500];
            wsprintf(szText, "Gra siê rozpoczê³a.");
            SetWindowText(hwndStatic1Box, szText);
            //czyszczenie pol

            HWND hwndButton10 = GetDlgItem(hwndDlg, IDC_BUTTON10);
            wsprintf(szText, "STOP");
            SetWindowText(hwndButton10, szText);

            //Rysowanie siatki gry
            HDC hdc = GetDC(hwndDlg);
            DrawBoard(hdc);
            ReleaseDC(hwndDlg, hdc);

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
        HDC hdcBitmap = CreateCompatibleDC(hdc);
       
        int x = LOWORD(lParam), y = HIWORD(lParam);
        
        if ((x > 100 && x < 400) && (y > 0 && y < 300))
        {
          int filedX = ((x - 100) / 100), filedY = ((y - 0) / 100);
          if (isFieldOccupiedByFirstPlayer[filedX][filedY] == false
            && isFieldOccupiedBySecondPlayer[filedX][filedY] == false)
          {
            x = filedX * 100 + 100/2;
            y = filedY * 100 + 100/2;
            if (isFirstPlayerTurn == true)
            {
              DrawX(hdc, x +50, y - 50);
              isFieldOccupiedByFirstPlayer[filedX][filedY] = true;
              iBoard[filedX][filedY] = 'X';
              CheckRadioButton(hwndDlg, IDC_RADIO1, IDC_RADIO2, IDC_RADIO2);
              
              if (CheckWinningCondition(hwndDlg))
              {
                char szText[500];
                isGameOn = false;
                wsprintf(szText, "wygrywa X");
                TextOut(hdc, 400, 10, szText, strlen(szText));
                
                HWND hwndButton10 = GetDlgItem(hwndDlg, IDC_BUTTON10);
                wsprintf(szText, "START");
                SetWindowText(hwndButton10, szText);
                return TRUE;
              }
              if (isTie)
              {
                CHAR szText[500];
                isGameOn = false;
                wsprintf(szText, "remis");
                TextOut(hdc, 400, 10, szText, strlen(szText));
                
                HWND hwndButton10 = GetDlgItem(hwndDlg, IDC_BUTTON10);
                wsprintf(szText, "START");
                SetWindowText(hwndButton10, szText);
                return TRUE;
              }
            }
            else
            {
              DrawO(hdc, x+50 , y - 50);
              isFieldOccupiedBySecondPlayer[filedX][filedY] = true;
              iBoard[filedX][filedY] = 'O';
              CheckRadioButton(hwndDlg, IDC_RADIO1, IDC_RADIO2, IDC_RADIO1);

              if (CheckWinningCondition(hwndDlg))
              {
                char szText[500];
                isGameOn = false;
                wsprintf(szText, "wygrywa O");
                TextOut(hdc, 400, 10, szText, strlen(szText));
                
                HWND hwndButton10 = GetDlgItem(hwndDlg, IDC_BUTTON10);
                wsprintf(szText, "START");
                SetWindowText(hwndButton10, szText);
                return TRUE;
              }
              if (isTie)
              {
                char szText[500];
                isGameOn = false;
                wsprintf(szText, "remis");
                TextOut(hdc, 400, 10, szText, strlen(szText));
                
                HWND hwndButton10 = GetDlgItem(hwndDlg, IDC_BUTTON10);
                wsprintf(szText, "START");
                SetWindowText(hwndButton10, szText);
                return TRUE;
              }
            }
            ReleaseDC(hwndDlg, hdc);
            isFirstPlayerTurn = !isFirstPlayerTurn;
          }
        }
      }
      return TRUE;
    case WM_INITDIALOG:
    {
      hBitMapGameBoard = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP3));
		  hBitMapX = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP7));
		  hBitMapO = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP4));
		  hBitMapStart = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP6));
		  hBitMapReset = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP5));

		  HWND hwndButton = GetDlgItem(hwndDlg, IDC_BUTTON10); // sterowanie przycisku
		  WNDPROC wpOrgButtonProc = (WNDPROC)SetWindowLong(hwndButton, -4, (LONG)ButtonWndProc);
    }
      return TRUE;
    case WM_PAINT:
    {
      HDC hdc = GetDC(hwndDlg);
      BitBlt(hdc, 0, 0, 500, 321, GetDC(0), 0, 0, SRCCOPY);
      DrawBoard(hdc);

      for (int iFiledX = 0; iFiledX < 3; iFiledX++)
        for (int iFiledY = 0; iFiledY < 3; iFiledY++)
        {
          if (isFieldOccupiedByFirstPlayer[iFiledX][iFiledY] == true)
          {
            DrawX(hdc, iFiledX * 100 + 100, iFiledY * 100);
          }
          if (isFieldOccupiedBySecondPlayer[iFiledX][iFiledY] == true)
          {
            DrawO(hdc, iFiledX * 100 + 100, iFiledY * 100);
          }
        }
      ReleaseDC(hwndDlg, hdc);
      return DefWindowProc(hwndDlg,uMsg,wParam,lParam);
    }
    case WM_CLOSE:
      DestroyWindow(hwndDlg); //zniszczenie okienka
      PostQuitMessage(0); //umieszczenie w petli komunikatow polecenia zakonczenia aplkkacji
      DeleteObject(hBitMapGameBoard);
      DeleteObject(hBitMapO);
      DeleteObject(hBitMapX);
      DeleteObject(hBitMapStart);
      DeleteObject(hBitMapReset);
      return TRUE;
    }
    return FALSE;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow) //dla aplikacji win zamiast main jest WinMain
{
  hInst = hInstance;
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
