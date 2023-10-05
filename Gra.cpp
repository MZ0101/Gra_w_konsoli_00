#include <iostream>
#include "Pojazd.h"
#include <Windows.h>


int main()
{

    int x = 0;
    
    int y = 0;
    
    Pojazd a;
    
   
    while(a.hp)
    {
        a.czyszczenie();
// Tu się zapytaj czy jest coś lepszego niż: GetAsyncKeyState
        if (GetAsyncKeyState(0x57)) x = -1;
   
        if (GetAsyncKeyState(0x41)) y = -1;
 
        if (GetAsyncKeyState(0x53)) x = 1;
   
        if (GetAsyncKeyState(0x44)) y = 1;
        
        if (GetAsyncKeyState(0x20))
        { 
            a.pocisk(); 
        }

        a.zamiana(x, y);
        
        if (a.i % 7 == 0)
        {
            a.wrog();
            a.pocisk_w();
        }
      
        a.i++;
        a.menu();
        
        a.wyswietlanie();
        Sleep(70);
        system("cls");
        
        
    }
   
  return 0;
}