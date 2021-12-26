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
class ControladorCargar{
	BASEDEDATOS<Profesor> BDListaProfesores;
	BASEDEDATOS<Materia>  BDListaMaterias;
	
	public :
		ControladorCargar(){
		};	
	

	BASEDEDATOS<Materia> cargarDatos();
	void cargarDatosProfesor(BASEDEDATOS<Materia>  BDListaMaterias);
	void cargarDatosGrupoMateria(BASEDEDATOS<Profesor>  listProfes);
	void cargarDatosCorte(BASEDEDATOS<GrupoMateria>  listGrupoMate);
	void cargarDatosActividad(BASEDEDATOS<Corte>  listCorte);
	void cargarDatosListaTarea(BASEDEDATOS<Actividad>  listActividad);
	void cargarDatosTarea(BASEDEDATOS< BASEDEDATOS< Tarea > > list_listTarea);
	
	
	
	
	void setBDListaMaterias(BASEDEDATOS<Materia> BDListaMaterias){ControladorCargar::BDListaMaterias = BDListaMaterias;};
	void setListaProfesores(BASEDEDATOS<Profesor> BDListaProfesores){ControladorCargar::BDListaProfesores = BDListaProfesores;};
};

BASEDEDATOS<Materia> ControladorCargar::cargarDatos(){
	//Lista de estructuras de la funcion
	BASEDEDATOS<Materia> listMater;
	//Nodo de la estructura de la funcion
	nodo<Materia> nM;
	
	//leer Archivo 
	//Nodo de la funcion
	ifstream fileMater( "Materias.bin", ios::binary);
	if (fileMater.is_open()){
		fileMater.read( (char *) &nM, sizeof(nM));
		while( !fileMater.eof()) {
			
			listMater.insertar(nM.clave,nM.info);
			fileMater.read( (char *) &nM, sizeof(nM));
		}
		
		BDListaMaterias = listMater;
	
		setBDListaMaterias(listMater);
		
		//Llamado para llenar profe usando la lista de materias como parametro
		cargarDatosProfesor(BDListaMaterias);
		
		return BDListaMaterias;
		
	} else{
		BASEDEDATOS<Materia> listPRRR;
		return  listMater;
		
	} cout << "Error de apertura de archivo." << endl;
	
	
	
}


void ControladorCargar::cargarDatosProfesor(BASEDEDATOS<Materia>  BDListaMaterias){
	string dirNum="";
	string nombreArchivo="";
	
	
	//Lista de estructuras de la funcion
	BASEDEDATOS<Profesor> listProfes;
	//Nodo de la estructura de la funcion
	nodo<Profesor> nP;
	
	//Estructura anterior
	Materia *m;
	//Nodo de la estructura anterior
	nodo<Materia> *nM;
	//Nodo de la estructura anterior = a lista anterior 
	nM=BDListaMaterias.primero();
	
	
	//Agregar a cada miembro de la lista de materias, las listas de los profesores
	//Nodo de la estructura anterior
	while(nM->clave!=std::numeric_limits<int>::max()){
		
		//Objeto para castear el int a string
		stringstream ss;
		//Se guarda el cont del archivos para generar el nombre
		ss<<nM->clave;
		ss>>dirNum;
		//Nombre cambiante
		nombreArchivo ="Profesores"+dirNum+".bin";
		
		//Se abre el archivo
		//Nodo de la funcion
		ifstream fileProfe( nombreArchivo.c_str(), ios::binary);
		if (fileProfe.is_open()){
			fileProfe.read( (char *) &nP, sizeof(nP));
			while( !fileProfe.eof()) {
				//Inserta en la lista de la función
				listProfes.insertar(nP.clave,nP.info);
				Profesor p=nP.info;
				cout<<p.apellidos<<p.cedula<<p.nombres<<"\n";
				fileProfe.read( (char *) &nP, sizeof(nP));
			}
		} else cout << "Error de apertura de archivo." << endl;
		
		fileProfe.close();
		
		//Estructura anterior
		m=&nM->info;
		//Estructura anteior . lista asiganda a lista de la funcion
		m->listaProXClase=listProfes;
		
		//Reinsercion
		BDListaMaterias.insertar(nM->clave,*m);
		
		//Llamar la función
		cargarDatosGrupoMateria(listProfes);
		
		//Corrimiento del nodo de la estructura anterior
		nM=nM->nodoSig;
		
	}
}

