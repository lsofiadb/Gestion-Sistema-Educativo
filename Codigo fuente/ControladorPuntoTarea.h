#include "Tema.h"
#include "Tarea.h"
#include "Corte.h"
#include <conio.h>
#include "BASEDEDATOS.h"
#include <limits>
#include "ControladorTema.h"
#include <string.h>


#include "ControladorCargarTema.h"
#include "ControladorPersistenciaTema.h"

class ControladorPuntoTarea{	
	BASEDEDATOS<Tema> bdTemas;
	ControladorTema controladorTema;
	
	public :
		static int claveTarea;
		ControladorPuntoTarea(){
		ControladorCargarTema controladorCargarTema;
		controladorCargarTema.cargarDatosTema(bdTemas);
		
		};
		
	BASEDEDATOS<Tarea> crearTarea();
	BASEDEDATOS<Tarea> asignarPuntosTarea();
	BASEDEDATOS<Tarea> asignarUnicoPTarea();
	BASEDEDATOS<Tarea> actualizarControladorPuntoTarea();			
};
int ControladorPuntoTarea::claveTarea=1;
//---------------------------------------------------------------
BASEDEDATOS<Tarea> ControladorPuntoTarea::crearTarea(){
	int opcion;
	do{	
		cout<<endl<<"________________Asignar Tarea/s a la actividad________________"<<endl;
		cout<<"Opciones para asignar tareas :"<<endl;
		cout<<"1) Unico punto por la actividad "<<endl;
		cout<<"2) Mas de un punto por la actividad "<<endl;
		cout<<"Ingrese la opcion : ";
		cin>>opcion;
	}while(!((opcion==1)||(opcion==2)));
 cout<<"----------------------------"<<endl;
	switch(opcion){
		case 2 :
				return asignarUnicoPTarea();
			break;
		case 1 :
				return asignarPuntosTarea();
			break;	
		default:
			cout<<"Error";
	}
}

BASEDEDATOS<Tarea> ControladorPuntoTarea::asignarPuntosTarea(){
	BASEDEDATOS<Tarea> listaTarea;
	Tarea tarea;
	
	Tema auxTema;
	
	int codigoTema;
	
	cout<<"______________________________________"<<endl;
	cout<<"Tarea por valor de 100%"<<endl;
	controladorTema.setBDListaTemas(bdTemas);
	controladorTema.mostrarTemario();
	//Guardar temas
	ControladorPersistenciaTema CPT;
	CPT.guardarTema(bdTemas);
	do{
		cout<<"--------------------------------------------------"<<endl;
		cout<<endl<<" Ingrese la clave del tema a realizar : ";
		cin>>codigoTema;
		auxTema = bdTemas.buscar(codigoTema);
	}while(auxTema.codigoTema==0);
	cout<<"--------------------------------------------------"<<endl;

		//-----------------------------------
		//strcpy(<cadena_destino>, <cadena_origen>)
		strcpy(tarea.nombreTema, auxTema.nombreTema);
		//--------------------------------
		tarea.codigoTema =  auxTema.codigoTema;
		tarea.claveTarea = 	claveTarea;
		tarea.porcentaje = 100;
		claveTarea++;
		
		
		cout<<endl<<"Se ingreso correctamente la Tarea"<<endl;
		listaTarea.insertar(tarea.claveTarea,tarea);
		tarea = listaTarea.buscar(tarea.claveTarea);
		cout<<"_____________ Datos ingresados _____________ "<<endl;
		cout<<"Titulo del tema : "<<tarea.nombreTema<<endl;
		cout<<"Codigo del tema : "<<tarea.codigoTema<<endl;
		cout<<"ID de la tera creada : "<<tarea.claveTarea<<endl;
		cout<<"Valoe : "<<tarea.porcentaje<<"%"<<endl;
	return listaTarea;	
}

BASEDEDATOS<Tarea>  ControladorPuntoTarea::asignarUnicoPTarea(){
	
	BASEDEDATOS<Tarea> listaTarea;
	
	int porcentajePunto,codigoTema,cantTareas;
	Tema auxTema;
	Tarea auxTarea;
	
	cout<<"______________________________________"<<endl;
	cout<<"Tarea con mas de un punto total 100%"<<endl;
	controladorTema.setBDListaTemas(bdTemas);
	controladorTema.mostrarTemario();
	//Guardar temas
	ControladorPersistenciaTema CPT;
	CPT.guardarTema(bdTemas);
	cout<<"Ingrese la cantidad de puntos a realizar por la tarea : ";
	cin>>cantTareas;
	
	//Se agregan cantidad de puntos a la tarea 
	for(int j=0; j<cantTareas; j++){
		do{
			cout<<"--------------------------------------------------"<<endl;
			cout<<endl<<" Ingrese la clave del tema a realizar : ";
			cin>>codigoTema;
			auxTema = bdTemas.buscar(codigoTema);
		}while(auxTema.codigoTema==0);
		cout<<"--------------------------------------------------"<<endl;

		cout<<"Ingrese el valor del porcentaje para el punto "<<j+1<<" de la actividad :";
		cin>>porcentajePunto;
		//-----------------------------------
		//strcpy(<cadena_destino>, <cadena_origen>)
		strcpy(auxTarea.nombreTema, auxTema.nombreTema);
		//--------------------------------
		auxTarea.codigoTema = auxTema.codigoTema;
		auxTarea.claveTarea = claveTarea;
		auxTarea.porcentaje = porcentajePunto;
		claveTarea++;
		cout<<endl<<"Se ingreso correctamente el punto de la Tarea"<<endl;	
		//-------------------------------------------------------
		listaTarea.insertar(auxTarea.claveTarea, auxTarea);
		
		auxTarea = 	listaTarea.buscar(auxTarea.claveTarea);
		cout<<auxTarea.nombreTema<<endl;
		cout<<auxTarea.codigoTema<<endl;
		cout<<auxTarea.claveTarea<<endl;
		cout<<auxTarea.porcentaje<<endl;
		
		}
	return listaTarea;	
}

BASEDEDATOS<Tarea> ControladorPuntoTarea::actualizarControladorPuntoTarea(){
	cout<<"_________________Actualizar_______________"<<endl;
	cout<<"SE TIENEN QUE ACTUALIZAR TODOS LOS PUNTOS "<<endl;
	return crearTarea();
}


