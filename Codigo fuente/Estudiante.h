#ifndef ESTUDIANTE_H
#define ESTUDIANTE_H
#include "BASEDEDATOS.h"
#include "nota.h"
#include "GrupoMateria.h"
struct Estudiante{
	char nombresEstudiante [30];
	char apellidosEstudiante [30];
	int codigoEstudiante=0;
	BASEDEDATOS <nota> listaNotasEstudiante; 
	BASEDEDATOS <GrupoMateria> listaGrupoMateria;
	
	
};

#endif
