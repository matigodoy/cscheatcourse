#include <windows.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>

#define VK_F2 0x3C0000  // Con esto redefinimos la tecla q ya existe, "VK_F2" por el hexa de F2

using namespace std;

int main() {
	char nick[255]="name \x22Mati\x22"; // x22 es el hexa de las "
	
	// Declaramos la ventana por el nombre de la misma
	HWND cs=FindWindow(0,"Counter-Strike");
	
	while(1) {
		if(GetKeyState(VK_F1)){
			for(int i=0; i<100; i++){
				// Creamos archivo cfg y le damos valores.
				cout<<"se apreto f1: "<< i << endl;
				ofstream file("nickname.cfg");
				file << nick << i << "\x22" << endl;
				file.close();
				
				// Presionamos la tecla F2, esperamos, la soltamos y luego duerme 2s
				SendMessage(cs,WM_KEYDOWN,VK_F2,VK_F2);
				Sleep(1);
				SendMessage(cs,WM_KEYUP,VK_F2,VK_F2);
				Sleep(2000);
			}
			
			
		}
		Sleep(1);
	}
}
