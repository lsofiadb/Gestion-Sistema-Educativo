#include <iostream>
#include <windows.h>
#include "ControladorInicial.h"
#include <string.h>


using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	SetConsoleTitle("Base de datos academica");
	system("COLOR B");
	/**Se realiza el llamado del menu inicial */
	ControladorInicial controladorInicial;
	controladorInicial.menuInicial();
	return 0;
	                                                                                                                                                                                    
}

