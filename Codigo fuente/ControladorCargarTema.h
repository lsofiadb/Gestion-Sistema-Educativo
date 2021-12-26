#include<iostream>
#include "BASEDEDATOS.h"
#include <fstream>
#include <string.h>
#include <string>
#include <limits>
#include<sstream>  
//Estructuras
#include "Profesor.h"
#include "Materia.h"
#include "Actividad.h"
#include "Corte.h"
#include "GrupoMateria.h"
#include "Tarea.h"
#include "Tema.h"

using namespace std;
/**
*Persistencia de Tema
*/
class ControladorCargarTema{
	
	public :
		ControladorCargarTema(){
		};	
	

	void cargarDatosTema(BASEDEDATOS<Tema>  listTema);
	
};



void ControladorCargarTema::cargarDatosTema(BASEDEDATOS<Tema>  listTema){
	nodo<Tema> nT;
	
	//Se abre el archivo
	//Nodo de la funcion
	ifstream fileTema( "Temas.bin", ios::binary);
	if (fileTema.is_open()){
		fileTema.read( (char *) &nT, sizeof(nT));
		while( !fileTema.eof()) {
			//Inserta en la lista de la función
			listTema.insertar(nT.clave,nT.info);
			fileTema.read( (char *) &nT, sizeof(nT));
		}
	} else cout << "Error de apertura de archivo." << endl;
}
