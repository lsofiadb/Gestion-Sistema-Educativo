#ifndef CORTE_H
#define CORTE_H
#include "Actividad.h"
struct Corte {
		bool inicializacion = false;
		int claveCorte=0;
		int numCorte=0;
		int porcentajeCorte =1;
		//De acuerdo a la cantidad de actividades se asigna el valor
		BASEDEDATOS<Actividad> listActDifXCor; //Actividad 1-2-3....n por corte
		//Actividad 1-2-3....n por corte
};
#endif
