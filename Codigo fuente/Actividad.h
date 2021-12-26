#ifndef ACTIVIDAD_H
#define ACTIVIDAD_H
#include "BASEDEDATOS.h"
#include "Tarea.h"

struct Actividad {
		int claveActividad=0;
		//Datos
		int porcentajeAct;
		//string tipoActividad; //(Quiz, Taller, Parcial, proyecto, exposicion).
		int tipoActividad;
		int repeticionActividad=0;
		//Apuntador a la lista de tareas
		BASEDEDATOS< BASEDEDATOS< Tarea > > listaTareasXAct;
};
#endif
