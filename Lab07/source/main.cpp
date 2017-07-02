#include <Windows.h> //zawsze dolaczany do aplikacji windowsowej
#include <gl\gl.h>
#include <gl\glu.h>
#include "res.h"

#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")


bool isGameOn = false;
bool isFirstPlayerTurn = true;
bool isTie = false;
int iLicznik = 0, iMiejsce = 0;
char iBoard[3][3] = { {'0', '1', '2'},
                      {'3', '4', '5'},
                      {'6', '7', '8'} };
bool isFieldOccupiedByFirstPlayer[3][3];
bool isFieldOccupiedBySecondPlayer[3][3];

HDC hDC = NULL; // kontekst
HGLRC hRC = NULL; // kontekst renderowania

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
    case WM_INITDIALOG:
      //podpiecie komunikatow opengl
      //!!WM_INITDIALOG!!
      //1.zmienic styl okienka
    {
      //zmiana stylu okienka na okienko z wlasnym kontekstem graficznym
      SetWindowLong(hwndDlg, GWL_STYLE, CS_HREDRAW | CS_VREDRAW | CS_OWNDC | WS_OVERLAPPEDWINDOW); 
      //2.stworzyc maszyne stanu
      static PIXELFORMATDESCRIPTOR pfd = {
        sizeof(PIXELFORMATDESCRIPTOR),
        1,
        PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
        PFD_TYPE_RGBA,
        16,
        0, 0, 0, 0, 0, 0,
        0,
        0,
        0,
        0, 0, 0, 0,
        16,
        0,
        0,
        PFD_MAIN_PLANE,
        0,
        0, 0, 0
      };
      //3.podpiac ja pod okienko
 
      GLuint PixelFormat;

      hDC = GetDC(hwndDlg);
      PixelFormat = ChoosePixelFormat(hDC, &pfd);
      SetPixelFormat(hDC, PixelFormat, &pfd);

      hRC = wglCreateContext(hDC);
      wglMakeCurrent(hDC, hRC);
    }
    case WM_SIZE:
      {
      GLint iWidth = LOWORD(lParam);
      GLint iHeight = HIWORD(lParam);

      glViewport(0, 0, iWidth, iHeight);

      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();

      //glLoadMatrix();
      if (iHeight == 0) iHeight = 1;
      gluPerspective(45.0f, iWidth / iHeight, 0.1f, 1000.0f);

      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
      }
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
    
   /* case WM_PAINT:
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
      }*/
    
    case WM_CLOSE:
      DestroyWindow(hwndDlg); //zniszczenie okienka
      PostQuitMessage(0); //umieszczenie w petli komunikatow polecenia zakonczenia aplkkacji
      return TRUE;
    }
    return FALSE;
  }


void DrawBlackCube(int a, int b, int c)
{
  glBegin(GL_QUADS);
  glColor3d(0, -1, 0);
  glNormal3d(0, -1, 0);
  glVertex3d(0, 0, 0);
  glVertex3d(0, 0, c);
  glVertex3d(a, 0, c);
  glVertex3d(a, 0, 0);

  glColor3d(0, 1, 0);
  glNormal3d(0, -1, 0);
  glVertex3d(a, 0, 0);
  glVertex3d(a, 0, c);
  glVertex3d(a, b, c);
  glVertex3d(a, b, 0);

  glColor3d(1, 0, 0);
  glNormal3d(0, 1, 0);
  glVertex3d(a, b, 0);
  glVertex3d(a, b, c);
  glVertex3d(0, b, c);
  glVertex3d(0, b, 0);

  glColor3d(0, 1, 1);
  glNormal3d(-1, 0, 0);
  glVertex3d(0, b, 0);
  glVertex3d(0, b, c);
  glVertex3d(0, 0, c);
  glVertex3d(0, 0, 0);

  /*glColor3d(0, 0, 0);
  glNormal3d(0, 0, 1);
  glVertex3d(0, 0, c);
  glVertex3d(0, b, c);
  glVertex3d(a, b, c);
  glVertex3d(a, 0, c);
  */
  glColor3d(1, 1, 0);
  glNormal3d(0, 0, -1);
  glVertex3d(0, 0, 0);
  glVertex3d(a, 0, 0);
  glVertex3d(a, b, 0);
  glVertex3d(0, b, 0);
  glEnd();
}

