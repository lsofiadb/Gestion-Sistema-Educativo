#include<iostream>
#include <limits>
#include "Tema.h"
#include "BASEDEDATOS.h"

using namespace std;

//Controlador ingreso Temas
class ControladorTema{
	BASEDEDATOS<Tema> bdTemas;
	public :
		static int claveTema;
		//static int claveTema;
		ControladorTema(){
		};		
		void ingresarTemario();
		void mostrarTemario();
		
		void setBDListaTemas(BASEDEDATOS<Tema> bdTemas){ControladorTema::bdTemas = bdTemas;};
};
int ControladorTema::claveTema = 1;

//---------------------------------------------------
void  ControladorTema::ingresarTemario(void){
	Tema tema;
	int cantidadTemas;
	
	cout<<endl<<"___________________Temas_____________________"<<endl;
	cout<<endl<<"Ingrese la cantidad de temas : ";
	cin>>cantidadTemas;
	cout<<endl;
	for(int i=0; i<cantidadTemas; i++){
		cout<<"Tema "<<(i+1)<<endl;
		cout<<"Ingrese el nombre del tema : ";
		cin>>tema.nombreTema;
		cout<<"Ingrese el indice del tema : ";
		cin>>tema.indiceTema;
		//----------------------------------
		tema.codigoTema = claveTema;
		//----------------------------------
		bdTemas.insertar(tema.codigoTema, tema);
		claveTema++;
	}
	mostrarTemario();
}
//---------------------------------------------------
void  ControladorTema::mostrarTemario(){
	Tema tema;
	//obtiene la clave del primer tema
	int primerClaveTema = bdTemas.primero()->clave;
	cout<<endl<<"___________________Mostrando Temario_____________________"<<endl;
	if(primerClaveTema==std::numeric_limits<int>::max()){
		cout<<"No a registrado temas =("<<endl;
		ingresarTemario();
	}
	cout<<"----------------------------"<<endl;
	while(primerClaveTema!=std::numeric_limits<int>::max()){
		tema = bdTemas.buscar(primerClaveTema);
		cout<<"Clave         :"<<tema.codigoTema;
		cout<<endl<<"Nombre tema   :"<<tema.nombreTema;
		cout<<endl<<"Indice        :"<<tema.indiceTema;
		primerClaveTema=bdTemas.nodoSiguiente(primerClaveTema)->clave;
		cout<<endl;
		cout<<"----------------------------"<<endl;
	}
}
//---------------------------------------------------------------


