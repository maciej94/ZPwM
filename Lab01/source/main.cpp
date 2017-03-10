#include <Windows.h> //zawsze dolaczany do aplikacji windowsowej

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow) //dla aplikacji win zamiast main jest WinMain
{
  int iRetKey = MessageBox(0, "Podoba Ci sie aplikacja?", "Aplikacja", MB_YESNO);

  if (iRetKey == IDYES)
  {
    MessageBox(0, "To wspaniale", "Aplikacja", MB_OK);
  }
  else
  {
    MessageBox(0, "Smutno", "Aplikacja", MB_OK | MB_ICONQUESTION);
  }
  return 0;
}
