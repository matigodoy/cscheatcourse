/**
 * Author: Matias Godoy
 * Date: 4/21/2024
 * Code: Autobunny con lectura de memoria y HUD
 */

#include <windows.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>

using namespace std;

#define sec1 Sleep(1);
#define cls system("cls");
#define VK_F2 0x3C0000 // Con esto redefinimos la tecla q ya existe, "VK_F2" por el hexa de F2

int main(int argc, char const *argv[])
{
#pragma region Direcciones de memoria

    // Dlls
    DWORD CLIENT = 0x28640000;
    DWORD ENGINE = 0x14830000;

    // Dirección menú / hud
    DWORD MENU_STATE = 0x12537C;
    int menuOn = 1;
    int menuOff = 0;
    DWORD MENU_TEXT = 0x1316D3;
    char menuText[255] = ">> Saltando";

    // Dirección suelo
    DWORD FL_ONGROUND = 0x122DF54;

#pragma endregion Direcciones de memoria

    // Variables de ventana
    LPCSTR ventana = "Counter-Strike";
    HWND cs = FindWindow(0, ventana);
    if (cs == NULL)
    {
        cout << "No se encontró la ventana '" << ventana << "'." << endl;
        return 1;
    }

    HANDLE hProcess;
    DWORD pid;

    // Variables de lectura de memoria
    GetWindowThreadProcessId(cs, &pid);
    hProcess = OpenProcess(PROCESS_ALL_ACCESS, true, pid);
    if (hProcess == NULL)
    {
        cout << "Falló al abrir el proceso (pId: " << pid << ")." << endl;
        return 1;
    }
    else
    {
        cout << "Proceso abierto correctamente (pId: " << pid << ")." << endl;
    }

    int onGround;

    WriteProcessMemory(hProcess, (LPVOID)(CLIENT + MENU_TEXT), &menuText, sizeof(menuText), 0); // Escribimos el texto en el HUD

    while (1)
    {
        // if (GetKeyState(VK_F3))
        // {
        //     WriteProcessMemory(hProcess, (LPVOID)(CLIENT + MENU_STATE), &menuOn, sizeof(menuOn), 0); //
        //     cout << ">> Menu activado <<" << endl;
        // }
        // else
        // {
        //     WriteProcessMemory(hProcess, (LPVOID)(CLIENT + MENU_STATE), &menuOff, sizeof(menuOff), 0); //
        //     cout << ">> Menu desactivado <<" << endl;
        // }

        // Leemos la memoria
        ReadProcessMemory(hProcess, (LPVOID)(ENGINE + FL_ONGROUND), &onGround, sizeof(onGround), 0); //

        if (GetKeyState(VK_SPACE) & 0x80000)
        {
            ReadProcessMemory(hProcess, (LPVOID)(ENGINE + FL_ONGROUND), &onGround, sizeof(onGround), 0);
            if (onGround > 0)
            {
                WriteProcessMemory(hProcess, (LPVOID)(CLIENT + MENU_STATE), &menuOn, sizeof(menuOn), 0); // Mostramos el HUD
                cout << ">> Saltando <<" << endl;
                ReadProcessMemory(hProcess, (LPVOID)(ENGINE + FL_ONGROUND), &onGround, sizeof(onGround), 0);
                SendMessage(cs, WM_KEYDOWN, VK_F2, VK_F2);
                sec1
                    SendMessage(cs, WM_KEYUP, VK_F2, VK_F2);
                sec1
            }
        }
        else
        {
            WriteProcessMemory(hProcess, (LPVOID)(CLIENT + MENU_STATE), &menuOff, sizeof(menuOff), 0); // Ocultamos el HUD
            cout << ">> Esperando activacion por ESPACIO..." << endl;
        }
    }

    return 0;
}
