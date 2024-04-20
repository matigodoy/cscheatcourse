#include <windows.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>

using namespace std;

int main() {
	char nick[255]="name \x22Mati\x22";
	
	
	while(1) {
		if(GetKeyState(VK_F1)){
			for(int i=0; i<100; i++){
				cout<<"se apreto f1: "<< i << endl;
				ofstream kg("keygen2009.cfg");
				kg << nick << i << "\x22" << endl;
				kg.close();
			}
			
			
		}
		Sleep(1);
	}
}
