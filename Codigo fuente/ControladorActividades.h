#include "Corte.h"
#include <iostream>
#include "BASEDEDATOS.h"
#include <limits>
#include "ControladorPuntoTarea.h"

using namespace std;

class ControladorActividades{
	Corte corte;
	ControladorPuntoTarea controladorPuntoTarea;
	
	public :
		/**Identificador de la actividad*/
		static int IdActividad;
		static int IdGrupo;
		/**Constructor*/
		ControladorActividades(){
		};
		/**Muestra la lista de actividades que se tienen por corte*/
		void mostrarTipoActividades();
		int menuOpciones();
		int asignarInformacionXcorte();
		void mostrarInformacionXactividad();
		void asignarPuntosXActividad();
		/**Se asigna el corte que se tiene en esta clase al que se recibe para conservar los datos*/
		void setcorte(Corte corte){ControladorActividades::corte = corte;};
		void editarPuntosActividad();
};
/**Inicializacion del identificador de la actividad autoincremenatable*/
int ControladorActividades::IdActividad = 1;
int ControladorActividades::IdGrupo = 1;

/**Lista de actividades disponibles*/
void ControladorActividades::mostrarTipoActividades(){
	cout<<endl<<"___________Lista Tipo actividades___________"<<endl;
	cout<<"-------------------------------------"<<endl;
	cout<<"1. Quiz"<<endl;
	cout<<"2. Taller"<<endl;
	cout<<"3. Parcial"<<endl;
	cout<<"4. Proyecto"<<endl;
	cout<<"5. Exposicion"<<endl;
	cout<<"6. finalizar"<<endl;
	cout<<"-------------------------------------"<<endl;
}


int ControladorActividades::menuOpciones(){
	int opcion;
	do{
		cout<<"_____________Modulo Actividades por Corte_____________"<<endl;
		cout<<"1. Agregar porcentaje actividades al corte "<<endl;
		cout<<"4. Agregar puntos actividad"<<endl;
		cout<<"5. Editar puntos actividad"<<endl;
		cout<<"7. regresar."<<endl;
		cout<<"--------------------------------------------------------"<<endl;
		cout<<"Ingrese la opcion : ";
		cin>>opcion;
		cout<<"--------------------------------------------------------"<<endl;
	}while(!((opcion==1)||(opcion==4)||(opcion==5)||(opcion==7)));
	
	switch(opcion) {
		case 1:
			if(asignarInformacionXcorte()==2){
				menuOpciones();
			}
			break;
		case 4:
			asignarPuntosXActividad();
			break;
		case 5:
			editarPuntosActividad();
			break;							
		default:
			return 2;
		}
}
/**Se agrega informacion por corte*/
int ControladorActividades::asignarInformacionXcorte(){
	cout<<"___________________________________________________"<<endl;
	cout<<"1) Agregar los porcentajes del corte"<<endl;
	
	int acumulador=0,j=0;
	int porcentaje;
	/**	Arreglo de tipos de actividades */
	Actividad actividad[5];
	/**Muestra los tipos disponibles*/
	mostrarTipoActividades();
	
	/**Muestra el porcentaje limite del corte que fue asignado previamente*/
	cout<<"Recordar porcentaje total del corte es : "<<corte.porcentajeCorte<<"%"<<endl;
	do{/**Informacion del numero de actividades a realizar en el corte con sus respectivos porcentajes*/
		cout<<"Seleccione una actividad para el corte : ";
		cin>>actividad[j].tipoActividad;
		
		cout<<"Ingrese porcentaje total que coresponde al mismo tipo de actividad "<<actividad[j].tipoActividad<<" en el corte : ";
		cin>>actividad[j].porcentajeAct;
		
		cout<<"Ingrese el numero total de veces que se realizara la actividad "<<actividad[j].tipoActividad<<" :";
		cin>>actividad[j].repeticionActividad;
		
		
		acumulador = acumulador + actividad[j].porcentajeAct;
		j++;
		
	}while((acumulador<corte.porcentajeCorte)&&(j<5));	
	/**Validacion*/
	if(acumulador!=corte.porcentajeCorte){
		cout<<"El porcentaje no concuerda =("<<endl;
				/**Le hace repetir el proceso nuevamente*/
		asignarInformacionXcorte();
	}else{
		/**Inserta la lista de actividades a cada corte*/
		for(int x=0; x<j; x++){
			actividad[x].claveActividad = IdActividad;
			
			corte.listActDifXCor.insertar(IdActividad,actividad[x]);
			IdActividad++;
		}
	}
	//setcorte(corte);
	/**Muestra la informacion por actividad*/
	mostrarInformacionXactividad();	
	return 2;
}
/**Muestra la informacion de las actividades de cada corte */
void ControladorActividades::mostrarInformacionXactividad(){
	/**nodo que contiene el primer nodo de la BD de actividades por corte**/
	cout<<"_________________Informacion general de las actividades_________________"<<endl;
	nodo<Actividad> *nodoCorte = corte.listActDifXCor.primero();
	Actividad actividad;
	/**Validacion*/
	if(nodoCorte->clave==numeric_limits<int>::max()){
		cout<<"No hay informacion almacenada"<<endl;
	}
	cout<<"------------------------------------------------------------------------"<<endl;
	while(nodoCorte->clave!=std::numeric_limits<int>::max()){
		/**Almacena la actividad del nodo del corte*/

		actividad = nodoCorte->info;
		cout<<"Identificador de la actividad : "<<actividad.claveActividad<<endl;
		cout<<"Porcentaje de la actividad : "<<actividad.porcentajeAct<<endl;
		cout<<"Clasificacion de la actividad : "<<actividad.tipoActividad<<endl;
		cout<<"Asignacion del numero de veces a realizar la actividad : "<<actividad.repeticionActividad<<endl;
		nodoCorte  = nodoCorte->nodoSig;
		cout<<"------------------------------------------------------------------------"<<endl;
	}
}


