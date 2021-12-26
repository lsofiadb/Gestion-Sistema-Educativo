#ifndef CLASE_H
#define CLASE_H
#include "Profesor.h"
//Mateira generales
struct Materia {
	int idMateria=0;
	char nombreMateria[30];
	BASEDEDATOS<Profesor> listaProXClase;//Lista de profesores para una misma clase
};
#endif