void ControladorCargar::cargarDatosGrupoMateria(BASEDEDATOS<Profesor>  listProfes){
	string dirNum="";
	string nombreArchivo="";
	
	
	//Lista de estructuras de la funcion
	BASEDEDATOS<GrupoMateria> listGrupoMate;
	//Nodo de la estructura de la funcion
	nodo<GrupoMateria> nGM;
	
	//Estructura anterior
	Profesor *p;
	//Nodo de la estructura anterior
	nodo<Profesor> *nP;
	//Nodo de la estructura anterior = a lista anterior 
	nP=listProfes.primero();
	
	
	//Agregar a cada miembro de la lista de profesores, las listas de los grupos de materias
	//Nodo de la estructura anterior
	while(nP->clave!=std::numeric_limits<int>::max()){
		//Objeto para castear el int a string
		stringstream ss;
		
		//Se guarda el cont del archivos para generar el nombre
		ss<<nP->clave;
		ss>>dirNum;
		//Nombre cambiante
		nombreArchivo ="GrupoMaterias"+dirNum+".bin";
		
		//Se abre el archivo
		//Nodo de la funcion
		ifstream fileGrupoMate( nombreArchivo.c_str(), ios::binary);
		if (fileGrupoMate.is_open()){
			fileGrupoMate.read( (char *) &nGM, sizeof(nGM));
			while( !fileGrupoMate.eof()) {
				//Inserta en la lista de la función
				listGrupoMate.insertar(nGM.clave,nGM.info);
				fileGrupoMate.read( (char *) &nGM, sizeof(nGM));
			}
		} else cout << "Error de apertura de archivo." << endl;
		fileGrupoMate.close();
		
		//Estructura anterior
		p=&nP->info;
		//Estructura anteior . lista asiganda a lista de la funcion
		p->listaMateriaDoc=listGrupoMate;
		
		//Reinsercion lista parametro. nodoAnterior, estructura anterior
		listProfes.insertar(nP->clave,*p);
		
		//Llamar la función
		cargarDatosCorte(listGrupoMate);
		
		
		//Corrimiento del nodo de la estructura anterior
		nP=nP->nodoSig;
	}
}

void ControladorCargar::cargarDatosCorte(BASEDEDATOS<GrupoMateria>  listGrupoMate){
	
	string dirNum="";
	string nombreArchivo="";
	
	
	//Lista de estructuras de la funcion
	BASEDEDATOS<Corte> listCorte;
	//Nodo de la estructura de la funcion
	nodo<Corte> nC;
	
	//Estructura anterior
	GrupoMateria *gM;
	//Nodo de la estructura anterior
	nodo<GrupoMateria> *nGM;
	//Nodo de la estructura anterior = a lista anterior 
	nGM=listGrupoMate.primero();
	
	
	//Agregar a cada miembro de la lista de los grupos de materias, las listas de los cortes
	//Nodo de la estructura anterior
	while(nGM->clave!=std::numeric_limits<int>::max()){
		
		//Objeto para castear el int a string
		stringstream ss;
		//Se guarda el cont del archivos para generar el nombre
		ss<<nGM->clave;
		ss>>dirNum;
		//Nombre cambiante
		nombreArchivo ="Cortes"+dirNum+".bin";
		
		//Se abre el archivo
		//Nodo de la funcion
		ifstream fileCorte( nombreArchivo.c_str(), ios::binary);
		if (fileCorte.is_open()){
			fileCorte.read( (char *) &nC, sizeof(nC));
			while( !fileCorte.eof()) {
				//Inserta en la lista de la función
				listCorte.insertar(nC.clave,nC.info);
				fileCorte.read( (char *) &nC, sizeof(nC));
			}
		} else cout << "Error de apertura de archivo." << endl;
		fileCorte.close();
		//Estructura anterior
		gM=&nGM->info;
		
		//Estructura anteior . lista asiganda a lista de la funcion
		gM->listaCortesXAsig=listCorte;
		
		//Reinsercion lista parametro. nodoAnterior, estructura anterior
		listGrupoMate.insertar(nGM->clave,*gM);
		
		//Llamar la función
		cargarDatosActividad(listCorte);
		
		//Corrimiento del nodo de la estructura anterior
		nGM=nGM->nodoSig;
	}
}

void ControladorCargar::cargarDatosActividad(BASEDEDATOS<Corte>  listCorte){
	string dirNum="";
	string nombreArchivo="";
	//Objeto para castear el int a string
	stringstream ss;
	
	//Lista de estructuras de la funcion
	BASEDEDATOS<Actividad> listActividad;
	//Nodo de la estructura de la funcion
	nodo<Actividad> nA;
	
	//Estructura anterior
	Corte *c;
	//Nodo de la estructura anterior
	nodo<Corte> *nC;
	//Nodo de la estructura anterior = a lista anterior 
	nC=listCorte.primero();
	
	
	//Agregar a cada miembro de la lista de los cortes, las listas de las actividades
	//Nodo de la estructura anterior
	while(nC->clave!=std::numeric_limits<int>::max()){
		//Objeto para castear el int a string
		stringstream ss;
		//Se guarda el cont del archivos para generar el nombre
		ss<<nC->clave;
		ss>>dirNum;
		//Nombre cambiante
		nombreArchivo ="Actividades"+dirNum+".bin";
		
		//Se abre el archivo
		//Nodo de la funcion
		ifstream fileActividad( nombreArchivo.c_str(), ios::binary);
		if (fileActividad.is_open()){
			fileActividad.read( (char *) &nA, sizeof(nA));
			while( !fileActividad.eof()) {
				//Inserta en la lista de la función
				listActividad.insertar(nA.clave,nA.info);
				fileActividad.read( (char *) &nA, sizeof(nA));
			}
		} else cout << "Error de apertura de archivo." << endl;
		fileActividad.close();
		//Estructura anterior
		c=&nC->info;
		//Estructura anteior . lista asiganda a lista de la funcion
		c->listActDifXCor=listActividad;
		
		
		//Reinsercion lista parametro. nodoAnterior, estructura anterior
		listCorte.insertar(nC->clave,*c);
		
		//Llamar la función
		cargarDatosListaTarea(listActividad);
		
		//Corrimiento del nodo de la estructura anterior
		nC=nC->nodoSig;
	}
}

