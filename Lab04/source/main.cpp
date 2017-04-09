#include <Windows.h> //zawsze dolaczany do aplikacji windowsowej
#include "res.h"
#include <time.h>

bool isGameOn = false;
bool isFirstPlayerTurn = true;
bool isTie = false;
bool bFirst = true;
int iLicznik = 0, iMiejsce = 0;
int iBoard[9] = {2, 3, 4, 5, 6, 7, 8, 9, 10};
int markSpaces = 0;
int winX = 0, winO = 0, ties = 0;

bool CheckWinningCompCondition()
{
  markSpaces++;
  if (iBoard[0] == iBoard[1] && iBoard[1] == iBoard[2] && iBoard[0] == iBoard[1] == iBoard[2] == 1||
    iBoard[3] == iBoard[4] && iBoard[4] == iBoard[5] && iBoard[3] == iBoard[4] == iBoard[5] == 1 ||
    iBoard[6] == iBoard[7] && iBoard[7] == iBoard[8] && iBoard[6] == iBoard[7] == iBoard[8] == 1 ||
    iBoard[0] == iBoard[3] && iBoard[3] == iBoard[6] && iBoard[0] == iBoard[3] == iBoard[6] == 1 ||
    iBoard[1] == iBoard[4] && iBoard[4] == iBoard[7] && iBoard[1] == iBoard[4] == iBoard[7] == 1 ||
    iBoard[2] == iBoard[5] && iBoard[5] == iBoard[8] && iBoard[2] == iBoard[5] == iBoard[8] == 1 ||
    iBoard[0] == iBoard[4] && iBoard[4] == iBoard[8] && iBoard[0] == iBoard[4] == iBoard[8] == 1 ||
    iBoard[2] == iBoard[4] && iBoard[4] == iBoard[6] && iBoard[2] == iBoard[4] == iBoard[6] == 1) return true;
  else
  {
    iLicznik++;
    if (iLicznik == 9) isTie = true;
    return false;
  }
}