void ControladorActividades::asignarPuntosXActividad(){
	int opcion;
	Actividad actividad;
	do{
		cout<<"__________Modulo puntos actividad__________"<<endl;
		mostrarInformacionXactividad();
		cout<<"-----------------------------------------------------------"<<endl;
		cout<<endl<<"Ingrese la clave de la actividad a modificar :"<<endl;
		cin>>opcion;
		cout<<"-----------------------------------------------------------"<<endl;
		actividad=corte.listActDifXCor.buscar(opcion);
	}while(actividad.claveActividad==0);
	
		if(actividad.repeticionActividad!=0){
			for(int j=0; j<actividad.repeticionActividad;j++){
				//------------------------
				
				actividad.listaTareasXAct.insertar(IdGrupo,controladorPuntoTarea.crearTarea());
				cout<<"________Se ingreso exitosamente________"<<endl;
				IdGrupo++;
				//------------------------
			}
		}else{
			cout<<"Asigne el porcentaje de la actividad primero"<<endl;	
		}
	
	menuOpciones();
}
void ControladorActividades::editarPuntosActividad(){
	int opcion;
	Actividad actividad;
	do{
		cout<<"__________Modulo actualizar actividad__________"<<endl;
		mostrarInformacionXactividad();
		cout<<"-----------------------------------------------------------"<<endl;
		cout<<endl<<"Ingrese la clave de la actividad a modificar :"<<endl;
		cin>>opcion;
		cout<<"-----------------------------------------------------------"<<endl;
		actividad=corte.listActDifXCor.buscar(opcion);
	}while(actividad.claveActividad==0);
	
	BASEDEDATOS< BASEDEDATOS< Tarea > > listaTareasXAct;
	BASEDEDATOS< Tarea >  listaTareasXAct_2;
 	nodo<BASEDEDATOS < Tarea > > *listaPuntosPorCorte; 
	
	listaPuntosPorCorte = actividad.listaTareasXAct.primero();
	
	cout<<"ID lista de puntos "<<endl;
	while(listaPuntosPorCorte->clave!=std::numeric_limits<int>::max()){
		cout<<" ID : "<<listaPuntosPorCorte->clave;
		listaPuntosPorCorte= listaPuntosPorCorte->nodoSig;
	}
	opcion=0;
	do{
		cout<<endl<<"Ingrese la clave de la lista de puntos :"<<endl;
		cout<<"-----------------------------------------------------------"<<endl;
		cin>>opcion;
		listaTareasXAct_2 = actividad.listaTareasXAct.buscar(opcion);
	}while(listaTareasXAct_2.primero()->clave==std::numeric_limits<int>::max());
		actividad.listaTareasXAct.cambiar(opcion,controladorPuntoTarea.crearTarea());
		cout<<"________Se actualizo exitosamente________"<<endl;
		menuOpciones();
}
