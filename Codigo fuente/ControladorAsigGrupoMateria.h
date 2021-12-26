#include<iostream>
#include "GrupoMateria.h"
using namespace std;
#include <string.h>
#include "Materia.h"
#include "BASEDEDATOS.h"
#include <limits>
#include "ControladorCorte.h"

/**
Controla las diferestes opciones de la lista de Materia
*/
class ControladorAsigGrupoMateria{
	/**Objeto de la clase controlador corte*/
	ControladorCorte controladorCorte;
	public :
		/**Constructor*/
		ControladorAsigGrupoMateria(){
		};	
	/**Crear nuevo grupo materia*/			
	GrupoMateria crearNuevoGrupoMateria(Materia nombreMateria);
	/**Informacion de un grupo de materia a cargo de un profesor*/
	
	void mostrarGrupoMateria(Profesor profesor);
	/**Modificacion de la informacion de una materia a cargo de un profesor*/

	int modificarInformacionXmateria(Profesor profesor);

};


/**
Menu opciones para la materia
*/
void ControladorAsigGrupoMateria::mostrarGrupoMateria(Profesor profesor){
	/**Recupera el primer nodo de la lista de grupos de materias*/
	nodo<GrupoMateria> *nodoGrupoMateria = profesor.listaMateriaDoc.primero();
	/**Estructura para almacenar a la estructura del primer grupo materia del profesor*/

	GrupoMateria grupoMateria;
	/**Recorre la lista de grupo de materia con el apuntador a nodo siguiente que tiene cada nodo*/

	cout<<"_________________Cursos del Profesor_________________"<<endl;
	do{
		grupoMateria = nodoGrupoMateria->info;
		cout<<"Nombre de la Materia    : "<<grupoMateria.nombreGrupoMateria<<endl;
		cout<<"Identificador de la Materia    : "<<grupoMateria.grupoMateria<<endl;
		cout<<"Cortes de la Materia    : "<<grupoMateria.cantidadCorte<<endl;
		nodoGrupoMateria = nodoGrupoMateria->nodoSig;
	}while(nodoGrupoMateria->clave!=std::numeric_limits<int>::max());
	cout<<"_____________________________________________________"<<endl;
}

/**Creacion de un nuevo grupo de materia de acuerdo a la que se envie */

GrupoMateria ControladorAsigGrupoMateria::crearNuevoGrupoMateria(Materia nombreMateria){
	GrupoMateria grupoMateria;
	//-----------------------------------
	//strcpy(<cadena_destino>, <cadena_origen>)
	strcpy(grupoMateria.nombreGrupoMateria, nombreMateria.nombreMateria);
	//--------------------------------
	cout<<"Ingrese el codigo de la asignatura : ";
	cin>>grupoMateria.grupoMateria;
	return grupoMateria;
}




int ControladorAsigGrupoMateria::modificarInformacionXmateria(Profesor profesor){
	/**Muestra la informacion de los cursos a cargo del profesor*/
	mostrarGrupoMateria(profesor);
	GrupoMateria grupoMateria;
	int codigo, opcionCorte,opcion;
	do{
		cout<<"-----------------------------------------------"<<endl;
		cout<<"Ingrese el codigo de la asignatura a modificar: ";
		cin>>codigo;
		/**Busca la materia en la BD de acuerdo a su codigo*/
		grupoMateria=profesor.listaMateriaDoc.buscar(codigo);
		/**Si no la encuentra*/
		if(grupoMateria.grupoMateria==0){
			cout<<"CODIGO INCORRECTO"<<endl;
		}
	}while(grupoMateria.grupoMateria==0);
	cout<<"______________Menu modificacion Materia_______________"<<endl;
	cout<<"-----------------------------------------------"<<endl;
	cout<<"Nombre de la materia: "<<grupoMateria.nombreGrupoMateria<<endl;
	cout<<"Codigo de la materia: "<<grupoMateria.grupoMateria<<endl;
	cout<<"-----------------------------------------------"<<endl;
	do{
		cout<<"1. Modificacion cantidad de cortes"<<endl;	
		cout<<"2. Ingresar informacion por cortes"<<endl;
		cout<<"5. Modulo actividad"<<endl;
		cout<<"6. regresar"<<endl;
		cout<<"-----------------------------------------------"<<endl;
		cout<<"Ingrese una opcion: ";
		cin>>opcion;
		/**Se valida el valor ingresado*/

	}while(!((opcion==1)||(opcion==2)||(opcion==5)||(opcion==6)));	
	cout<<"-----------------------------------------------"<<endl;
	switch(opcion) {
			case 1:
				do{	
					cout<<"1. Modificacion cantidad de cortes"<<endl;
					cout<<"-----------------------------------------------"<<endl;
					cout<<"Ingrese el nuevo numero de cortes : ";
					cin>>opcionCorte;
					cout<<"-----------------------------------------------"<<endl;
				}while(opcionCorte<=0);
				grupoMateria.cantidadCorte = opcionCorte;
				profesor.listaMateriaDoc.cambiar(grupoMateria.grupoMateria,grupoMateria);
				cout<<"Modificacion exitosa =)"<<endl;
				return 2;
				break;
			case 2:
				/**Almacena el grupo materia al que se desea modificar su
					 respectiva informacion por cortes*/
					grupoMateria=profesor.listaMateriaDoc.buscar(codigo);
				/**En caso de no tener cortes se envia al controlador de corte 
					para asignarle los respectivos cortes al grupo materia*/
				
					if(grupoMateria.cantidadCorte!=0){
						controladorCorte.setGrupoMateria(grupoMateria);
						if(controladorCorte.menuCortePorcentaje()==2){
						/**En caso de querer regresar desde el menu de cortePorcentaje a este*/

							modificarInformacionXmateria(profesor);
						}
					}else{
						cout<<"El numero de cortes es nulo"<<endl;
						modificarInformacionXmateria(profesor);
					}
				break;	
			case 5:
				/**Se envia el grupo materia al controlador corte*/
				controladorCorte.setGrupoMateria(grupoMateria);
				/**Se dirige al menu para agregar la informacion de actividades
				 de acuerdo a cada corte del grupo materia*/
					
				if(controladorCorte.ingresarModuloactividades()==2){
					/**En caso de querer regresar a este menu*/					
					modificarInformacionXmateria(profesor);
				}	
				break;		
			default:
			return 2;
	}
	
}
