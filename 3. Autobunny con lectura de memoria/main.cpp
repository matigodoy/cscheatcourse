/**
 * Author: Matias Godoy
 * Date: 4/20/2024
 * Code: Autobunny con lectura de memoria (Cheat-Engine v7.5)
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

int main(int argc, char *argv[])
{
	// Direcciones de memoria
	DWORD FL_ONGROUND = 0x122DF54; // Base
	DWORD ENGINE = 0x0A3F0000;	   // Offset

	// Variables de ventana
	LPCSTR ventana = "Counter-Strike";
	HWND cs = FindWindow(0, ventana);
	HANDLE hProcess;
	DWORD pid;

	// Variables de lectura de memoria
	GetWindowThreadProcessId(cs, &pid);
	hProcess = OpenProcess(PROCESS_ALL_ACCESS, true, pid);

	int onGround;

	while (1)
	{
		// Leemos la memoria
		ReadProcessMemory(hProcess, (LPVOID)(ENGINE + FL_ONGROUND), &onGround, sizeof(onGround), 0); //

		if (GetKeyState(VK_SPACE) & 0x80000)
		{
			ReadProcessMemory(hProcess, (LPVOID)(ENGINE + FL_ONGROUND), &onGround, sizeof(onGround), 0);
			if (onGround > 0)
			{
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
			cout << ">> Esperando activacion por ESPACIO..." << endl;
		}
	}

	return 0;
}
