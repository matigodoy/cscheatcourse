#include <windows.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>

using namespace std;

int main() {
	char nick[255]="name \x22Mati\x22";
	ofstream kg("keygen2009.cfg");
	kg << nick << endl;
	
	kg.close();
}