void DrawCube(int xmin, int xmax, int ymin, int ymax, int zmin, int zmax)
{
  glNormal3d(0, -1, 0);
  glVertex3d(xmin, ymin, zmin);
  glVertex3d(xmin, ymin, zmax);
  glVertex3d(xmax, ymin, zmax);
  glVertex3d(xmax, ymin, zmax);

  glNormal3d(0, -1, 0);
  glVertex3d(xmax, ymin, zmin);
  glVertex3d(xmax, ymin, zmax);
  glVertex3d(xmax, ymax, zmax);
  glVertex3d(xmin, ymax, zmin);

  glNormal3d(0, 1, 0);
  glVertex3d(xmax, ymax, zmin);
  glVertex3d(xmax, ymax, zmax);
  glVertex3d(xmin, ymax, zmax);
  glVertex3d(xmin, ymax, zmin);

  glNormal3d(-1, 0, 0);
  glVertex3d(xmin, ymax, zmin);
  glVertex3d(xmin, ymax, zmax);
  glVertex3d(xmin, ymin, zmax);
  glVertex3d(xmin, ymin, zmin);

  glNormal3d(0, 0, 1);
  glVertex3d(xmin, ymin, zmax);
  glVertex3d(xmin, ymax, zmax);
  glVertex3d(xmax, ymax, zmax);
  glVertex3d(xmax, ymin, zmax);

  glNormal3d(0, 0, -1);
  glVertex3d(xmin, ymin, zmin);
  glVertex3d(xmax, ymin, zmin);
  glVertex3d(xmax, ymax, zmin);
  glVertex3d(xmin, ymax, zmin);
}
void DrawSide(int xmin, int xmax, int ymin, int ymax, int zmin, int zmax, int r, int g, int b)
{
  glColor3d(r, g, b);

  glVertex3d(xmin, ymin, zmax);
  glVertex3d(xmax, ymax, zmax);
  glVertex3d(xmax, ymax, zmin);

  glVertex3d(xmax, ymax, zmin);
  glVertex3d(xmin, ymin, zmin);
  glVertex3d(xmin, ymin, zmax);

}

GLint DrawGLScene()
{
  glEnable(GL_DEPTH_TEST);
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glLoadIdentity();
  static GLfloat fAngle = 0.0;
  fAngle += 0.009f;
  glTranslatef(0, 0, -100);
  //glRotatef(fAngle, 0, 1, 0);

  return 1;
}

