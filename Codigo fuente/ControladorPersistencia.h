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
Se encarga de identificar a los usuarios
*/
class ControladorPersistencia{
	BASEDEDATOS<Profesor> BDListaProfesores;
	BASEDEDATOS<Materia>  BDListaMaterias;
	
	public :
		ControladorPersistencia(){
		};	
	
	void guardarDatos();
	//Para profesor
	void guardarProfesor(BASEDEDATOS<Profesor> listProf, string nameFile);
	//Para grupo materia
	void guardarGrupoMateria(BASEDEDATOS<GrupoMateria> listGrupoMate, string nameFile);
	//Para corte
	void guardarCorte(BASEDEDATOS<Corte> listCorte, string nameFile);
	//Para actividad
	void guardarActividad(BASEDEDATOS<Actividad> listActividad, string nameFile);
	//Para lista de tareas
	void guardarListaTareas(BASEDEDATOS< BASEDEDATOS< Tarea > > list_listTarea, string nameFile);
	//Para Tarea
	void guardarTarea(BASEDEDATOS<Tarea> listTarea, string nameFile);
	
	
	//Para Tema
	void guardarTema(BASEDEDATOS< Tema > listTema);
	void setBDListaMaterias(BASEDEDATOS<Materia> BDListaMaterias){ControladorPersistencia::BDListaMaterias = BDListaMaterias;};
	void setListaProfesores(BASEDEDATOS<Profesor> BDListaProfesores){ControladorPersistencia::BDListaProfesores = BDListaProfesores;};
};

void ControladorPersistencia::guardarDatos (){
	
	//Nodo de la funcion
	nodo<Materia> nM;
	//Nodo de la funcion = a lista de la funcion 
	nM = *BDListaMaterias.primero();
	
	//Guardar lista materias
	ofstream fileMateria("Materias.bin",ios::binary);
	if(fileMateria.is_open()){
		while(nM.clave!=std::numeric_limits<int>::max()){
			fileMateria.write((char *) &nM, sizeof(nM));	
			nM=*(nM.nodoSig);
		}
	}else{
		cout<<"Error al guardar";
	}	
	
	//Guardar listas de profesores
	//Lista del siguiente
	BASEDEDATOS<Profesor> listProf;
	//Nodo del siguiente
	nodo<Profesor> nP;
	//Estructura de la funcion
	Materia m;
	//nodo de la funcion = a lista de la funcion 
	nM=*BDListaMaterias.primero();
	//nodo de la funcion
	while(nM.clave!=std::numeric_limits<int>::max()){
		//Estructura de la funcion = a nodo de la funcion
		m = nM.info;
		//Lista del siguiente = a estructura de la funcion
		listProf=m.listaProXClase;
		//Guarda profesor
		string key;
		stringstream ss;
		//nodo de la funcion
		ss<<nM.clave;
		ss>>key;
		//llamado del siguinte, lista de la siguiente funcion y key
		guardarProfesor(listProf,key);
		//corrimiento nodo de la funcion	
		nM=*nM.nodoSig;
	}
	
	
	
}
//Guardado de profesores
//nameFile es el numero del archivo correspondiente a la clave de la lista del elemento al cual pertenece
void ControladorPersistencia::guardarProfesor(BASEDEDATOS<Profesor> listProf, string nameFile){
	nameFile="Profesores"+ nameFile+".bin";
	
	//Nodo de la funcion
	nodo<Profesor> nP;
	//Nodo de la funcion = a lista de la funcion 
	nP = *listProf.primero();
	
	//Guardar lista materias
	ofstream fileProfesor(nameFile.c_str(),ios::binary);
	if(fileProfesor.is_open()){
		while(nP.clave!=std::numeric_limits<int>::max()){
			fileProfesor.write((char *) &nP, sizeof(nP));	
			nP=*(nP.nodoSig);
		}
	}else{
		cout<<"Error al guardar";
	}	
	
	//Guardar listas de grupo
	//Lista del siguiente
	BASEDEDATOS<GrupoMateria> listGruMa;
	//Nodo del siguiente
	nodo<GrupoMateria> nGM;
	//Estructura de la funcion
	Profesor p;
	//nodo de la funcion = a lista de la funcion 
	nP=*listProf.primero();
	//nodo de la funcion
	while(nP.clave!=std::numeric_limits<int>::max()){
		//Estructura de la funcion = a nodo de la funcion
		p = nP.info;
		//Lista del siguiente = a estructura de la funcion
		listGruMa = p.listaMateriaDoc;
		//Guarda profesor
		string key;
		stringstream ss;
		//nodo de la funcion
		ss<<nP.clave;
		ss>>key;
		//llamado del siguinte, lista de la siguiente funcion y key
		guardarGrupoMateria(listGruMa,key);	
		//corrimiento nodo de la funcion	
		nP=*nP.nodoSig;
	}
}


