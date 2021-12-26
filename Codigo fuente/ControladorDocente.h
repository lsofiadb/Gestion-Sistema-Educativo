#include<iostream>
#include "BASEDEDATOS.h"
#include "Materia.h"
#include "Profesor.h"
#include "ControladorAsigGrupoMateria.h"
#include "GrupoMateria.h"
#include <limits>

using namespace std;
/**
Controla las diferestes opciones ------------------------
*/
class ControladorDocente{
	BASEDEDATOS<Profesor> BDListaDocente;
	BASEDEDATOS<Materia> BDListaMaterias;
	/**Objeto de la clase del controlador asignar grupo materia*/

	ControladorMateria controladorMateria;

	ControladorAsigGrupoMateria controladorAsigGrupoMateria;
	
	static int IdDocente;
	public :
		/**Constructor*/
		ControladorDocente(){};	
		/**Opciones de asignacion que tiene el administrador sobre los docentes*/

		int menuDocente();
		
		int crearNuevoDocente();
		void eliminarDocente();	
		void editarDocente();
		void mostrarListaDoc();
		
		void asignarCargaAcademicaDocente(Profesor profesor);
		/**Metodos para relacionar las listas de BD de docentes, materias, 
		con el fin de conservar los datos que han sido almacenados previamente*/
	
		void setBDListaProfesor(BASEDEDATOS<Profesor> BDListaDocente){ControladorDocente::BDListaDocente = BDListaDocente;};
		void setBDBDListaMaterias(BASEDEDATOS<Materia> BDListaMaterias){ControladorDocente::BDListaMaterias = BDListaMaterias;};
		void SetcontroladorMateria(ControladorMateria controladorMateria){ControladorDocente::controladorMateria = controladorMateria;};
		
		

};
/**Identificador autoincrementable de cada docente  */

int ControladorDocente::IdDocente = 1;

//---------------------------------------------------------------------
int ControladorDocente::menuDocente(){
	int opcion;
	cout<<"_______________Menu Docente_______________"<<endl;
	cout<<"1. Crear nuevo docente    "<<endl;
	cout<<"2. Mostrar lista docentes "<<endl;
	cout<<"3. Eliminar docente "<<endl;
	cout<<"4 Editar docente "<<endl;
	cout<<"5. regresar"<<endl;
	cout<<"-------------------------------------------"<<endl;
	cout<<"Ingrese la opcion : ";
	cin>>opcion;
	cout<<"-------------------------------------------"<<endl;
	switch(opcion) {
		case 1:
			return crearNuevoDocente();
			break;
		case 2:
			mostrarListaDoc();
			break;	
		case 3:
			eliminarDocente();
			break;
		case 4:
			editarDocente();
			break;			
		default :
			return 2;
	}
}
/**Permite agregar un nuevo docente a la BD de docentes*/

int ControladorDocente::crearNuevoDocente(){
	Profesor profesor;
	/**Se asignan los datos personales en un estructura tipo profesor*/
	
	cout<<"1. Crear nuevo docente    "<<endl;
	cout<<"Ingrese el numero de su cedula : ";
	cin>>profesor.cedula;
	cout<<"Ingrese los apellidos : ";
	cin>>profesor.apellidos;
	cout<<"Ingrese los nombres   : ";
	cin>>profesor.nombres;
	do{
		/**Se le asignan el total de clases a la estructura*/
		
		cout<<"Ingrese el numero total de clases a cargo del docente : ";
		cin>>profesor.numTotalClases;	
		/**Validacion del valor ingresado recorriendo la BD de materias*/
		
		if(BDListaMaterias.primero()->clave==std::numeric_limits<int>::max()){
			profesor.numTotalClases=0;
			cout<<"Error (No hay materias registradas o el # ingresado es negativo)"<<endl;
			return 2;
		}
	}while(profesor.numTotalClases<=0);
	/**Se llama a la funcion para asignarle carga academica a cada profesor 
		enviandole al mismo  como parametro para conservar la informacion previamente ingresada */
	
	
	asignarCargaAcademicaDocente(profesor);
}

