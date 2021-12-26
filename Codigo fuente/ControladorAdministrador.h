#include<iostream>
#include "BASEDEDATOS.h"
#include "Profesor.h"
#include "Materia.h"
#include "ControladorMateria.h"
#include "ControladorDocente.h"
#include "Estudiante.h"
#include "GrupoMateria.h"
#include "ControladorEstudiante.h"

using namespace std;
/**
Se encarga de identificar al administrador
*/
class ControladorAdministrador{	
	BASEDEDATOS<Profesor> BDListaProfesores;
	BASEDEDATOS<Materia>  BDListaMaterias;
	/**Objeto de la clase Controlador materia*/
	ControladorMateria controladorMateria;
	/**Objeto de la clase Controlador docente*/
	ControladorDocente controladorDocente;
	BASEDEDATOS<Estudiante>  BDListaEstudiantes;
	BASEDEDATOS<GrupoMateria> BDListaGrupoMateria;
	ControladorEstudiante controladorEstudiante;
	
	public :
		/**Constructor*/
		ControladorAdministrador(){
			//this.controladorInicial = controladorInicial;
		};
		/**Menu del adiministrador*/
		int menuAdministrador();
		/**Funciones a cargo del administrador*/
		void funcionesAdministrador();
		
		/**Creacion de una nueva materia que sera almacenada en la BD*/
		void crearNuevaMateria();
		
		/**
		Asignacion de las listas generales del aplicativo
		*/
		void setBDListaMaterias(BASEDEDATOS<Materia> BDListaMaterias){ControladorAdministrador::BDListaMaterias = BDListaMaterias;};
		void setListaProfesores(BASEDEDATOS<Profesor> BDListaProfesores){ControladorAdministrador::BDListaProfesores = BDListaProfesores;};
		void setBDListaEstudiantes(BASEDEDATOS<Estudiante> BDListaEstudiantes){ControladorAdministrador::BDListaEstudiantes = BDListaEstudiantes;};
		void setBDListaGrupoMateria(BASEDEDATOS<GrupoMateria> BDListaGrupoMateria){ControladorAdministrador::BDListaGrupoMateria = BDListaGrupoMateria;};


};
/**
Menu opciones para el administrador
*/
//--------------------------------------------------------------------------------------

int ControladorAdministrador::menuAdministrador(){
	/**Clave de ingreso del administrador*/
	int clave;
	int opcionSistema;
		/**Se realizara el menu hasta que se ingrese la opcion correcta*/

	do{
		cout<<"________________Administrador________________"<<endl;
		cout<<"1. Ingresar"<<endl;
		cout<<"2. Regresar"<<endl;
		cout<<"----------------------------------------------"<<endl;
		cout<<"Ingrese la opcion : ";
		cin>>opcionSistema;
	}while(!((opcionSistema==1)||(opcionSistema==2)));
	cout<<"----------------------------------------------"<<endl;
	/**Ingreso del administrador al sistema*/
	switch(opcionSistema) {
		case 1:
			cout<<"Ingrese la clave : ";
			cin>>clave;
			if(clave == 123){
				cout<<"Ingreso corectamente"<<endl;
				/**llamado a las funciones del administrador ya que ingreso al sistema*/
				funcionesAdministrador();
			}else{
				/**En caso de ingresar una clave invalida*/
				cout<<"Usuario invalido"<<endl;
				menuAdministrador();
			}
			break;
		/**Valor de retorno para regresar al menu anterior*/	
		default :
			return 2;
			break;
	}
}

//-----------------------------------------------------------------
void ControladorAdministrador::funcionesAdministrador(){
	//Estructura tipo materia
	Materia mat;
	int opcion_1;
	/**Se envia el listado de materias que se tienen hasta el momento al controlador de materias */

			
	controladorMateria.setBDListaMaterias(BDListaMaterias);
	do{
		cout<<"________________Modulos administrador________________"<<endl;
		cout<<"¿Que desea realizar?"<<endl;
		cout<<"2. Ingresar asignaturas"<<endl;
		cout<<"3. Editar  asignaturas"<<endl;
		cout<<"4. Eliminar asignaturas"<<endl;
		cout<<"5. Docentes"<<endl;
		cout<<"6. Modulo estudiante"<<endl;
		cout<<"7. Regresar"<<endl;
		cout<<"-----------------------------------------------------"<<endl;
		cout<<"Ingrese la opcion : ";
		cin>>opcion_1;
	}while(!((opcion_1==2)||(opcion_1==3)||(opcion_1==4)||(opcion_1==5)||(opcion_1==6)||(opcion_1==7)));

	switch(opcion_1) {
		case 2:
			/**Añadir materias a la base de datos */

			if(controladorMateria.crearNuevaMateria()==2){
				funcionesAdministrador();
			/**Se envia al administrador al menu anterior*/

			}
			break;
		case 3:
			/**Añadir materias a la base de datos */

			if(controladorMateria.editarMateria()==2){
			/**Se envia al administrador al menu anterior*/
				funcionesAdministrador();
			}
			break;
		case 4:
			if(controladorMateria.eliminarMateria()==2){
				funcionesAdministrador();
			}
			break;		
		case 5:
			/**Se le envia el objeto de controlador materia al controlador docente
			 para asignarle la/s materia/s almacenadas en la BD previamente*/
		
			controladorDocente.setBDBDListaMaterias(BDListaMaterias);
			controladorDocente.setBDListaProfesor(BDListaProfesores);
			/**Se le envia la lista de materias y profesores al controlador docente*/
			controladorDocente.SetcontroladorMateria(controladorMateria);
			if(controladorDocente.menuDocente()==2){
				funcionesAdministrador();
			}
			break;	
		case 6:
			controladorEstudiante.setBDListaGrupoMateria(BDListaGrupoMateria);
			controladorEstudiante.setBDListaEstudiantes(BDListaEstudiantes);
			if(controladorEstudiante.menuControladorEstudiante()==2){
					funcionesAdministrador();
				}
			break;			
		default :
			menuAdministrador();
			break;
	}	
}

