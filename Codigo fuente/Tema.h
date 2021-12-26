#ifndef TEMA_H
#define TEMA_H
#include "Corte.h"
#include <string>
struct Tema {
	//Datos
	//Codigo de referencia para x asignatura
	int codigoTema=0;
	char nombreTema[35];
	int indiceTema; //Tema a tratar por cada asignatura
};
#endif