//----------------------------------------------------------------------------------
void ControladorDocente::asignarCargaAcademicaDocente(Profesor profesor){
	/**Almacenara la informacion de la materia asignada al docente*/

	Materia materia;
	int identificador;
	/**Curso que dictara el profesor*/
	
	GrupoMateria grupoMateria;
	
/*Se repite el procedimiento de acuerdo al numero total de clases 
	que se le fueron asignadas al docente*/
		
	for(int j=0; j<profesor.numTotalClases; j++){
			/**Le muestra la lista de materias que hay en la BD de materias*/
	
		controladorMateria.mostrarMaterias();
		do{
			cout<<"_________________Asignacion de carga academica_________________"<<endl;
			/**Identificador de la materia que le fue asignada al docente para agregar su informacion*/
		
			cout<<"Ingrese el identificador de la materia :";
			cin>>identificador;
			/*Almacena la materia con el respectivo identificador ingresado */

			materia = BDListaMaterias.buscar(identificador);
				/**Valida en caso de no encontrar dicha materia*/
		
			if(materia.idMateria==0){
				cout<<"Identificador erroneo"<<endl;
			}
		}while(materia.idMateria == 0);
		//-----------------------------------------------------------------------
		/**Envia la materia que se quiere modificar al controlador de grupo materia*/
	
		
		//------------------------------------------
		grupoMateria = controladorAsigGrupoMateria.crearNuevoGrupoMateria(materia);
		/**Le inserta la materia con toda la informacion a la lista de materias del profesor*/

		profesor.listaMateriaDoc.insertar(grupoMateria.grupoMateria, grupoMateria);
		cout<<"A cargado la materia al docente correctamente..."<<endl;
		/**Inserta el profesor a la BD de profesores*/
		
		BDListaDocente.insertar(profesor.cedula, profesor);
		/**Inserta el profesor a la BD de profesores por clase*/
		
		materia.listaProXClase.insertar(profesor.cedula,profesor);
	}
	menuDocente();
}


void ControladorDocente::mostrarListaDoc(){
	nodo<Materia> nM = *BDListaMaterias.primero();
	Materia m;
	
	cout<<"_________________listado docentes___________________"<<"\n";
	while(nM.clave!=std::numeric_limits<int>::max()){
		nodo<Profesor> nP= *m.listaProXClase.primero();
		Profesor p;
		while(nP.clave!=std::numeric_limits<int>::max()){
			p=nP.info;
			cout<<"Nombres del docente   : "<<p.nombres<<"\n";
			cout<<"Apellidos del docente : "<<p.apellidos<<"\n";
			cout<<"Cedula del docente    : "<<p.cedula<<"\n";
			cout<<"Carga academica       : "<<p.numTotalClases<<" cursos "<<"\n";
			nP=*nP.nodoSig;
		}
		
		nM=*nM.nodoSig;
	}
	
	
	nodo<Profesor> *nodoPro = BDListaDocente.primero();
	Profesor profesor;
	cout<<"_________________listado docentes___________________"<<endl;
	while(nodoPro->clave!=std::numeric_limits<int>::max()){
		profesor = nodoPro->info;
		cout<<"Nombres del docente   : "<<profesor.nombres<<endl;
		cout<<"Apellidos del docente : "<<profesor.apellidos<<endl;
		cout<<"Cedula del docente    : "<<profesor.cedula<<endl;
		cout<<"Carga academica       : "<<profesor.numTotalClases<<" cursos "<<endl;
		nodoPro = nodoPro->nodoSig;
	}
	cout<<"_____________________________________________________"<<endl;
	menuDocente();
}

void ControladorDocente::eliminarDocente(){
	Profesor profesor;
	int cedula; 
	cout<<"Ingrese el numero de cedula del docente que quiere eliminar : "<<endl;
	mostrarListaDoc();
	cin>>cedula;
	profesor=BDListaDocente.buscar(cedula);
	if(profesor.cedula==0){
		menuDocente();
	}
	BDListaDocente.borrar(cedula);
	cout<<"Ha eliminado al docente de la base de datos"<<endl;
	mostrarListaDoc();
	menuDocente();
}

void ControladorDocente::editarDocente(){
	Profesor profesor; 
	int cedula;
	cout<<"Ingrese el numero de cedula del docente que quiere modificar : "<<endl;
	mostrarListaDoc();
	cin>>cedula;
	profesor=BDListaDocente.buscar(cedula);
	if(profesor.cedula==0){
		cout<<"El profesor no se encuentra en la base de datos :( "<<endl;
		menuDocente();
	}
	cout<<"_________________Actualizar________________________"<<endl;
	cout<<"Ingrese nuevo nombre del docente   	: ";
	cin>>profesor.nombres;
	cout<<"Ingrese nuevo apellidos del docente 	: ";
	cin>>profesor.apellidos;
	
	if(BDListaDocente.cambiar(profesor.cedula, profesor)){
		cout<<"Modificacion exitosa =)"<<endl;
	}
	menuDocente();
}
