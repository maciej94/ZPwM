#include <Windows.h> //zawsze dolaczany do aplikacji windowsowej

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow) //dla aplikacji win zamiast main jest WinMain
{
  int iRetKey = MessageBox(0, "Wybierz liczbe z zakresu 1-40.", "Gra", MB_OK);

  if (iRetKey == IDOK)
  {
    iRetKey = MessageBox(0, "Czy liczba jest wieksza od 20?", "Gra", MB_YESNO);
    if (iRetKey == IDYES)
    {
      iRetKey = MessageBox(0, "Czy liczba jest wieksza od 30?", "Gra", MB_YESNO);
      if (iRetKey == IDYES)
      {
        iRetKey = MessageBox(0, "Czy liczba jest wieksza od 35?", "Gra", MB_YESNO);
        if (iRetKey == IDYES)
        {
          iRetKey = MessageBox(0, "Czy liczba jest wieksza od 38?", "Gra", MB_YESNO);
          if (iRetKey == IDYES)
          {
            iRetKey = MessageBox(0, "Czy liczba jest wieksza od 39?", "Gra", MB_YESNO);
            if (iRetKey == IDYES)
            {
              MessageBox(0, "Twoja liczba to 40", "Gra", MB_YESNO);
            }
            else MessageBox(0, "Twoja liczba to 39", "Gra", MB_YESNO);
          }
          else
          {

          }
        }
      }
    }
  }
  else
  {
    MessageBox(0, "Smutno", "Aplikacja", MB_OK | MB_ICONQUESTION);
  }
  return 0;
}