void ControladorCargar::cargarDatosListaTarea(BASEDEDATOS<Actividad>  listActividad){
	string dirNum="";
	string nombreArchivo="";
	
	
	//Lista de estructuras de la funcion
	BASEDEDATOS< BASEDEDATOS< Tarea > > list_listTarea;
	//Nodo de la estructura de la funcion
	nodo< BASEDEDATOS < Tarea > > nLT;
	
	//Estructura anterior
	Actividad *a;
	//Nodo de la estructura anterior
	nodo<Actividad> *nA;
	//Nodo de la estructura anterior = a lista anterior 
	nA=listActividad.primero();
	
	
	/**Agregar a cada miembro de la lista de las actividades, las listas de listas de tareas*/
	//Nodo de la estructura anterior
	while(nA->clave!=std::numeric_limits<int>::max()){
		//Objeto para castear el int a string
		stringstream ss;
		//Se guarda el cont del archivos para generar el nombre
		ss<<nA->clave;
		ss>>dirNum;
		//Nombre cambiante
		nombreArchivo ="ListaTareas"+dirNum+".bin";
		
		//Se abre el archivo
		//Nodo de la funcion
		ifstream fileListListTarea( nombreArchivo.c_str(), ios::binary);
		if (fileListListTarea.is_open()){
			fileListListTarea.read( (char *) &nLT, sizeof(nLT));
			while( !fileListListTarea.eof()) {
				//Inserta en la lista de la función
				list_listTarea.insertar(nLT.clave,nLT.info);
				fileListListTarea.read( (char *) &nLT, sizeof(nLT));
			}
		} else cout << "Error de apertura de archivo." << endl;
		fileListListTarea.close();
		//Estructura anterior
		a=&nA->info;
		//Estructura anteior . lista asiganda a lista de la funcion
		a->listaTareasXAct=list_listTarea;
		
		//Reinsercion lista parametro. nodoAnterior, estructura anterior
		listActividad.insertar(nA->clave,*a);
		
		//Llamar la función
		cargarDatosTarea(list_listTarea);
		
		//Corrimiento del nodo de la estructura anterior
		nA=nA->nodoSig;
	}
}

void ControladorCargar::cargarDatosTarea(BASEDEDATOS< BASEDEDATOS< Tarea > > list_listTarea){
	string dirNum="";
	string nombreArchivo="";
	
	
	//Lista de estructuras de la funcion
	BASEDEDATOS<Tarea> listTarea;
	//Nodo de la estructura de la funcion
	nodo<Tarea> nT;
	
	//Estructura anterior
	BASEDEDATOS< Tarea > *t;
	//Tal vez borre esto
	
	
	//Nodo de la estructura anterior
	nodo< BASEDEDATOS< Tarea > > *nLT;
	//Nodo de la estructura anterior = a lista anterior 
	nLT=list_listTarea.primero();
	
	
	/**Agregar a cada miembro de las listas de listas de tareas, las listas de tareas*/
	//Nodo de la estructura anterior
	while(nLT->clave!=std::numeric_limits<int>::max()){
		//Objeto para castear el int a string
		stringstream ss;
		//Se guarda el cont del archivos para generar el nombre
		ss<<nLT->clave;
		ss>>dirNum;
		//Nombre cambiante
		nombreArchivo ="ListaTareas"+dirNum+".bin";
		
		//Se abre el archivo
		//Nodo de la funcion
		ifstream fileTarea( nombreArchivo.c_str(), ios::binary);
		if (fileTarea.is_open()){
			fileTarea.read( (char *) &nT, sizeof(nT));
			while( !fileTarea.eof()) {
				//Inserta en la lista de la función
				listTarea.insertar(nT.clave,nT.info);
				fileTarea.read( (char *) &nT, sizeof(nT));
			}
		} else cout << "Error de apertura de archivo." << endl;
		fileTarea.close();
		//Estructura anterior
		//t=t.info;
		//Estructura anteior . lista asiganda a lista de la funcion
		//t=listTarea;
		
		//Llamar la función
		//cargarDatosTarea(listTarea);
		
		//Reinsercion lista parametro. nodoAnterior, estructura anterior
		list_listTarea.insertar(nLT->clave,*t);
		
		//Corrimiento del nodo de la estructura anterior
		nLT=nLT->nodoSig;
	}
}




