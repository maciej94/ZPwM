#include <Windows.h> //zawsze dolaczany do aplikacji windowsowej
#include <stdio.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow) //dla aplikacji win zamiast main jest WinMain
{
  int iRetKey = MessageBox(0, "Wybierz liczbe z zakresu 1-40.", "Gra", MB_OK);
  
  int gora = 40, dol = 1, srodek = 0;
  char buf[500];

  do
  {
    srodek = (gora + dol) / 2;
    sprintf_s(buf, "Czy Twoja liczba jest wieksza od %d?", srodek);
    iRetKey = MessageBox(0, buf, "Gra", MB_YESNO);
    if (iRetKey == IDYES) dol = srodek + 1;
    else gora = srodek;
  } while (gora > dol);
  
  sprintf_s(buf, "Twoja liczba to %d?", dol);
  iRetKey = MessageBox(0, buf, "Gra", MB_YESNO);
  if (iRetKey == IDYES) MessageBox(0, "Zgadlem!", "Gra", MB_OK);
  else MessageBox(0, "UPS!", "Gra", MB_OK);

  return 0;
}
