#ifndef PROFESOR_H
#define PROFESOR_H
#include "GrupoMateria.h"

struct Profesor {
		//Datos
		int cedula=0;
		char apellidos[30];
		char nombres[30];
		int numTotalClases;
		BASEDEDATOS<GrupoMateria> listaMateriaDoc;//De acuerdo a la cantidad de cortes se asigna el valor
};
#endif
