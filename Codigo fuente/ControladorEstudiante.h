#include "Estudiante.h"
#include "BASEDEDATOS.h"
class ControladorEstudiante{
	public :
		static int claveEstudiante;
		ControladorEstudiante(){};
		
	void crearNuevoEstudiante();
	void asignaGrupoMateria();	
	int menuControladorEstudiante();
	void mostrarListaEstudiantes();
	BASEDEDATOS<Estudiante> BDListaEstudiantes;
	BASEDEDATOS<GrupoMateria> BDListaGrupoMateria;
	void setBDListaEstudiantes(BASEDEDATOS<Estudiante> BDListaEstudiantes){ControladorEstudiante::BDListaEstudiantes = BDListaEstudiantes;};
	void setBDListaGrupoMateria(BASEDEDATOS<GrupoMateria> BDListaGrupoMateria){ControladorEstudiante::BDListaGrupoMateria = BDListaGrupoMateria;};
	
};
int ControladorEstudiante::claveEstudiante=1;

int ControladorEstudiante::menuControladorEstudiante(){
	int opcion;
	cout<<"_______MENU CONTROLADOR ESTUDIANTE__________"<<endl;
	cout<<"1. Crear nuevo estudiante"<<endl;
	cout<<"2. Asignar grupo materia a estudiante"<<endl;
	cout<<"3. Regresar. "<<endl;
	cout<<"Ingrese una opcion"<<endl;
	cin>>opcion;
	switch(opcion){
		case 1:
			 crearNuevoEstudiante();
			break;
		case 2:
			break;
		default:
			return 2;
	}
	
}

void ControladorEstudiante::crearNuevoEstudiante(){
	Estudiante estudiante;
	cout<<"__________Ingrese los datos del estudiante_________"<<endl;
	cout<<"Ingrese los nombres del estudiante: ";
	cin>>estudiante.nombresEstudiante;
	cout<<"Ingrese los apellidos del estudiante: ";
	cin>>estudiante.apellidosEstudiante;
	cout<<"Ingrese el codigo del estudiante ";
	cin>>estudiante.codigoEstudiante;
	BDListaEstudiantes.insertar(claveEstudiante,estudiante);
	claveEstudiante++;
	mostrarListaEstudiantes();
	menuControladorEstudiante();	
}

void ControladorEstudiante::mostrarListaEstudiantes(){
	nodo<Estudiante> *nodoEstudiante = BDListaEstudiantes.primero();
	Estudiante estudiante;
	cout<<"______listado estudiantes______"<<endl;
	while(nodoEstudiante->clave!=std::numeric_limits<int>::max()){
		estudiante = nodoEstudiante->info;
		cout<<"Nombres del estudiante   : "<<estudiante.nombresEstudiante<<endl;
		cout<<"Apellidos del estudiante : "<<estudiante.apellidosEstudiante<<endl;
		cout<<"Codigo del estudiante    : "<<estudiante.codigoEstudiante<<endl;
		
	//	cout<<"Grupos que ve el estudiante      : "<<profesor.numTotalClases<<" cursos "<<endl;
		nodoEstudiante = nodoEstudiante->nodoSig;
	}
	cout<<"___________________"<<endl;

}
