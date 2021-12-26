#include<iostream>
#include "BASEDEDATOS.h"
#include "Profesor.h"
#include "Materia.h"
#include <limits>
using namespace std;
/**
Controla las diferestes opciones la lista de Materia
*/
class ControladorMateria{
	BASEDEDATOS<Materia> BDListaMaterias;
	static int IDMateria;
	public :
	/**Constructor*/	
		ControladorMateria(){
		};	
		
	/**Creacion de una nueva materia en  la BD de materias*/
	int crearNuevaMateria();
	/**Listado de materias disponibles*/
	void mostrarMaterias();
	int eliminarMateria();
	int editarMateria();
	/**Asigna a la lista de materias la que ya se tiene con informacion previamente almacenada*/

	void setBDListaMaterias(BASEDEDATOS<Materia> BDListaMaterias){ControladorMateria::BDListaMaterias = BDListaMaterias;};
	
};
/**Identificador autoincrementable de la materia*/

int ControladorMateria::IDMateria = 1;


/**
Menu opciones para la materia
*/
int ControladorMateria::crearNuevaMateria(){
	/**Permite crear una nueva materia, insertarla en la BD y mostrar su informacion */
	
	Materia materia;
	int opcion;
	do{
		cout<<"________________Nueva materia________________"<<endl;
		cout<<"Ingrese el nombre de la Materia : ";
		cin>>materia.nombreMateria;
		materia.idMateria = IDMateria;
		//-------------------------------------------------------
		BDListaMaterias.insertar(materia.idMateria, materia);
		cout<<"----------------------------------------------"<<endl;
		cout<<"Se creo correctamente =) : "<<endl;
		materia = BDListaMaterias.buscar(materia.idMateria);
		cout<<"--------------Informacion---------------------"<<endl;
		cout<<"Nombre de la asignatura      : "<<materia.nombreMateria<<endl;
		cout<<"Identificar de la asignatura : "<<materia.idMateria<<endl;
		cout<<"-----------------------------------------------"<<endl;
		/**Si desea ingresar otra materia a la BD*/
		
		cout<<"_____________________________________________"<<endl;
		cout<<"Opciones"<<endl;
		cout<<"1. Nueva materia"<<endl;
		cout<<"2. regresar"<<endl;
		cout<<"Ingrese la opcion : "<<endl;
		cin>>opcion;
		IDMateria++;
	}while(!((opcion==1)||(opcion==2)));
	switch(opcion) {
		case 1:
				crearNuevaMateria();
			break;	
			/*Si desea regresar al menu anterior*/	
		
		default:
			return 2;
	}
}
//-------------------------------------------------------------------------
/*Muestra el listado de materias consultando a la BD de materias realizando
las validaciones respectivas*/
//-------------------------------------------------------------------------
void ControladorMateria::mostrarMaterias(){
	nodo<Materia> *nodoLista = BDListaMaterias.primero();
	Materia materia;
	
	if(nodoLista->clave!=std::numeric_limits<int>::max()){
		cout<<"_______________Listado de la Materias_______________"<<endl;
		do{
			materia = nodoLista->info;
			cout<<"Identificado de la materia : "<<materia.idMateria<<endl;
			cout<<"Nombre de la Materia       : "<<materia.nombreMateria<<endl;
			nodoLista = nodoLista->nodoSig;
		}while(nodoLista->clave!=std::numeric_limits<int>::max());
		/**Si aun no se encuentra asignada una materia en la BD*/
	
	}else{
		cout<<"No hay ninguna materia aun =)"<<endl;
	}
}

//----------------------------------------------------------------------
int ControladorMateria::eliminarMateria(){
	Materia materia;
	int IDmateria; 
	nodo<Profesor> *nodoPro; 
	 
	cout<<"Ingrese el ID de la Materia que quiere eliminar : "<<endl;
	mostrarMaterias();
	cin>>IDmateria;
	
	materia=BDListaMaterias.buscar(IDmateria);
	nodoPro = materia.listaProXClase.primero();
	
	if(materia.idMateria==0||(nodoPro->clave!=std::numeric_limits<int>::max())){
		cout<<"Datos incorrectos"<<endl;
		return 2;
	}
	BDListaMaterias.borrar(materia.idMateria);
	cout<<"Ha eliminado la materia de la base de datos"<<endl;
	mostrarMaterias();
	return 2;
	
	
}


int ControladorMateria::editarMateria(){
	Materia materia; 
	nodo<Profesor> *nodoPro; 
	int IDmateria;
	
	cout<<"Ingrese ID de la materia que quiere modificar : "<<endl;
	mostrarMaterias();
	cin>>IDmateria;
	
	nodoPro = materia.listaProXClase.primero();

	materia=BDListaMaterias.buscar(IDmateria);
								//clave == maximo no hay docente
	if((materia.idMateria==0)||(nodoPro->clave!=std::numeric_limits<int>::max())){
		cout<<"La materia no se encuentra en la base de datos o "<<endl;
		cout<<"La materia esta asignada a un profesor :( "<<endl;
		return 2;
	}
	
	cout<<"_________________Actualizar________________________"<<endl;
	cout<<"Ingrese nuevo nombre de la materia   	: ";
	cin>>materia.nombreMateria;
	
	if(BDListaMaterias.cambiar(materia.idMateria,materia)){
		cout<<"Modificacion exitosa =)"<<endl;
	}
	mostrarMaterias();
	return 2;
}
//------------------------------------------------------------------------
