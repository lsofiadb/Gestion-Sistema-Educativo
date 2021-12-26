#include<iostream>
#include "BASEDEDATOS.h"
#include "Profesor.h"

using namespace std;
/**
Controla las diferestes opciones la lista de profesores 
*/
class ControladorIngresoProfesor{
		/**BD de profesores*/
	BASEDEDATOS<Profesor> BDListaProfesores;
	/**Objeto del controlador Asignar grupo Materia*/
	
	ControladorAsigGrupoMateria controladorAsigGrupoMateria;
	public :
		/**Constructor*/
		ControladorIngresoProfesor(){};	
		/**Menu principal*/
		int menuProfesor();
		int ingresarProfesor();
		int menuIngreso(Profesor profesor);
		
		void mostrarDatosPersonales(Profesor profesor);
		
		int moduloMateria(Profesor profesor);
		/**Asigna a una BD de profesores la que se tenia creada previamente hasta el momento*/
	
		void setListaProfesores(BASEDEDATOS<Profesor> BDListaProfesores){ControladorIngresoProfesor::BDListaProfesores = BDListaProfesores;};
};
/**Ingreso del docente*/
int ControladorIngresoProfesor::menuProfesor(){
	int opcion;
	do{
		cout<<"__________________Menu Profesor__________________"<<endl;	
		cout<<"1. Ingresar  profesor "<<endl;
		cout<<"2.           regresar "<<endl;
		cout<<"Que desea realizar :";
		cin>>opcion;
	}while(!((opcion==1)||(opcion==2)));
	
	switch(opcion) {
		case 1 :
			return ingresarProfesor();
			break;
		default:
			return 2;
	}
}
/**Validacion del ingreso del profesor de acuerdo a su cedula*/

int ControladorIngresoProfesor::ingresarProfesor(){
	Profesor profesor;
	int cedula;
	do{
		/**
		Verificar el usuario
		*/
		cout<<"_________________Ingreso Docente_________________"<<endl;
		cout<<"Ingrese el numero del documento de identificacion : ";
		cin>>cedula;
		/**Validacion*/
		profesor = BDListaProfesores.buscar(cedula);
		if(profesor.cedula==0){
			cout<<"Acceso denegado"<<endl;
			return menuProfesor();
		}
	}while(profesor.cedula==0);
	cout<<"El usuario "<<profesor.nombres<<" "<<profesor.apellidos<<" "<<" ingreso corectamente =)"<<endl;
	/**Envia al profesor al menu de Ingreso*/
	
	menuIngreso(profesor);
}

/**Funcionalidades del profesor*/

int ControladorIngresoProfesor::menuIngreso(Profesor profesor){
	int opcion;
	do{
		cout<<"_______________Menu ingreso_______________"<<endl;
		cout<<"1. Consultar informacion personal"<<endl;
		cout<<"2. Modulo Materia "<<endl;
		cout<<"3. regresar"<<endl;	
		cout<<"----------------------------------------------"<<endl;
		cout<<"Ingrese la opcion : ";
		cin>>opcion;
	}while(!((opcion==1)||(opcion==2)||(opcion==3)));
	cout<<"----------------------------------------------"<<endl;
	switch(opcion) {
		/**Visualizacion de sus datos personales*/

		case 1:
			mostrarDatosPersonales(profesor);
			break;
		/**Menu de opciones respecto a los grupos de materias que tiene a cargo*/
			
		case 2:
			if(moduloMateria(profesor)==2){
				menuIngreso(profesor);
			}
			break;
		/**Si desea regresar al menu anterior*/	
					
		default:
			return 2;
	}

}	
/**Datos personales del profesor */

void ControladorIngresoProfesor::mostrarDatosPersonales(Profesor profesor){
	cout<<"______________Informacion personal______________"<<endl;
	cout<<"Nombres                  :"<<profesor.nombres <<endl;
	cout<<"Apellidos                :"<<profesor.apellidos<<endl;
	cout<<"Documento                :"<<profesor.cedula<<endl;
	cout<<"------------------------------------------------"<<endl;
	/**Lo regresa al menu anterior*/
	
	menuIngreso(profesor);
}

int ControladorIngresoProfesor::moduloMateria(Profesor profesor){
	//Prueba Borra-----------------
	GrupoMateria grupoMateria; 
	
	int opcion;
	do{
		cout<<"_______________Menu Materia_______________"<<endl;
		cout<<"1. Consultar informacion de los grupos a cargo"<<endl;
		cout<<"2. Modificar informacion de una materia"<<endl;
		cout<<"3. Regresar"<<endl;	
		cout<<"----------------------------------------------"<<endl;
		cout<<"Ingrese la opcion : ";
		cin>>opcion;
	}while(!((opcion==1)||(opcion==2)||(opcion==3)));
		cout<<"----------------------------------------------"<<endl;
	switch(opcion) {
		/**Informacion de los grupos que tiene a cargo */
	
		case 1:
		/**Se le envia el profesor para no perder la referencia*/
	
			controladorAsigGrupoMateria.mostrarGrupoMateria(profesor);
			moduloMateria(profesor);
			break;
		/**Modificacion de los grupos que tiene a cargo*/
			
		case 2:
			if(controladorAsigGrupoMateria.modificarInformacionXmateria(profesor)==2){
				moduloMateria(profesor);
			}
			break;
		/**Si desea regresar al modulo anterior*/			
						
		default:
			return 2;
	}
}