void glDrawBoard()
{
  glBegin(GL_QUADS);
  DrawCube(-30, 30, -15, -10, -5, 0);
  DrawCube(-30, 30, 10, 15, -5, 0);
  DrawCube(-15, -10, -30, 30, -5, 0);
  DrawCube(10, 15, -30, 30, -5, 0);
  glEnd();

}
void glDrawX()
{
  glBegin(GL_QUADS);
  DrawCube(-5, 5, -3, 2, -5, 0);
  DrawCube(-2, 2, -7, 6, -5, 0);
  glEnd();
  /*glBegin(GL_TRIANGLES);
 

  //front
  {
    glColor3d(1, 0, 1);
    glNormal3d(1, 0, 0);
    glVertex3d(a + 5, b + 5, c - 0);
    glVertex3d(a + 15, b + 5, c - 0);
    glVertex3d(a + 38, b + 41, c - 0);//

    glVertex3d(a + 38, b + 41, c - 0);
    glVertex3d(a + 28, b + 41, c - 0);
    glVertex3d(a + 5, b + 5, c - 0);//

    glVertex3d(a + 5, b + 41, c - 0);
    glVertex3d(a + 15, b + 41, c - 0);
    glVertex3d(a + 38, b + 5, c - 0);//

    glVertex3d(a + 38, b + 5, c - 0);
    glVertex3d(a + 28, b + 5, c - 0);
    glVertex3d(a + 5, b + 41, c - 0);
  }

  //ty³
  {
    glColor3d(1, 1, 0);
    glNormal3d(-1, 0, 0);
    glVertex3d(a + 5, b + 5, c - 10);
    glVertex3d(a + 15, b + 5, c - 10);
    glVertex3d(a + 38, b + 41, c - 10);//

    glVertex3d(a + 38, b + 41, c - 10);
    glVertex3d(a + 28, b + 41, c - 10);
    glVertex3d(a + 5, b + 5, c - 10);//

    glVertex3d(a + 5, b + 41, c - 10);
    glVertex3d(a + 15, b + 41, c - 10);
    glVertex3d(a + 38, b + 5, c - 10);//

    glVertex3d(a + 38, b + 5, c - 10);
    glVertex3d(a + 28, b + 5, c - 10);
    glVertex3d(a + 5, b + 41, c - 10);
  }

  //dó³
  {
    glColor3d(0, 0, 1);

    //lewy dol
    glNormal3d(0, -1, 0);
    glVertex3d(a + 5, b + 5, c - 0);
    glVertex3d(a + 15, b + 5, c - 0);
    glVertex3d(a + 5, b + 5, c - 10);

    glVertex3d(a + 15, b + 5, c - 10);
    glVertex3d(a + 5, b + 5, c - 10);
    glVertex3d(a + 15, b + 5, c - 0);

    //lewy gora
    glNormal3d(0, 1, 0);
    glVertex3d(a + 5, b + 41, c - 0);
    glVertex3d(a + 15, b + 41, c - 0);
    glVertex3d(a + 5, b + 41, c - 10);


    glVertex3d(a + 15, b + 41, c - 10);
    glVertex3d(a + 5, b + 41, c - 10);
    glVertex3d(a + 15, b + 41, c - 0);
  }
  //góra
  {
    glColor3d(0, 0, 1);

    //prawy dol
    glNormal3d(0, -1, 0);
    glVertex3d(a + 28, b + 5, c - 0);
    glVertex3d(a + 38, b + 5, c - 0);
    glVertex3d(a + 28, b + 5, c - 10);

    glVertex3d(a + 38, b + 5, c - 10);
    glVertex3d(a + 28, b + 5, c - 10);
    glVertex3d(a + 38, b + 5, c - 0);

    //prawy gora
    glNormal3d(0, 1, 0);
    glVertex3d(a + 28, b + 41, c - 0);
    glVertex3d(a + 38, b + 41, c - 0);
    glVertex3d(a + 28, b + 41, c - 10);


    glVertex3d(a + 38, b + 41, c - 10);
    glVertex3d(a + 28, b + 41, c - 10);
    glVertex3d(a + 38, b + 41, c - 0);
  }
  //boki
  {
    glColor3d(0, 1, 1);

    //1
    glNormal3d(-1, 1, 0);
    glVertex3d(a + 5, b + 5, c - 0);
    glVertex3d(a + 28, b + 41, c - 0);
    glVertex3d(a + 5, b + 5, c - 10);//

    glVertex3d(a + 28, b + 41, c - 0);
    glVertex3d(a + 28, b + 41, c - 10);
    glVertex3d(a + 5, b + 5, c - 10);//

                                     //2
    glNormal3d(1, -1, 0);
    glVertex3d(a + 15, b + 5, c - 0);
    glVertex3d(a + 38, b + 41, c - 0);
    glVertex3d(a + 15, b + 5, c - 10);//

    glVertex3d(a + 38, b + 41, c - 0);
    glVertex3d(a + 38, b + 41, c - 10);
    glVertex3d(a + 15, b + 5, c - 10);//

                                      //3
    glVertex3d(a + 5, b + 41, c - 0);
    glVertex3d(a + 28, b + 5, c - 0);
    glVertex3d(a + 5, b + 41, c - 10);//

    glVertex3d(a + 28, b + 5, c - 0);
    glVertex3d(a + 28, b + 5, c - 10);
    glVertex3d(a + 5, b + 41, c - 10);//

                                      //4
    glVertex3d(a + 15, b + 41, c - 0);
    glVertex3d(a + 38, b + 5, c - 0);
    glVertex3d(a + 15, b + 41, c - 10);//

    glVertex3d(a + 38, b + 5, c - 0);
    glVertex3d(a + 38, b + 5, c - 10);
    glVertex3d(a + 15, b + 41, c - 10);//


  }
  glEnd();*/
}