bool CheckWinningCondition(HWND hwndDlg, HWND param, int znak)
{
  markSpaces++;
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

void vMoveComputer(HWND hwndDlg, int znak)
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

    for (int i = 0; i < 3; i++)
    {
      if (iBoard[i * 3] == 0 && iBoard[i * 3 + 1] == 0 && iBoard[i * 3 + 2] != 0 && iBoard[i * 3 + 2] != 1 ||
        iBoard[i * 3] == 1 && iBoard[i * 3 + 1] == 1 && iBoard[i * 3 + 2] != 0 && iBoard[i * 3 + 2] != 1)
      {
        if (i == 0)
        {
          if (GetWindowTextLength(hwndButton3) == 0)
          {
            CHAR szText[500];
            wsprintf(szText, "O");
            SetWindowText(hwndButton3, szText);
            iBoard[2] = 1;
          }
        }
        if (i == 1)
        {
          if (GetWindowTextLength(hwndButton6) == 0)
          {
            CHAR szText[500];
            wsprintf(szText, "O");
            SetWindowText(hwndButton6, szText);
            iBoard[5] = 1;
          }
        }
        if (i == 2)
        {
          if (GetWindowTextLength(hwndButton9) == 0)
          {
            CHAR szText[500];
            wsprintf(szText, "O");
            SetWindowText(hwndButton9, szText);
            iBoard[8] = 1;
          }
        }
        return;
      }

      if (iBoard[i * 3 + 1] == 0 && iBoard[i * 3 + 2] == 0 && iBoard[i * 3] != 0&& iBoard[i * 3] != 1 || 
        iBoard[i * 3 + 1] == 1 && iBoard[i * 3 + 2] == 1 && iBoard[i * 3] != 0 && iBoard[i * 3] != 1 )
      {
        if (i == 0)
        {
          if (GetWindowTextLength(hwndButton1) == 0)
          {
            CHAR szText[500];
            wsprintf(szText, "O");
            SetWindowText(hwndButton1, szText);
            iBoard[0] = 1;
          }
        }
        if (i == 1)
        {
          if (GetWindowTextLength(hwndButton4) == 0)
          {
            CHAR szText[500];
            wsprintf(szText, "O");
            SetWindowText(hwndButton4, szText);
            iBoard[3] = 1;
          }
        }
        if (i == 2)
        {
          if (GetWindowTextLength(hwndButton7) == 0)
          {
            CHAR szText[500];
            wsprintf(szText, "O");
            SetWindowText(hwndButton7, szText);
            iBoard[6] = 1;
          }
        }
        return;
      }

      if (iBoard[i * 3] == 0 && iBoard[i * 3 + 2] == 0 && iBoard[i * 3 + 1] != 0 && iBoard[i * 3 + 1] != 1 ||
        iBoard[i * 3] == 1 && iBoard[i * 3 + 2] == 1 && iBoard[i * 3 + 1] != 0 && iBoard[i * 3 + 1] != 1)
      {
        if (i == 0)
        {
          if (GetWindowTextLength(hwndButton2) == 0)
          {
            CHAR szText[500];
            wsprintf(szText, "O");
            SetWindowText(hwndButton2, szText); 
            iBoard[1] = 1;
          }
        }
        if (i == 1)
        {
          if (GetWindowTextLength(hwndButton5) == 0)
          {
            CHAR szText[500];
            wsprintf(szText, "O");
            SetWindowText(hwndButton5, szText);
            iBoard[4] = 1;
          }
        }
        if (i == 2)
        {
          if (GetWindowTextLength(hwndButton8) == 0)
          {
            CHAR szText[500];
            wsprintf(szText, "O");
            SetWindowText(hwndButton8, szText);
            iBoard[7] = 1;
          }
        }
        return;
      }

      if (iBoard[i] == 0 && iBoard[i + 3] == 0  && iBoard[i + 6] != 0 && iBoard[i + 6] != 1 ||
        iBoard[i] == 1 && iBoard[i + 3] == 1 && iBoard[i + 6] != 0&& iBoard[i + 6] != 1)
      {
        if (i == 0)
        {
          if (GetWindowTextLength(hwndButton7) == 0)
          {
            CHAR szText[500];
            wsprintf(szText, "O");
            SetWindowText(hwndButton7, szText);
            iBoard[6] = 1;
          }
        }
        if (i == 1)
        {
          if (GetWindowTextLength(hwndButton8) == 0)
          {
            CHAR szText[500];
            wsprintf(szText, "O");
            SetWindowText(hwndButton8, szText);
            iBoard[7] = 1;
          }
        }
        if (i == 2)
        {
          if (GetWindowTextLength(hwndButton9) == 0)
          {
            CHAR szText[500];
            wsprintf(szText, "O");
            SetWindowText(hwndButton9, szText);
            iBoard[8] = 1;
          }
        }
        return;
      }

      if (iBoard[i] == 0 && iBoard[i + 6] == 0 && iBoard[i + 3] != 0 && iBoard[i + 3] != 1 ||
        iBoard[i] == 1 && iBoard[i + 6] == 1 && iBoard[i + 3] != 0 && iBoard[i + 3] != 1)
      {
        if (i == 0)
        {
          if (GetWindowTextLength(hwndButton4) == 0)
          {
            CHAR szText[500];
            wsprintf(szText, "O");
            SetWindowText(hwndButton4, szText);
            iBoard[3] = 1;
          }
        }
        if (i == 1)
        {
          if (GetWindowTextLength(hwndButton5) == 0)
          {
            CHAR szText[500];
            wsprintf(szText, "O");
            SetWindowText(hwndButton5, szText);
            iBoard[4] = 1;
          }
        }
        if (i == 2)
        {
          if (GetWindowTextLength(hwndButton6) == 0)
          {
            CHAR szText[500];
            wsprintf(szText, "O");
            SetWindowText(hwndButton6, szText);
            iBoard[5] = 1;
          }
        }
        return;
      }

      if (iBoard[i + 3] == 0 && iBoard[i + 6] == 0 && iBoard[i] != 0 && iBoard[i] != 1 ||
        iBoard[i + 3] == 1 && iBoard[i + 6] == 1 && iBoard[i] != 0 && iBoard[i] != 1)
      {
        if (i == 0)
        {
          if (GetWindowTextLength(hwndButton1) == 0)
          {
            CHAR szText[500];
            wsprintf(szText, "O");
            SetWindowText(hwndButton1, szText);
            iBoard[0] = 1;
          }
        }
        if (i == 1)
        {
          if (GetWindowTextLength(hwndButton2) == 0)
          {
            CHAR szText[500];
            wsprintf(szText, "O");
            SetWindowText(hwndButton2, szText);
            iBoard[1] = 1;
          }
        }
        if (i == 2)
        {
          if (GetWindowTextLength(hwndButton3) == 0)
          {
            CHAR szText[500];
            wsprintf(szText, "O");
            SetWindowText(hwndButton3, szText);
            iBoard[2] = 1;
          }
        }
        return;
      }
    }

    if (iBoard[0] == 0 && iBoard[4] == 0 && iBoard[8] != 0 && iBoard[8] != 1 ||
      iBoard[0] == 1 && iBoard[4] == 1 && iBoard[8] != 0 && iBoard[8] != 1)
    {
      if (GetWindowTextLength(hwndButton9) == 0)
      {
        CHAR szText[500];
        wsprintf(szText, "O");
        SetWindowText(hwndButton9, szText);
        iBoard[8] = 1;
      }
      return;
    }

    if (iBoard[0] == 0 && iBoard[8] == 0 && iBoard[4] != 0&& iBoard[4] != 1 || 
      iBoard[0] == 1 && iBoard[8] == 1 && iBoard[4] != 0 && iBoard[4] != 1)
    {
      if (GetWindowTextLength(hwndButton5) == 0)
      {
        CHAR szText[500];
        wsprintf(szText, "O");
        SetWindowText(hwndButton5, szText);
        iBoard[4] = 1;
      }
      return;
    }

    if (iBoard[8] == 0 && iBoard[4] == 0 && iBoard[0] != 0 && iBoard[0] != 1 ||
      iBoard[8] == 1 && iBoard[4] == 1 && iBoard[0] != 0 && iBoard[0] != 1)
    {
      if (GetWindowTextLength(hwndButton1) == 0)
      {
        CHAR szText[500];
        wsprintf(szText, "O");
        SetWindowText(hwndButton1, szText);
        iBoard[0] = 1;
      }
      return;
    }

    if (iBoard[2] == 0 && iBoard[4] == 0 && iBoard[6] != 0 && iBoard[6] != 1 ||
      iBoard[2] == 1 && iBoard[4] == 1 && iBoard[6] != 0 && iBoard[6] != 1)
    {
      if (GetWindowTextLength(hwndButton7) == 0)
      {
        CHAR szText[500];
        wsprintf(szText, "O");
        SetWindowText(hwndButton7, szText);
        iBoard[6] = 1;
      }
      return;
    }

    if (iBoard[6] == 0 && iBoard[4] == 0 && iBoard[2] != 0 && iBoard[2] != 1 ||
      iBoard[6] == 1 && iBoard[4] == 1 && iBoard[2] != 0 && iBoard[2] != 1)
    {
      if (GetWindowTextLength(hwndButton3) == 0)
      {
        CHAR szText[500];
        wsprintf(szText, "O");
        SetWindowText(hwndButton3, szText);
        iBoard[2] = 1;
      }
      return;
    }

    if (iBoard[6] == 0 && iBoard[2] == 0 && iBoard[4] != 0 && iBoard[4] != 1 ||
      iBoard[6] == 1 && iBoard[2] == 1 && iBoard[4] != 0 && iBoard[4] != 1)
    {
      if (GetWindowTextLength(hwndButton5) == 0)
      {
        CHAR szText[500];
        wsprintf(szText, "O");
        SetWindowText(hwndButton5, szText);
        iBoard[4] = 1;
      }
      return;
    }

    CHAR szText[500];
    wsprintf(szText, "O");
    bool bIsOk = false;
    if (iBoard[4] != 0 && bFirst && (iBoard[0] == 0 || iBoard[2] == 0 || iBoard[6] == 0 || iBoard[8] == 0))
    {
      iBoard[4] = 1;
      SetWindowText(hwndButton5, szText);

      bFirst = false;
    }
    else
    {
      while(!bIsOk && markSpaces != 9)
      {
        iMiejsce = rand() % 9;
      
        if (iMiejsce == 0)
        {
          if (GetWindowTextLength(hwndButton1) == 0)
          {
            iBoard[iMiejsce] = 1;
            SetWindowText(hwndButton1, szText);
            bIsOk = true;
          }
        }

        if (iMiejsce == 1)
        {
          if (GetWindowTextLength(hwndButton2) == 0)
          {
            iBoard[iMiejsce] = 1;

            SetWindowText(hwndButton2, szText);
            bIsOk = true;
          }
        }
        if (iMiejsce == 2)
        {
          if (GetWindowTextLength(hwndButton3) == 0)
          {
            iBoard[iMiejsce] = 1;

            SetWindowText(hwndButton3, szText);
            bIsOk = true;
          }
        }
        if (iMiejsce == 3)
        {
          if (GetWindowTextLength(hwndButton4) == 0)
          {
            iBoard[iMiejsce] = 1;

            SetWindowText(hwndButton4, szText);
            bIsOk = true;
          }
        }
        if (iMiejsce == 4)
        {
          if (GetWindowTextLength(hwndButton5) == 0)
          {
            iBoard[iMiejsce] = 1;

            SetWindowText(hwndButton5, szText);
            bIsOk = true;
          }
        }
        if (iMiejsce == 5)
        {
          if (GetWindowTextLength(hwndButton6) == 0)
          {
            iBoard[iMiejsce] = 1;

            SetWindowText(hwndButton6, szText);
            bIsOk = true;
          }
        }
        if (iMiejsce == 6)
        {
          if (GetWindowTextLength(hwndButton7) == 0)
          {
            iBoard[iMiejsce] = 1;

            SetWindowText(hwndButton7, szText);
            bIsOk = true;
          }
        }
        if (iMiejsce == 7)
        {
          if (GetWindowTextLength(hwndButton8) == 0)
          {
            iBoard[iMiejsce] = 1;

            SetWindowText(hwndButton8, szText);
            bIsOk = true;
          }
        }
        if (iMiejsce == 8)
        {
          if (GetWindowTextLength(hwndButton9) == 0)
          {
            iBoard[iMiejsce] = 1;
            SetWindowText(hwndButton9, szText);
            bIsOk = true;
          }
        }
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
                  HWND hwndWinX = GetDlgItem(hwndDlg, IDC_STATIC5);
                  CHAR szText[500];
                  wsprintf(szText, "wygrana X. Koniec gry. Wcisnij START, zeby rozpoczac.");
                  SetWindowText(hwndStatic1Box, szText);

                  isGameOn = false; //przerwanie gry
                  winX++;
                  wsprintf(szText, "wygrane X: %d", winX);
                  SetWindowText(hwndWinX, szText);

                  HWND hwndButton10 = GetDlgItem(hwndDlg, IDC_BUTTON10);
                  wsprintf(szText, "START");
                  SetWindowText(hwndButton10, szText);
                }
                else if (isTie)
                {
                  HWND hwndStatic1Box = GetDlgItem(hwndDlg, IDC_STATIC1);
                  HWND hwndTies = GetDlgItem(hwndDlg, IDC_STATIC7);
                  CHAR szText[500];
                  wsprintf(szText, "remis. Koniec gry. Wcisnij START, zeby rozpoczac.");
                  SetWindowText(hwndStatic1Box, szText);

                  isGameOn = false; //przerwanie gry
                  ties++;
                  wsprintf(szText, "remisy: %d", ties);
                  SetWindowText(hwndTies, szText);

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
                  HWND hwndWinO = GetDlgItem(hwndDlg, IDC_STATIC6);
                  CHAR szText[500];
                  wsprintf(szText, "wygrana O. Koniec gry. Wcisnij START, zeby rozpoczac.");
                  SetWindowText(hwndStatic1Box, szText);

                  isGameOn = false; //przerwanie gry
                  winO++;
                  wsprintf(szText, "wygrane O: %d", winO);
                  SetWindowText(hwndWinO, szText);

                  HWND hwndButton10 = GetDlgItem(hwndDlg, IDC_BUTTON10);
                  wsprintf(szText, "START");
                  SetWindowText(hwndButton10, szText);
                }
                else if (isTie)
                {
                  HWND hwndStatic1Box = GetDlgItem(hwndDlg, IDC_STATIC1);
                  HWND hwndTies = GetDlgItem(hwndDlg, IDC_STATIC7);
                  CHAR szText[500];
                  wsprintf(szText, "remis. Koniec gry. Wcisnij START, zeby rozpoczac.");
                  SetWindowText(hwndStatic1Box, szText);

                  isGameOn = false; //przerwanie gry
                  ties++;
                  wsprintf(szText, "remisy: %d", ties);
                  SetWindowText(hwndTies, szText);

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
            bFirst = true;
            markSpaces = 0;
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
          return FALSE;
        case IDC_BUTTON12:
        {
          winO = winX = ties = 0;
          CHAR szText[500];
          HWND hwndWinX = GetDlgItem(hwndDlg, IDC_STATIC5);
          HWND hwndWinO = GetDlgItem(hwndDlg, IDC_STATIC6);
          HWND hwndTies = GetDlgItem(hwndDlg, IDC_STATIC7);
          wsprintf(szText, "wygrane X: 0");
          SetWindowText(hwndWinX, szText);
          wsprintf(szText, "wygrane O: 0");
          SetWindowText(hwndWinO, szText);
          wsprintf(szText, "remisy: 0");
          SetWindowText(hwndTies, szText);
        }
        return TRUE;
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
  
  else if (IsDlgButtonChecked(hwndDlg, IDC_RADIO3))
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
            CHAR szText[500];
            if (GetWindowTextLength(hwndButton) == 0)
            {
              wsprintf(szText, "X");
              CheckRadioButton(hwndDlg, IDC_RADIO1, IDC_RADIO2, IDC_RADIO2);
              SetWindowText(hwndButton, szText);

                if (CheckWinningCondition(hwndDlg, hwndButton, 0))
                {
                  HWND hwndStatic1Box = GetDlgItem(hwndDlg, IDC_STATIC1);
                  HWND hwndWinX = GetDlgItem(hwndDlg, IDC_STATIC5);
                  CHAR szText[500];
                  wsprintf(szText, "wygrana X. Koniec gry. Wcisnij START, zeby rozpoczac.");
                  SetWindowText(hwndStatic1Box, szText);

                  isGameOn = false; //przerwanie gry
                  winX++;
                  wsprintf(szText, "wygrane X: %d", winX);
                  SetWindowText(hwndWinX, szText);

                  HWND hwndButton10 = GetDlgItem(hwndDlg, IDC_BUTTON10);
                  wsprintf(szText, "START");
                  SetWindowText(hwndButton10, szText);
                  
                }
                else if (isTie)
                {
                  HWND hwndStatic1Box = GetDlgItem(hwndDlg, IDC_STATIC1);
                  HWND hwndTies = GetDlgItem(hwndDlg, IDC_STATIC7);
                  CHAR szText[500];
                  wsprintf(szText, "remis. Koniec gry. Wcisnij START, zeby rozpoczac.");
                  SetWindowText(hwndStatic1Box, szText);

                  isGameOn = false; //przerwanie gry
                  ties++;
                  wsprintf(szText, "remisy: %d", ties);
                  SetWindowText(hwndTies, szText);

                  HWND hwndButton10 = GetDlgItem(hwndDlg, IDC_BUTTON10);
                  wsprintf(szText, "START");
                  SetWindowText(hwndButton10, szText);
                }
             
              if(isGameOn) vMoveComputer(hwndDlg, 0);
              CheckRadioButton(hwndDlg, IDC_RADIO1, IDC_RADIO2, IDC_RADIO1);
                  if (CheckWinningCompCondition())
                  {
                    HWND hwndStatic1Box = GetDlgItem(hwndDlg, IDC_STATIC1);
                    HWND hwndWinO = GetDlgItem(hwndDlg, IDC_STATIC6);
                    CHAR szText[500];
                    wsprintf(szText, "wygrana O. Koniec gry. Wcisnij START, zeby rozpoczac.");
                    SetWindowText(hwndStatic1Box, szText);

                    isGameOn = false; //przerwanie gry
                    winO++;
                    wsprintf(szText, "wygrane O: %d", winO);
                    SetWindowText(hwndWinO, szText);

                    HWND hwndButton10 = GetDlgItem(hwndDlg, IDC_BUTTON10);
                    wsprintf(szText, "START");
                    SetWindowText(hwndButton10, szText);
                  }
                  else if (isTie)
                  {
                    HWND hwndStatic1Box = GetDlgItem(hwndDlg, IDC_STATIC1);
                    HWND hwndTies = GetDlgItem(hwndDlg, IDC_STATIC7);
                    CHAR szText[500];
                    wsprintf(szText, "remis. Koniec gry. Wcisnij START, zeby rozpoczac.");
                    SetWindowText(hwndStatic1Box, szText);

                    isGameOn = false; //przerwanie gry
                    //ties;
                    wsprintf(szText, "remisy: %d", ties);
                    SetWindowText(hwndTies, szText);

                    HWND hwndButton10 = GetDlgItem(hwndDlg, IDC_BUTTON10);
                    wsprintf(szText, "START");
                    SetWindowText(hwndButton10, szText);
                  }            
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
            isTie = false;
            bFirst = true;

            markSpaces = 0;
            
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
          return FALSE;
        case IDC_BUTTON12:
        {
          winO = winX = ties = 0;
          CHAR szText[500];
          HWND hwndWinX = GetDlgItem(hwndDlg, IDC_STATIC5);
          HWND hwndWinO = GetDlgItem(hwndDlg, IDC_STATIC6);
          HWND hwndTies = GetDlgItem(hwndDlg, IDC_STATIC7);
          wsprintf(szText, "wygrane X: 0");
          SetWindowText(hwndWinX, szText);
          wsprintf(szText, "wygrane O: 0");
          SetWindowText(hwndWinO, szText);
          wsprintf(szText, "remisy: 0");
          SetWindowText(hwndTies, szText);
        }
        return TRUE;
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
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow) //dla aplikacji win zamiast main jest WinMain
{
  HWND hwndMainWindow = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_MAINVIEW), NULL, DialogProc);
  ShowWindow(hwndMainWindow, iCmdShow);

  srand(time(NULL));

  MSG msg = {};
  while (GetMessage(&msg, NULL, 0, 0))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  return 0;
}
