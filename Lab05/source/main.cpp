#include <Windows.h> //zawsze dolaczany do aplikacji windowsowej
#include "res.h"
#include <time.h>

bool isGameOn = false;
bool isFirstPlayerTurn = true;
bool isTie = false;
int iLicznik = 0, iMiejsce = 0;
int iBoard[9] = { 2, 3, 4, 5, 6, 7, 8, 9, 10 };
int iDane[12] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
bool isFieldOccupiedByFirstPlayer[3][3];
bool isFieldOccupiedBySecondPlayer[3][3];

bool CheckWinningCondition(HWND hwndDlg, HWND param, int znak)
{
  HWND hwndButton1 = GetDlgItem(hwndDlg, IDC_BUTTON1);
  HWND hwndButton2 = GetDlgItem(hwndDlg, IDC_BUTTON2);
  HWND hwndButton3 = GetDlgItem(hwndDlg, IDC_BUTTON3);
  HWND hwndButton4 = GetDlgItem(hwndDlg, IDC_BUTTON4);
  HWND hwndButton5 = GetDlgItem(hwndDlg, IDC_BUTTON5);
  HWND hwndButton6 = GetDlgItem(hwndDlg, IDC_BUTTON6);
  HWND hwndButton7 = GetDlgItem(hwndDlg, IDC_BUTTON7);
  HWND hwndButton8 = GetDlgItem(hwndDlg, IDC_BUTTON8);
  HWND hwndButton9 = GetDlgItem(hwndDlg, IDC_BUTTON9);

  if (znak == 0)
  {
    if ((hwndButton1) == param) iBoard[0] = 0;
    if ((hwndButton2) == param) iBoard[1] = 0;
    if ((hwndButton3) == param) iBoard[2] = 0;
    if ((hwndButton4) == param) iBoard[3] = 0;
    if ((hwndButton5) == param) iBoard[4] = 0;
    if ((hwndButton6) == param) iBoard[5] = 0;
    if ((hwndButton7) == param) iBoard[6] = 0;
    if ((hwndButton8) == param) iBoard[7] = 0;
    if ((hwndButton9) == param) iBoard[8] = 0;
  }
  else
  {
    if ((hwndButton1) == param) iBoard[0] = 1;
    if ((hwndButton2) == param) iBoard[1] = 1;
    if ((hwndButton3) == param) iBoard[2] = 1;
    if ((hwndButton4) == param) iBoard[3] = 1;
    if ((hwndButton5) == param) iBoard[4] = 1;
    if ((hwndButton6) == param) iBoard[5] = 1;
    if ((hwndButton7) == param) iBoard[6] = 1;
    if ((hwndButton8) == param) iBoard[7] = 1;
    if ((hwndButton9) == param) iBoard[8] = 1;
  }

  if (iBoard[0] == iBoard[1] && iBoard[1] == iBoard[2] ||
    iBoard[3] == iBoard[4] && iBoard[4] == iBoard[5] ||
    iBoard[6] == iBoard[7] && iBoard[7] == iBoard[8] ||
    iBoard[0] == iBoard[3] && iBoard[3] == iBoard[6] ||
    iBoard[1] == iBoard[4] && iBoard[4] == iBoard[7] ||
    iBoard[2] == iBoard[5] && iBoard[5] == iBoard[8] ||
    iBoard[0] == iBoard[4] && iBoard[4] == iBoard[8] ||
    iBoard[2] == iBoard[4] && iBoard[4] == iBoard[6]) return true;
  else
  {
    iLicznik++;
    if (iLicznik == 9) isTie = true;
    return false;
  }
}

