/**
 * Author: Matias Godoy
 * Date: 4/20/2024
 * Code: Autobunny básico para Counter Strike 1.6
 */

#include <windows.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>

using namespace std;

#define sec1 Sleep(1);
#define VK_F2 0x3C0000 // Con esto redefinimos la tecla q ya existe, "VK_F2" por el hexa de F2

int main()
{
    // Declaramos la ventana por el nombre de la misma
    LPCSTR ventana = "Counter-Strike";
    HWND cs = FindWindow(0, ventana);

    while (1)
    {
        if (GetKeyState(VK_SPACE)) // Se puede agregar una condición (& 0x8000) para que solo se active mientras está presionada
        {
            cout << ">> Saltando <<" << endl;
            // Presionamos la tecla F2, esperamos, la soltamos y luego duerme 2s
            SendMessage(cs, WM_KEYDOWN, VK_F2, VK_F2);
            sec1
                SendMessage(cs, WM_KEYUP, VK_F2, VK_F2);
        }
        else
        {
            cout << ">> Esperando activacion por ESPACIO..." << endl;
        }
        sec1
    }
}
