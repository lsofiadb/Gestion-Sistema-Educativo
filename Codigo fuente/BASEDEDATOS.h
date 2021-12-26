#ifndef BASEDEDATOS_H
#define BASEDEDATOS_H
#include <iostream>
#include <limits>

using namespace std; 

template <class T>
struct nodo {
    int clave;
    T info;
    nodo <T> *nodoSig;
};

template <class T>
class BASEDEDATOS{
	nodo<T> *cabeza, *limiteclave;
    int tam;

    public: BASEDEDATOS(){
    	cabeza = new nodo <T>;
        limiteclave = new nodo <T>;
        cabeza->nodoSig = limiteclave;
        limiteclave-> nodoSig = limiteclave;
        //Limite de la clave, es el valor maximo almacenado en un dato de tipo entero
        
        limiteclave->clave = std::numeric_limits<int>::max();
        tam = 0;
	}
	
    bool lista_vacia();
    void insertar(int clave, T info); 
	bool borrar(int clave);
	T buscar(int clave);
	bool cambiar(int clave, T infoNueva);
	void mostrarLista(int indice, T *infoRet, int *clave);
	nodo<T> *primero();
	nodo<T> * anterior(int clave);
	nodo<T> *nodoSiguiente(int clave);
	int get_tam(){
		return tam;
	}  
};


template <class T>
bool BASEDEDATOS<T>::lista_vacia()
{if(cabeza->nodoSig ==limiteclave)
    return true;
 else
 	return false;
}

template <class T> 
void BASEDEDATOS <T>::insertar(int clave , T info){
    nodo <T> *ant, *pos;
    ant = cabeza;
    pos = cabeza->nodoSig;

    while (clave > pos->clave){
        ant=pos;
        pos= ant->nodoSig;
    }
    
    if(clave==pos->clave){
    	cout<<"  "<<endl;	
	}else {
		nodo <T> *nuevo;
		nuevo = new nodo <T>;
    	nuevo->clave = clave;
    	nuevo->info = info;
		ant->nodoSig= nuevo;
    	nuevo->nodoSig= pos;
   		tam++;
	} 
}


template <class T>
bool BASEDEDATOS<T>::borrar(int clave){ 
	 nodo <T> *ant, *pos;
	if(lista_vacia()==true){
		cout<<"La lista esta vacia"<<endl;
		return false;
	} else{
		nodo <T> *ant, *pos;
		ant = cabeza;
    	pos = cabeza->nodoSig;
    	while(clave > pos->clave){
    		ant=pos;
        	pos= ant->nodoSig;
		} 
		if(clave==pos->clave){
			ant->nodoSig=pos->nodoSig;
			
			delete pos;
			tam--;
			return true;
		}else{
			cout<<"La clave "<<clave<<" no se encuentra, no se puede elimiteclavenar"<<endl;
			return false;
		}
	}
}


template <class T>
T BASEDEDATOS<T>::buscar(int clave){
	T info;   
	nodo <T> *Aux;
	Aux=cabeza;
	Aux=Aux->nodoSig;
	while(Aux->clave!=clave && Aux!=limiteclave && Aux!=NULL){		
		Aux=Aux->nodoSig;
	}
	if(Aux->clave==clave){
		info=Aux->info;
		return info;
	}
}


template <class T>
bool BASEDEDATOS<T>::cambiar(int clave, T infoNueva){
	nodo <T> *ant, *pos;
	if(lista_vacia()==true){
		cout<<"La lista esta vacia"<<endl;
		return false;
	} else{
		nodo <T> *ant, *pos;
		ant = cabeza;
    	pos = cabeza->nodoSig;
    	while(clave > pos->clave){
    		ant=pos;
        	pos= ant->nodoSig;
		} 
		if(clave==pos->clave){
			pos->info=infoNueva;
			return true;
		}else{
			cout<<"La clave "<<clave<<" no se encuentra, no se puede cambiar la informacion"<<endl;
			return false;
		}
	}

	
}
//Muestra toda la lista
template <class T>
void BASEDEDATOS<T>::mostrarLista(int indice, T *infoRet, int *clave){
	if(lista_vacia()==true){
	cout<<"La lista esta vacia"<<endl;
	} else{
		nodo <T> *aux=cabeza->nodoSig;
		
    	int p = 1;
   		while(p<indice && aux->nodoSig != limiteclave){
	    aux = aux->nodoSig;
        p++;
    	}
    	*infoRet = aux->info;
    	*clave = aux->clave;
		}	
}

//retorna el nodo anterior respecto a la clave
template <class T>
nodo<T> *BASEDEDATOS<T>::anterior(int clave){
	nodo <T> *Aux, *temp;
	Aux=cabeza;
	temp=Aux;
	Aux=Aux->nodoSig;
	while(Aux->clave!=clave && Aux!=limiteclave){		
		temp=Aux;
		Aux=Aux->nodoSig;
	}
	if(Aux->clave==clave && temp!=cabeza){
		return temp;
	}	
}

//retorna el primer nodo de la lista
template <class T>
nodo<T> *BASEDEDATOS<T>::primero(){
	nodo <T> *Aux;
	Aux=cabeza;
	Aux=Aux->nodoSig;
	
	if(Aux!=NULL){
		
		return Aux;
	}else{
		cout<<"--Lista vacia-- \n";
		return NULL;
	}
}

//retorna el nodo nodoSiguiente a la clave que se ingresa
template <class T>
nodo<T> *BASEDEDATOS<T>::nodoSiguiente(int clave){
	nodo <T> *Aux;
	Aux=cabeza;
	Aux=Aux->nodoSig;
	while(Aux->clave!=clave && Aux!=limiteclave){		
		Aux=Aux->nodoSig;
	}
	if(Aux->clave==clave){
		nodo<T> *nuevo = new nodo<T>;
		nuevo = Aux->nodoSig; 
		return nuevo;
	}
}
#endif