void vMoveComputer(HWND hwndDlg, HWND hwndButton, int znak)
{
  HWND hwndButton1 = GetDlgItem(hwndDlg, IDC_BUTTON1);
  HWND hwndButton2 = GetDlgItem(hwndDlg, IDC_BUTTON2);
  HWND hwndButton3 = GetDlgItem(hwndDlg, IDC_BUTTON3);
  HWND hwndButton4 = GetDlgItem(hwndDlg, IDC_BUTTON4);
  HWND hwndButton5 = GetDlgItem(hwndDlg, IDC_BUTTON5);
  HWND hwndButton6 = GetDlgItem(hwndDlg, IDC_BUTTON6);
  HWND hwndButton7 = GetDlgItem(hwndDlg, IDC_BUTTON7);
  HWND hwndButton8 = GetDlgItem(hwndDlg, IDC_BUTTON8);
  HWND hwndButton9 = GetDlgItem(hwndDlg, IDC_BUTTON9);

  if (znak == 0)
  {
    for (int i = 0; i < 3; i++)
    {
      if (iBoard[i * 3] == 0 && iBoard[i * 3 + 1] == 0 && iBoard[i * 3 + 2] != 0 
        && iBoard[i * 3 + 2] != 1 && iDane[0] == 0 ||
        iBoard[i * 3] == 1 && iBoard[i * 3 + 1] == 1 && iBoard[i * 3 + 2] != 0 
        && iBoard[i * 3 + 2] != 1 && iDane[0] == 0)
      {
        CHAR szText[500];
        wsprintf(szText, "O");
        SetWindowText(hwndButton3, szText);
        iDane[0] = 1;
        return;
      }
      if (iBoard[i * 3 + 1] == 0 && iBoard[i * 3 + 2] == 0 && iBoard[i * 3] != 0
        && iBoard[i * 3] != 1 && iDane[1] == 0
        || iBoard[i * 3 + 1] == 1 && iBoard[i * 3 + 2] == 1 && iDane[1] == 0 && iBoard[i * 3] != 0
        && iBoard[i * 3] != 1)
      {
        CHAR szText[500];
        wsprintf(szText, "O");
        SetWindowText(hwndButton1, szText);
        iDane[1] = 1;
        return;
      }
      if (iBoard[i * 3] == 0 && iBoard[i * 3 + 2] == 0 && iDane[2] == 0 && iBoard[i * 3 + 1] != 0
        && iBoard[i * 3 + 1] != 1 ||
        iBoard[i * 3] == 1 && iBoard[i * 3 + 2] == 1 && iDane[2] == 0 && iBoard[i * 3 + 1] != 0
        && iBoard[i * 3 + 1] != 1)
      {
        CHAR szText[500];
        wsprintf(szText, "O");
        SetWindowText(hwndButton2, szText);
        iDane[2] = 1;
        return;
      }
      if (iBoard[i] == 0 && iBoard[i + 3] == 0 && iDane[3] == 0 && iBoard[i + 6] != 0
        && iBoard[i + 6] != 1 ||
        iBoard[i] == 1 && iBoard[i + 3] == 1 && iDane[3] == 0 && iBoard[i + 6] != 0
        && iBoard[i + 6] != 1)
      {
        CHAR szText[500];
        wsprintf(szText, "O");
        SetWindowText(hwndButton7, szText);
        iDane[3] = 1;
        return;
      }
      if (iBoard[i] == 0 && iBoard[i + 6] == 0 && iDane[4] == 0 && iBoard[i + 3] != 0
        && iBoard[i + 3] != 1 ||
        iBoard[i] == 1 && iBoard[i + 6] == 1 && iDane[4] == 0 && iBoard[i + 3] != 0
        && iBoard[i + 3] != 1)
      {
        CHAR szText[500];
        wsprintf(szText, "O");
        SetWindowText(hwndButton4, szText);
        iDane[4] = 1;
        return;
      }
      if (iBoard[i + 3] == 0 && iBoard[i + 6] == 0 && iDane[5] == 0 && iBoard[i] != 0
        && iBoard[i] != 1 ||
        iBoard[i + 3] == 1 && iBoard[i + 6] == 1 && iDane[5] == 0 && iBoard[i] != 0
        && iBoard[i] != 1)
      {
        CHAR szText[500];
        wsprintf(szText, "O");
        SetWindowText(hwndButton1, szText);
        iDane[5] = 1;
        return;
      }
    }
    if (iBoard[0] == 0 && iBoard[4] == 0 && iDane[6] == 0 && iBoard[8] != 0
      && iBoard[8] != 1 ||
      iBoard[0] == 1 && iBoard[4] == 1 && iDane[6] == 0 && iBoard[8] != 0
      && iBoard[8] != 1)
    {
      CHAR szText[500];
      wsprintf(szText, "O");
      SetWindowText(hwndButton9, szText);
      iDane[6] = 1;
      return;
    }
    if (iBoard[0] == 0 && iBoard[8] == 0 && iDane[7] == 0 && iBoard[4] != 0
      && iBoard[4] != 1 ||
      iBoard[0] == 1 && iBoard[8] == 1 && iDane[7] == 0 && iBoard[4] != 0
      && iBoard[4] != 1)
    {
      CHAR szText[500];
      wsprintf(szText, "O");
      SetWindowText(hwndButton5, szText);
      iDane[7] = 1;
      return;
    }
    if (iBoard[8] == 0 && iBoard[4] == 0 && iDane[8] == 0 && iBoard[0] != 0
      && iBoard[0] != 1 ||
      iBoard[8] == 1 && iBoard[4] == 1 && iDane[8] == 0 && iBoard[0] != 0
      && iBoard[0] != 1)
    {
      CHAR szText[500];
      wsprintf(szText, "O");
      SetWindowText(hwndButton1, szText);
      iDane[8] = 1;
      return;
    }
    if (iBoard[2] == 0 && iBoard[4] == 0 && iDane[9] == 0 && iBoard[6] != 0
      && iBoard[6] != 1 ||
      iBoard[2] == 1 && iBoard[4] == 1 && iDane[9] == 0 && iBoard[6] != 0
      && iBoard[6] != 1)
    {
      CHAR szText[500];
      wsprintf(szText, "O");
      SetWindowText(hwndButton7, szText);
      iDane[9] = 1;
      return;
    }
    if (iBoard[6] == 0 && iBoard[4] == 0 && iDane[10] == 0 && iBoard[2] != 0
      && iBoard[2] != 1 ||
      iBoard[6] == 1 && iBoard[4] == 1 && iDane[10] == 0 && iBoard[2] != 0
      && iBoard[2] != 1)
    {
      CHAR szText[500];
      wsprintf(szText, "O");
      SetWindowText(hwndButton3, szText);
      iDane[10] = 1;
      return;
    }
    if (iBoard[6] == 0 && iBoard[2] == 0 && iDane[11] == 0 && iBoard[4] != 0
      && iBoard[4] != 1 ||
      iBoard[6] == 1 && iBoard[2] == 1 && iDane[11] == 0 && iBoard[4] != 0
      && iBoard[4] != 1)
    {
      CHAR szText[500];
      wsprintf(szText, "O");
      SetWindowText(hwndButton5, szText);
      iDane[11] = 1;
      return;
    }
    iMiejsce = rand() % 9;
    iBoard[iMiejsce] = 0;
  }

  else if(znak == 1)
  {
    for (int i = 0; i < 3; i++)
    {
      if (iBoard[i * 3] == 0 && iBoard[i * 3 + 1] == 0 && iBoard[i * 3 + 2] != 0
        && iBoard[i * 3 + 2] != 1 && iDane[0] == 0 ||
        iBoard[i * 3] == 1 && iBoard[i * 3 + 1] == 1 && iBoard[i * 3 + 2] != 0
        && iBoard[i * 3 + 2] != 1 && iDane[0] == 0)
      {
        CHAR szText[500];
        wsprintf(szText, "X");
        SetWindowText(hwndButton3, szText);
        iDane[0] = 1;
        return;
      }
      if (iBoard[i * 3 + 1] == 0 && iBoard[i * 3 + 2] == 0 && iBoard[i * 3] != 0
        && iBoard[i * 3] != 1 && iDane[1] == 0
        || iBoard[i * 3 + 1] == 1 && iBoard[i * 3 + 2] == 1 && iDane[1] == 0 && iBoard[i * 3] != 0
        && iBoard[i * 3] != 1)
      {
        CHAR szText[500];
        wsprintf(szText, "X");
        SetWindowText(hwndButton1, szText);
        iDane[1] = 1;
        return;
      }
      if (iBoard[i * 3] == 0 && iBoard[i * 3 + 2] == 0 && iDane[2] == 0 && iBoard[i * 3 + 1] != 0
        && iBoard[i * 3 + 1] != 1 ||
        iBoard[i * 3] == 1 && iBoard[i * 3 + 2] == 1 && iDane[2] == 0 && iBoard[i * 3 + 1] != 0
        && iBoard[i * 3 + 1] != 1)
      {
        CHAR szText[500];
        wsprintf(szText, "X");
        SetWindowText(hwndButton2, szText);
        iDane[2] = 1;
        return;
      }
      if (iBoard[i] == 0 && iBoard[i + 3] == 0 && iDane[3] == 0 && iBoard[i + 6] != 0
        && iBoard[i + 6] != 1 ||
        iBoard[i] == 1 && iBoard[i + 3] == 1 && iDane[3] == 0 && iBoard[i + 6] != 0
        && iBoard[i + 6] != 1)
      {
        CHAR szText[500];
        wsprintf(szText, "X");
        SetWindowText(hwndButton7, szText);
        iDane[3] = 1;
        return;
      }
      if (iBoard[i] == 0 && iBoard[i + 6] == 0 && iDane[4] == 0 && iBoard[i + 3] != 0
        && iBoard[i + 3] != 1 ||
        iBoard[i] == 1 && iBoard[i + 6] == 1 && iDane[4] == 0 && iBoard[i + 3] != 0
        && iBoard[i + 3] != 1)
      {
        CHAR szText[500];
        wsprintf(szText, "X");
        SetWindowText(hwndButton4, szText);
        iDane[4] = 1;
        return;
      }
      if (iBoard[i + 3] == 0 && iBoard[i + 6] == 0 && iDane[5] == 0 && iBoard[i] != 0
        && iBoard[i] != 1 ||
        iBoard[i + 3] == 1 && iBoard[i + 6] == 1 && iDane[5] == 0 && iBoard[i] != 0
        && iBoard[i] != 1)
      {
        CHAR szText[500];
        wsprintf(szText, "X");
        SetWindowText(hwndButton1, szText);
        iDane[5] = 1;
        return;
      }
    }
    if (iBoard[0] == 0 && iBoard[4] == 0 && iDane[6] == 0 && iBoard[8] != 0
      && iBoard[8] != 1 ||
      iBoard[0] == 1 && iBoard[4] == 1 && iDane[6] == 0 && iBoard[8] != 0
      && iBoard[8] != 1)
    {
      CHAR szText[500];
      wsprintf(szText, "X");
      SetWindowText(hwndButton9, szText);
      iDane[6] = 1;
      return;
    }
    if (iBoard[0] == 0 && iBoard[8] == 0 && iDane[7] == 0 && iBoard[4] != 0
      && iBoard[4] != 1 ||
      iBoard[0] == 1 && iBoard[8] == 1 && iDane[7] == 0 && iBoard[4] != 0
      && iBoard[4] != 1)
    {
      CHAR szText[500];
      wsprintf(szText, "X");
      SetWindowText(hwndButton5, szText);
      iDane[7] = 1;
      return;
    }
    if (iBoard[8] == 0 && iBoard[4] == 0 && iDane[8] == 0 && iBoard[0] != 0
      && iBoard[0] != 1 ||
      iBoard[8] == 1 && iBoard[4] == 1 && iDane[8] == 0 && iBoard[0] != 0
      && iBoard[0] != 1)
    {
      CHAR szText[500];
      wsprintf(szText, "X");
      SetWindowText(hwndButton1, szText);
      iDane[8] = 1;
      return;
    }
    if (iBoard[2] == 0 && iBoard[4] == 0 && iDane[9] == 0 && iBoard[6] != 0
      && iBoard[6] != 1 ||
      iBoard[2] == 1 && iBoard[4] == 1 && iDane[9] == 0 && iBoard[6] != 0
      && iBoard[6] != 1)
    {
      CHAR szText[500];
      wsprintf(szText, "X");
      SetWindowText(hwndButton7, szText);
      iDane[9] = 1;
      return;
    }
    if (iBoard[6] == 0 && iBoard[4] == 0 && iDane[10] == 0 && iBoard[2] != 0
      && iBoard[2] != 1 ||
      iBoard[6] == 1 && iBoard[4] == 1 && iDane[10] == 0 && iBoard[2] != 0
      && iBoard[2] != 1)
    {
      CHAR szText[500];
      wsprintf(szText, "X");
      SetWindowText(hwndButton3, szText);
      iDane[10] = 1;
      return;
    }
    if (iBoard[6] == 0 && iBoard[2] == 0 && iDane[11] == 0 && iBoard[4] != 0
      && iBoard[4] != 1 ||
      iBoard[6] == 1 && iBoard[2] == 1 && iDane[11] == 0 && iBoard[4] != 0
      && iBoard[4] != 1)
    {
      CHAR szText[500];
      wsprintf(szText, "X");
      SetWindowText(hwndButton5, szText);
      iDane[11] = 1;
      return;
    }

  }
}

