#include<iostream>
#include "BASEDEDATOS.h"
#include "Profesor.h"
#include "Materia.h"
#include "ControladorAdministrador.h"
#include "ControladorIngresoProfesor.h"
#include "ControladorPersistencia.h"
#include "ControladorCargar.h"

using namespace std;
/**
Se encarga de identificar a los usuarios
*/
class ControladorInicial{
	/**Base de datos de profesores*/

	BASEDEDATOS<Profesor> BDListaProfesores;
	/**Base de datos de materias */
	BASEDEDATOS<Materia>  BDListaMaterias;
	/**Objeto de la clase controlador administrador*/
	
	ControladorAdministrador controladorAdministrador;
	/*Objeto de la clase controlador ingreso profesor*/
	
	ControladorIngresoProfesor controladorIngresoProfesor;
	BASEDEDATOS<Estudiante> BDListaEstudiantes;
	BASEDEDATOS<GrupoMateria> BDListaGrupoMateria;
	//------------------------------------------------
	
	//-------------------------------------------------
	public :
		/**Constructor*/
		ControladorInicial(){
		};		
		
	void menuInicial();
	void prueba();
	
};
/**
Menu opciones para el usuario
*/

void ControladorInicial::menuInicial(){
	ControladorPersistencia controladorPersistencia;
	ControladorCargar controladorCargar;
	
	controladorCargar.setBDListaMaterias(BDListaMaterias);
	controladorCargar.setListaProfesores(BDListaProfesores);
	if(!controladorCargar.cargarDatos().lista_vacia()){
		BDListaMaterias=controladorCargar.cargarDatos();
	}
	system("CLS");
	int opcion;
	do{
		cout<<"___________Login______________"<<endl;
		cout<<"1. Administrador"<<endl;
		cout<<"2. Profesor"<<endl;
		cout<<"3. Salir"<<endl;
		cout<<"------------------------------"<<endl;
		cout<<"Ingrese la opcion : ";
		cin>>opcion;
	}while(!((opcion==1)||(opcion==2)||(opcion==3)));	
	/**Usuario administrador*/

	cout<<endl;
	switch(opcion) {
		case 1:
			/*se le envia una lista de materias al administrador para ir realizando cambios sobre esta*/
			
			controladorAdministrador.setBDListaMaterias(BDListaMaterias);
			/*se le envia una lista de profesores al administrador para ir realizando cambios sobre esta*/
			
			controladorAdministrador.setListaProfesores(BDListaProfesores);
			controladorAdministrador.setBDListaGrupoMateria(BDListaGrupoMateria);
			ControladorAdministrador().setBDListaEstudiantes(BDListaEstudiantes);
			/**Si el administrador quiere regresar al menuInicial*/
		
			if(controladorAdministrador.menuAdministrador()==2){
				menuInicial();
			}
			break;
		case 2:
			prueba();
			/*Se le envia la lista de profesores creados por el administrador al controlador de ingreso Profesor*/
			controladorIngresoProfesor.setListaProfesores(BDListaProfesores);
			/**Si el profesor quiere regresar al menuInicial*/
			
			if(controladorIngresoProfesor.menuProfesor()==2){
				menuInicial();
			}
			break;	
		case 3:
			controladorPersistencia.setBDListaMaterias(BDListaMaterias);
			controladorPersistencia.setListaProfesores(BDListaProfesores);
			controladorPersistencia.guardarDatos();
			break;		
		default:
			cout<<"Error";
	}
}

void ControladorInicial::prueba(){
	Profesor profesor;
	
	profesor.cedula = 123;
	profesor.nombres[0] = 'c';
	profesor.apellidos[0] = 'p';
	
	profesor.numTotalClases = 1;
	
	GrupoMateria grupoMateria;
	grupoMateria.grupoMateria = 1;
	grupoMateria.nombreGrupoMateria[0] = 's';


	profesor.listaMateriaDoc.insertar(1, grupoMateria);
	BDListaProfesores.insertar(123, profesor);

}

