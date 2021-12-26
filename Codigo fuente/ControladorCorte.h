#include "Corte.h"
#include <conio.h>
#include <iostream>
#include "BASEDEDATOS.h"
#include <limits>
#include "GrupoMateria.h"
#include "ControladorActividades.h"

//ControladorAsigGrupoMateria.h
using namespace std;
/**
Controla las diferestes opciones ------------------------
*/

class ControladorCorte{
	/**Grupo materia sobre el cual se realizaran los respectivos cambios*/
	
	GrupoMateria grupoMateria;
	/**Objeto del controlador de actividades*/
	
	ControladorActividades controladorActividades;
	public :
		/**Identificador del corte en la BD*/
	
		static int IDcorte;
		/*Constructor*/
		ControladorCorte(){	
		};
		/*Menu para asignar el porcentaje de cada corte*/
			
		int menuCortePorcentaje();
		void mostrarPorcentajesCortes();
		int ingresarModuloactividades();
		/**Asigna el grupo materia que se define en esta clase al que se recibe para conservar la informacion respectiva*/
		void setGrupoMateria(GrupoMateria grupoMateria){ControladorCorte::grupoMateria = grupoMateria;}
		
};
/**Inicializacion del Identificador del corte autoincrementable*/

int ControladorCorte::IDcorte=1;

int ControladorCorte::menuCortePorcentaje(){
		Corte corte;//Se declara global para usarla en ambos ciclos for
		int x,acumulador;
		/**Arreglo que almacenara los porcentajes de los cortes*/

		int porcentajes[grupoMateria.cantidadCorte];
		do{
			acumulador=0;
			for(x=0; x<grupoMateria.cantidadCorte;x++){
				cout<<"________________Datos del corte________________"<<endl;
				cout<<"Ingrese el porcentaje para el corte numero "<<(x+1)<<" : ";
				cin>>porcentajes[x];
				/**Ira almacenando la suma total del porcentaje de los cortes*/
				acumulador=acumulador+porcentajes[x];
			}
			if(acumulador!=100){//Validacion
				cout<<"Los porcentajes no concuerdan, la sumatoria debe ser 100%";
			}
		}while(acumulador!=100);
		//Asigna la informacion a cada uno de los cortes con el arreglo que almacena los porcentajes
	
		for(x=0; x<grupoMateria.cantidadCorte;x++){
				corte.claveCorte = IDcorte;
				corte.numCorte = (x+1);
				corte.porcentajeCorte = porcentajes[x];
				grupoMateria.listaCortesXAsig.insertar(corte.claveCorte,corte);
				IDcorte++;
			}
		cout<<"Se realizo el registro correctamente"<<endl;	
		/**Se muestra la respectiva informaicion de los cortes*/

		mostrarPorcentajesCortes();
		/**Para regresar al menu anterior*/
		return 2;
	
}
/**Muestra la lista de los porcentajes de los cortes de acuerdo a la BD*/
void ControladorCorte::mostrarPorcentajesCortes(){
	nodo<Corte> *nodoCorte = grupoMateria.listaCortesXAsig.primero();
	Corte corte;
	cout<<"____________Informacion de los cortes____________"<<endl;
	while(nodoCorte->clave!=std::numeric_limits<int>::max()){
		corte = nodoCorte->info;
		cout<<"Clave  del corte     : "<<corte.claveCorte<<endl;
		cout<<"Numero del corte     : "<<corte.numCorte<<endl;
		cout<<"Porcentaje del corte : "<<corte.porcentajeCorte<<endl;
		/**Corrimiento al siguiente nodo en la BD*/	
		nodoCorte = nodoCorte->nodoSig;
		cout<<"--------------------------------------------------"<<endl;
	}
		cout<<"___________________________________________________"<<endl;
}
/**Modulo de actividades por cada corte*/

int ControladorCorte::ingresarModuloactividades(){
	int opcion;
	Corte corte_1;
	nodo<Corte> *nodoCorte = grupoMateria.listaCortesXAsig.primero();
	/**Verifica que se encuentren cortes asignados al grupo materia*/

	if( nodoCorte->clave==std::numeric_limits<int>::max()){
		cout<<"--------------------------------------------------"<<endl;
		cout<<"NO HAY INFORMACION =(, INGRESE LA INFORMACION DE LOS CORTES"<<endl;
		cout<<"--------------------------------------------------"<<endl;
		return 2;
	}else{
	/**Muestra los porcentajes de cada uno de los cortes del grupo materia*/

		mostrarPorcentajesCortes();
	//= grupoMateria
		do{
			/**Se va agregando la informacion de acuerdo a la clave del corte*/
	
			cout<<"Ingrese la clave del corte :"<<endl;
			cin>>opcion;
			cout<<"--------------------------------------------------"<<endl;
			corte_1 = grupoMateria.listaCortesXAsig.buscar(opcion);
			/**Validacion de que existan corte/cortes registrados en la BD*/

			if(corte_1.claveCorte==0){
				cout<<"Clave erronea =("<<endl;
			}	
		}while(corte_1.claveCorte==0);
		/**Lo dirige al controlador de actividades enviandole la informacion del corte y el grupo de la materia que esta modificando*/
	
		controladorActividades.setcorte(grupoMateria.listaCortesXAsig.buscar(opcion));
		/**Lo dirige al menu principal*/
		
		controladorActividades.menuOpciones();
	}
}