INT_PTR CALLBACK DialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  
  if (IsDlgButtonChecked(hwndDlg, IDC_RADIO4))
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
          if (isGameOn == true)
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
                if (CheckWinningCondition(hwndDlg, hwndButton, 0))
                {
                  HWND hwndStatic1Box = GetDlgItem(hwndDlg, IDC_STATIC1);
                  CHAR szText[500];
                  wsprintf(szText, "wygrana X. Koniec gry. Wcisnij START, zeby rozpoczac.");
                  SetWindowText(hwndStatic1Box, szText);

                  isGameOn = false; //przerwanie gry

                  HWND hwndButton10 = GetDlgItem(hwndDlg, IDC_BUTTON10);
                  wsprintf(szText, "START");
                  SetWindowText(hwndButton10, szText);
                }
                else if (isTie)
                {
                  HWND hwndStatic1Box = GetDlgItem(hwndDlg, IDC_STATIC1);
                  CHAR szText[500];
                  wsprintf(szText, "remis. Koniec gry. Wcisnij START, zeby rozpoczac.");
                  SetWindowText(hwndStatic1Box, szText);

                  isGameOn = false; //przerwanie gry

                  HWND hwndButton10 = GetDlgItem(hwndDlg, IDC_BUTTON10);
                  wsprintf(szText, "START");
                  SetWindowText(hwndButton10, szText);
                }
              }
              else
              {
                wsprintf(szText, "O");
                CheckRadioButton(hwndDlg, IDC_RADIO1, IDC_RADIO2, IDC_RADIO1);
                if (CheckWinningCondition(hwndDlg, hwndButton, 1))
                {
                  HWND hwndStatic1Box = GetDlgItem(hwndDlg, IDC_STATIC1);
                  CHAR szText[500];
                  wsprintf(szText, "wygrana O. Koniec gry. Wcisnij START, zeby rozpoczac.");
                  SetWindowText(hwndStatic1Box, szText);

                  isGameOn = false; //przerwanie gry

                  HWND hwndButton10 = GetDlgItem(hwndDlg, IDC_BUTTON10);
                  wsprintf(szText, "START");
                  SetWindowText(hwndButton10, szText);
                }
                else if (isTie)
                {
                  HWND hwndStatic1Box = GetDlgItem(hwndDlg, IDC_STATIC1);
                  CHAR szText[500];
                  wsprintf(szText, "remis. Koniec gry. Wcisnij START, zeby rozpoczac.");
                  SetWindowText(hwndStatic1Box, szText);

                  isGameOn = false; //przerwanie gry

                  HWND hwndButton10 = GetDlgItem(hwndDlg, IDC_BUTTON10);
                  wsprintf(szText, "START");
                  SetWindowText(hwndButton10, szText);
                }
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
            for (int i = 2; i < 11; i++) iBoard[i - 2] = i;
            iLicznik = 0;
            isTie = false;
            isFirstPlayerTurn = true;
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

            //Rysowanie siatki gry
            HDC hdc = GetDC(hwndDlg);
            //LineTo, MoveToEx, Rectange, TextOut, GetPixel, SetPixel
            MoveToEx(hdc, 31, 1, NULL);
            LineTo(hdc, 31, 91);

            MoveToEx(hdc, 61, 1, NULL);
            LineTo(hdc, 61, 91);

            MoveToEx(hdc, 1, 30, NULL);
            LineTo(hdc, 91, 30);

            MoveToEx(hdc, 1, 60, NULL);
            LineTo(hdc, 91, 60);

            HPEN hMyPen = CreatePen(PS_SOLID, 2, RGB(255, 255, 0));
            SelectObject(hdc, hMyPen);
            MoveToEx(hdc, 10, 10, NULL);
            LineTo(hdc, 10, 100);
            //DeleteObject(hMyPen);

            TextOut(hdc, 0, 0, szText, strlen(szText));
            
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
        int filedX = ((x - 10) / 30), filedY = ((y - 10) / 30);
        if ((x > 10 && x < 110) && (y > 10 && y < 110))
        {
          if (isFieldOccupiedByFirstPlayer[filedX][filedY] == false
            && isFieldOccupiedBySecondPlayer[filedX][filedY] == false)
          {
            x = filedX * 30 + 15;
            y = filedY * 30 + 15;
            if (isFirstPlayerTurn == true)
            {
              MoveToEx(hdc, x - 10, y - 10, NULL);
              LineTo(hdc, x + 10, y + 10);
              MoveToEx(hdc, x - 10, y + 10, NULL);
              LineTo(hdc, x + 10, y - 10);
              isFieldOccupiedByFirstPlayer[filedX][filedY] = true;
            }
            else
            {
              MoveToEx(hdc, x - 10, y - 10, NULL);
              LineTo(hdc, x - 10, y + 10);
              LineTo(hdc, x - 10, y - 10);
              LineTo(hdc, x + 10, y - 10);
              LineTo(hdc, x + 10, y + 10);
              isFieldOccupiedBySecondPlayer[filedX][filedY] = true;
            }
            ReleaseDC(hwndDlg, hdc);
            isFirstPlayerTurn = !isFirstPlayerTurn;
          }
        }
      }
      return TRUE;
    case WM_PAINT:
      HDC hdc = GetDC(hwndDlg);
      //DrawBoard(hdc);

      for(int iFiledX = 0; iFiledX < 3; iFiledX++)
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
      return TRUE;
    case WM_CLOSE:
      DestroyWindow(hwndDlg); //zniszczenie okienka
      PostQuitMessage(0); //umieszczenie w petli komunikatow polecenia zakonczenia aplkkacji
      return TRUE;
    }
    return FALSE;
  }
  /*else
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
          if (isGameOn == true)
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
                if (CheckWinningCondition(hwndDlg, hwndButton, 0))
                {
                  HWND hwndStatic1Box = GetDlgItem(hwndDlg, IDC_STATIC1);
                  CHAR szText[500];
                  wsprintf(szText, "wygrana X. Koniec gry. Wcisnij START, zeby rozpoczac.");
                  SetWindowText(hwndStatic1Box, szText);

                  isGameOn = false; //przerwanie gry

                  HWND hwndButton10 = GetDlgItem(hwndDlg, IDC_BUTTON10);
                  wsprintf(szText, "START");
                  SetWindowText(hwndButton10, szText);
                }
                else if (isTie)
                {
                  HWND hwndStatic1Box = GetDlgItem(hwndDlg, IDC_STATIC1);
                  CHAR szText[500];
                  wsprintf(szText, "remis. Koniec gry. Wcisnij START, zeby rozpoczac.");
                  SetWindowText(hwndStatic1Box, szText);

                  isGameOn = false; //przerwanie gry

                  HWND hwndButton10 = GetDlgItem(hwndDlg, IDC_BUTTON10);
                  wsprintf(szText, "START");
                  SetWindowText(hwndButton10, szText);
                }
              }
              else
              {
                wsprintf(szText, "O");
                CheckRadioButton(hwndDlg, IDC_RADIO1, IDC_RADIO2, IDC_RADIO1);
                if (CheckWinningCondition(hwndDlg, hwndButton, 1))
                {
                  HWND hwndStatic1Box = GetDlgItem(hwndDlg, IDC_STATIC1);
                  CHAR szText[500];
                  wsprintf(szText, "wygrana O. Koniec gry. Wcisnij START, zeby rozpoczac.");
                  SetWindowText(hwndStatic1Box, szText);

                  isGameOn = false; //przerwanie gry

                  HWND hwndButton10 = GetDlgItem(hwndDlg, IDC_BUTTON10);
                  wsprintf(szText, "START");
                  SetWindowText(hwndButton10, szText);
                }
                else if (isTie)
                {
                  HWND hwndStatic1Box = GetDlgItem(hwndDlg, IDC_STATIC1);
                  CHAR szText[500];
                  wsprintf(szText, "remis. Koniec gry. Wcisnij START, zeby rozpoczac.");
                  SetWindowText(hwndStatic1Box, szText);

                  isGameOn = false; //przerwanie gry

                  HWND hwndButton10 = GetDlgItem(hwndDlg, IDC_BUTTON10);
                  wsprintf(szText, "START");
                  SetWindowText(hwndButton10, szText);
                }
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
            for (int i = 2; i < 11; i++) iBoard[i - 2] = i;
            iLicznik = 0;
            isFirstPlayerTurn = true;
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
            wsprintf(szText, "Koniec gry. Wcisnij START, zeby rozpoczac.");
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
  }*/
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow) //dla aplikacji win zamiast main jest WinMain
{
  HWND hwndMainWindow = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_MAINVIEW), NULL, DialogProc);
  ShowWindow(hwndMainWindow, iCmdShow);

//  srand(time(NULL));

  MSG msg = {};
  while (GetMessage(&msg, NULL, 0, 0))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  return 0;
}
