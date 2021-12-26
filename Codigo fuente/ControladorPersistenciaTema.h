#include<iostream>
#include "BASEDEDATOS.h"
#include <fstream>
#include <string.h>
#include <string>
#include <limits>
#include<sstream>  
//Estructuras
#include "Profesor.h"
#include "Materia.h"
#include "Actividad.h"
#include "Corte.h"
#include "GrupoMateria.h"
#include "Tarea.h"
#include "Tema.h"

using namespace std;
/**
*Persistencia de Tema
*/
class ControladorPersistenciaTema{
	
	public :
		ControladorPersistenciaTema(){
		};	
	

	//Para Tema
	void guardarTema(BASEDEDATOS< Tema > listTema);
};

void ControladorPersistenciaTema::guardarTema(BASEDEDATOS< Tema > listTema){
	
	//Nodo de la funcion
	nodo<Tema> nT;
	//Nodo de la funcion = a lista de la funcion 
	nT = *listTema.primero();
	
	//Guardar lista actividades
	ofstream fileTema("Temas.bin",ios::binary);
	if(fileTema.is_open()){
		while(nT.clave!=std::numeric_limits<int>::max()){
			fileTema.write((char *) &nT, sizeof(nT));	
			nT=*(nT.nodoSig);
		}
	}else{
		cout<<"Error al guardar";
	}	
	
}