//Guardado de Grupo Materia
//nameFile es el numero del archivo correspondiente a la clave de la lista del elemento al cual pertenece
void ControladorPersistencia::guardarGrupoMateria(BASEDEDATOS<GrupoMateria> listGrupoMate, string nameFile){
	nameFile="GrupoMaterias"+ nameFile+".bin";
	
	//Nodo de la funcion
	nodo<GrupoMateria> nGM;
	//Nodo de la funcion = a lista de la funcion 
	nGM = *listGrupoMate.primero();
	
	//Guardar lista materias
	ofstream fileGrupoMateria(nameFile.c_str(),ios::binary);
	if(fileGrupoMateria.is_open()){
		while(nGM.clave!=std::numeric_limits<int>::max()){
			fileGrupoMateria.write((char *) &nGM, sizeof(nGM));	
			nGM=*(nGM.nodoSig);
		}
	}else{
		cout<<"Error al guardar";
	}	
	
	//Guardar listas de grupo
	//Lista del siguiente
	BASEDEDATOS<Corte> listCorte;
	//Nodo del siguiente
	nodo<Corte> nC;
	//Estructura de la funcion
	GrupoMateria grupoM;
	//nodo de la funcion = a lista de la funcion 
	nGM=*listGrupoMate.primero();
	//nodo de la funcion
	while(nGM.clave!=std::numeric_limits<int>::max()){
		//Estructura de la funcion = a nodo de la funcion
		grupoM = nGM.info;
		//Lista del siguiente = a estructura de la funcion
		listCorte = grupoM.listaCortesXAsig;
		//Guarda profesor
		string key;
		stringstream ss;
		//nodo de la funcion
		ss<<nGM.clave;
		ss>>key;
		//llamado del siguinte, lista de la siguiente funcion y key
		guardarCorte(listCorte,key);	
		//corrimiento nodo de la funcion	
		nGM=*nGM.nodoSig;
	}
			
}

void ControladorPersistencia::guardarCorte(BASEDEDATOS<Corte> listCorte, string nameFile){
	nameFile="Cortes"+ nameFile+".bin";
	
	//Nodo de la funcion
	nodo<Corte> nC;
	//Nodo de la funcion = a lista de la funcion 
	nC = *listCorte.primero();
	
	//Guardar lista materias
	ofstream fileCorte(nameFile.c_str(),ios::binary);
	if(fileCorte.is_open()){
		while(nC.clave!=std::numeric_limits<int>::max()){
			fileCorte.write((char *) &nC, sizeof(nC));	
			nC=*(nC.nodoSig);
		}
	}else{
		cout<<"Error al guardar";
	}	
	
	//Guardar listas de grupo
	//Lista del siguiente
	BASEDEDATOS<Actividad> listActividad;
	//Nodo del siguiente
	nodo<Actividad> nA;
	//Estructura de la funcion
	Corte c;
	//nodo de la funcion = a lista de la funcion 
	nC=*listCorte.primero();
	//nodo de la funcion
	while(nC.clave!=std::numeric_limits<int>::max()){
		//Estructura de la funcion = a nodo de la funcion
		c = nC.info;
		//Lista del siguiente = a estructura de la funcion
		listActividad = c.listActDifXCor;
		//Guarda profesor
		string key;
		stringstream ss;
		//nodo de la funcion
		ss<<nC.clave;
		ss>>key;
		//llamado del siguinte, lista de la siguiente funcion y key
		guardarActividad(listActividad,key);	
		//corrimiento nodo de la funcion	
		nC=*nC.nodoSig;
	}
}