void glDrawO()
{
  glBegin(GL_QUADS);
  DrawCube(-27, -20, 3, 5, -5, 0);
  DrawCube(-27, -25, -8, 5, -5, 0);
  DrawCube(-27, -20, -8, -7, -5, 0);
  DrawCube(-20, -18, -8, 5, -5, 0);
  glEnd();
  /*//przód
  {
    glColor3d(1, 1, 0);

    //lewy
    glVertex3d(a + 5, b + 16, c + 0);
    glVertex3d(a + 16, b + 16, c + 0);
    glVertex3d(a + 5, b + 27, c + 0);//

    glVertex3d(a + 16, b + 27, c + 0);
    glVertex3d(a + 16, b + 16, c + 0);
    glVertex3d(a + 5, b + 27, c + 0);//

                                     //skos
    glVertex3d(a + 5, b + 27, c + 0);
    glVertex3d(a + 16, b + 27, c + 0);
    glVertex3d(a + 16, b + 38, c + 0);//

                                      //gora
    glVertex3d(a + 16, b + 27, c + 0);
    glVertex3d(a + 16, b + 38, c + 0);
    glVertex3d(a + 27, b + 27, c + 0);//

    glVertex3d(a + 16, b + 38, c + 0);
    glVertex3d(a + 27, b + 38, c + 0);
    glVertex3d(a + 27, b + 27, c + 0);//

                                      //skos
    glVertex3d(a + 27, b + 27, c + 0);
    glVertex3d(a + 27, b + 38, c + 0);
    glVertex3d(a + 38, b + 27, c + 0);//

                                      //prawy
    glVertex3d(a + 27, b + 16, c + 0);
    glVertex3d(a + 38, b + 16, c + 0);
    glVertex3d(a + 27, b + 27, c + 0);//

    glVertex3d(a + 38, b + 27, c + 0);
    glVertex3d(a + 38, b + 16, c + 0);
    glVertex3d(a + 27, b + 27, c + 0);//

                                      //skos
    glVertex3d(a + 27, b + 5, c + 0);
    glVertex3d(a + 27, b + 16, c + 0);
    glVertex3d(a + 38, b + 16, c + 0);//

                                      //dol
    glVertex3d(a + 16, b + 5, c + 0);
    glVertex3d(a + 16, b + 16, c + 0);
    glVertex3d(a + 27, b + 5, c + 0);//

    glVertex3d(a + 16, b + 16, c + 0);
    glVertex3d(a + 27, b + 16, c + 0);
    glVertex3d(a + 27, b + 5, c + 0);//

                                     //skos
    glVertex3d(a + 5, b + 16, c + 0);
    glVertex3d(a + 16, b + 16, c + 0);
    glVertex3d(a + 16, b + 5, c + 0);//
  }
  //ty³
  {
    glColor3d(0, 1, 1);

    //lewy
    glVertex3d(a + 5, b + 16, c - 10);
    glVertex3d(a + 16, b + 16, c - 10);
    glVertex3d(a + 5, b + 27, c - 10);//

    glVertex3d(a + 16, b + 27, c - 10);
    glVertex3d(a + 16, b + 16, c - 10);
    glVertex3d(a + 5, b + 27, c - 10);//

                                      //skos
    glVertex3d(a + 5, b + 27, c - 10);
    glVertex3d(a + 16, b + 27, c - 10);
    glVertex3d(a + 16, b + 38, c - 10);//

                                       //gora
    glVertex3d(a + 16, b + 27, c - 10);
    glVertex3d(a + 16, b + 38, c - 10);
    glVertex3d(a + 27, b + 27, c - 10);//

    glVertex3d(a + 16, b + 38, c - 10);
    glVertex3d(a + 27, b + 38, c - 10);
    glVertex3d(a + 27, b + 27, c - 10);//

                                       //skos
    glVertex3d(a + 27, b + 27, c - 10);
    glVertex3d(a + 27, b + 38, c - 10);
    glVertex3d(a + 38, b + 27, c - 10);//

                                       //prawy
    glVertex3d(a + 27, b + 16, c - 10);
    glVertex3d(a + 38, b + 16, c - 10);
    glVertex3d(a + 27, b + 27, c - 10);//

    glVertex3d(a + 38, b + 27, c - 10);
    glVertex3d(a + 38, b + 16, c - 10);
    glVertex3d(a + 27, b + 27, c - 10);//

                                       //skos
    glVertex3d(a + 27, b + 5, c - 10);
    glVertex3d(a + 27, b + 16, c - 10);
    glVertex3d(a + 38, b + 16, c - 10);//

                                       //dol
    glVertex3d(a + 16, b + 5, c - 10);
    glVertex3d(a + 16, b + 16, c - 10);
    glVertex3d(a + 27, b + 5, c - 10);//

    glVertex3d(a + 16, b + 16, c - 10);
    glVertex3d(a + 27, b + 16, c - 10);
    glVertex3d(a + 27, b + 5, c - 10);//

                                      //skos
    glVertex3d(a + 5, b + 16, c - 10);
    glVertex3d(a + 16, b + 16, c - 10);
    glVertex3d(a + 16, b + 5, c - 10);//
  }
  //boki
  {
    //lewy
    DrawSide(a + 5, a + 5, b + 16, b + 27, c - 10, c, 0, 1, 0);
    //skos
    DrawSide(a + 5, a + 16, b + 27, b + 38, c - 10, c, 0, 1, 0);
    //gora
    DrawSide(a + 16, a + 27, b + 38, b + 38, c - 10, c, 0, 1, 0);
    //skos
    DrawSide(a + 38, a + 27, b + 27, b + 38, c - 10, c, 0, 1, 0);
    //prawy
    DrawSide(a + 38, a + 38, b + 16, b + 27, c - 10, c, 0, 1, 0);
    //skos
    DrawSide(a + 27, a + 38, b + 5, b + 16, c - 10, c, 0, 1, 0);
    //dol
    DrawSide(a + 16, a + 27, b + 5, b + 5, c - 10, c, 0, 1, 0);
    //skos
    DrawSide(a + 5, a + 16, b + 16, b + 5, c - 10, c, 0, 1, 0);
    //srodek lewy
    DrawSide(a + 16, a + 16, b + 16, b + 27, c - 10, c, 0, 1, 0);
    //srodek góra
    DrawSide(a + 16, a + 27, b + 27, b + 27, c - 10, c, 0, 1, 0);
    //srodek prawy
    DrawSide(a + 27, a + 27, b + 16, b + 27, c - 10, c, 0, 1, 0);
    //srodek dol
    DrawSide(a + 16, a + 27, b + 16, b + 16, c - 10, c, 0, 1, 0);
  }*/
}
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow) //dla aplikacji win zamiast main jest WinMain
{
  HWND hwndMainWindow = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_MAINVIEW), NULL, DialogProc);
  ShowWindow(hwndMainWindow, iCmdShow);

  MSG msg = {};
  /*while (GetMessage(&msg, NULL, 0, 0))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }*/

  //dla opengl:
  BOOL bDone = false;
  while(!bDone)
  {
    if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) // pobranie wiadaomosci z kolejki wiadomosci
    {
      if (msg.message == WM_QUIT) bDone = true;
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
    else
    {
      glColor3d(1, 0, 0);
      DrawGLScene();
      glDrawBoard();
      glColor3d(0, 1, 0);
      glDrawX();
      glColor3d(0, 0, 1);
      glDrawO();
      SwapBuffers(hDC);
    }
  }
  return 0;
}


