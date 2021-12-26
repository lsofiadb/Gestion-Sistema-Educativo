#ifndef ASIGNATURA_H
#define ASIGNATURA_H
#include "BASEDEDATOS.h"
#include "Corte.h"
struct GrupoMateria {
	//Datos
	char nombreGrupoMateria[30];
	int grupoMateria=0;
	int cantidadCorte=0;
	
	BASEDEDATOS<Corte> listaCortesXAsig;//Para el mismo docente
};
#endif