void ControladorPersistencia::guardarActividad(BASEDEDATOS<Actividad> listActividad, string nameFile){
	nameFile="Actividades"+ nameFile+".bin";
	
	//Nodo de la funcion
	nodo<Actividad> nA;
	//Nodo de la funcion = a lista de la funcion 
	nA = *listActividad.primero();
	
	//Guardar lista actividades
	ofstream fileActividad(nameFile.c_str(),ios::binary);
	if(fileActividad.is_open()){
		while(nA.clave!=std::numeric_limits<int>::max()){
			fileActividad.write((char *) &nA, sizeof(nA));	
			nA=*(nA.nodoSig);
		}
	}else{
		cout<<"Error al guardar";
	}	
	//Nota
	//Esctructura siguiente BASEDEDATOS< Tarea >
	
	//Guardar listas de grupo
	//Lista del siguiente
	BASEDEDATOS< BASEDEDATOS< Tarea > > list_listTarea;
	//Nodo del siguiente
	nodo < BASEDEDATOS < Tarea > >  nLT;
	//Estructura de la funcion
	Actividad a;
	//nodo de la funcion = a lista de la funcion 
	nA=*listActividad.primero();
	//nodo de la funcion
	while(nA.clave!=std::numeric_limits<int>::max()){
		//Estructura de la funcion = a nodo de la funcion
		a = nA.info;
		//Lista del siguiente = a estructura de la funcion
		list_listTarea = a.listaTareasXAct;
		//Guarda BASEDEDATOS< Tarea >
		string key;
		stringstream ss;
		//nodo de la funcion
		ss<<nA.clave;
		ss>>key;
		//llamado del siguinte, lista de la siguiente funcion y key
		guardarListaTareas(list_listTarea,key);	
		//corrimiento nodo de la funcion	
		nA=*nA.nodoSig;
	}
}

void ControladorPersistencia::guardarListaTareas(BASEDEDATOS< BASEDEDATOS< Tarea > > list_listTarea, string nameFile){
	nameFile="ListaTareas"+ nameFile+".bin";
	
	//Nodo de la funcion
	nodo< BASEDEDATOS< Tarea > > nLT;
	//Nodo de la funcion = a lista de la funcion 
	nLT = *list_listTarea.primero();
	
	//Guardar lista actividades
	ofstream fileListTarea(nameFile.c_str(),ios::binary);
	if(fileListTarea.is_open()){
		while(nLT.clave!=std::numeric_limits<int>::max()){
			fileListTarea.write((char *) &nLT, sizeof(nLT));	
			nLT=*(nLT.nodoSig);
		}
	}else{
		cout<<"Error al guardar";
	}	
	
	//Guardar listas de grupo
	//Lista del siguiente
	BASEDEDATOS< Tarea > listTarea;
	//Nodo del siguiente
	nodo<Tarea> nT;
	
	//Estructura de la funcion
	BASEDEDATOS< Tarea > lT;
	
	//nodo de la funcion = a lista de la funcion 
	nLT=*list_listTarea.primero();
	//nodo de la funcion
	while(nLT.clave!=std::numeric_limits<int>::max()){
		//Estructura de la funcion = a nodo de la funcion
		lT = nLT.info;
		
		//Lista del siguiente = a estructura de la funcion
		listTarea = lT;
		
		//Guarda "lista" tareas
		string key;
		stringstream ss;
		//nodo de la funcion
		ss<<nLT.clave;
		ss>>key;
		//llamado del siguinte, lista de la siguiente funcion y key
		guardarTarea(listTarea,key);	
		//corrimiento nodo de la funcion	
		nLT=*nLT.nodoSig;
	}
}


void ControladorPersistencia::guardarTarea(BASEDEDATOS< Tarea > listTarea, string nameFile){
	nameFile="Tareas"+ nameFile+".bin";
	
	//Nodo de la funcion
	nodo<Tarea> nT;
	//Nodo de la funcion = a lista de la funcion 
	nT = *listTarea.primero();
	
	//Guardar lista actividades
	ofstream fileTarea(nameFile.c_str(),ios::binary);
	if(fileTarea.is_open()){
		while(nT.clave!=std::numeric_limits<int>::max()){
			fileTarea.write((char *) &nT, sizeof(nT));	
			nT=*(nT.nodoSig);
		}
	}else{
		cout<<"Error al guardar";
	}	
	
}

void ControladorPersistencia::guardarTema(BASEDEDATOS< Tema > listTema){
	
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


