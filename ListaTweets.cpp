#include "ListaTweets.h"
#include<iostream>
using namespace std;

Lista::Celda::Celda(char * usuario, int cantidadMenciones){
	anterior = 0;
	siguiente = 0;
	abajo = 0;
	this->usuario = usuario;
	this->cantidadMenciones = cantidadMenciones;
}

void Lista::Celda::liberadorColumnas( ){
	if(abajo){
		delete abajo;
	}
}

Lista::Celda::~Celda(){
	while(!siguiente){
		delete siguiente;
	}
}

ostream & Lista::Celda::imprimir(ostream & salida, int cuantasMenciones){
	if(abajo && cuantasMenciones){
		salida << " Usuario Mencionado: " << abajo->usuario<<endl;
		salida << " Cantidad de Menciones: " << abajo->cantidadMenciones << endl;
		abajo->imprimir(salida, cuantasMenciones-1);
	}
	return salida;
}

Lista::Lista(){
  primera = 0;
  ultima = 0;
}

Lista::~Lista(){
	Celda * actual = primera;
	if(actual){
	actual->liberadorColumnas();
	actual = actual->siguiente;
	}
	if(primera){
		delete primera;
	}
}

Lista & Lista::pushFront(char * nuevo_Usuario, int cantidadMenciones){
    Celda * nueva = new Celda(nuevo_Usuario, cantidadMenciones);
    nueva->siguiente = primera;
    if(primera){ // SE VA A COLAR ANTES DEL QUE ESTA DE PRIMERO
		primera->anterior = nueva;
	}
	else { // LISTA ESTA VACIA
		ultima = nueva;
	}
	primera = nueva;
	cout<<" Se inserto "<< primera->usuario<<endl;
}

Lista & Lista::pushBack(char * nuevo_Usuario, int cantidadMenciones){
	Celda * nueva = new Celda(nuevo_Usuario, cantidadMenciones);
	nueva->anterior = ultima;
	if(ultima){
	   ultima->siguiente = nueva;
	}
	else {
		primera = nueva;
	}
	ultima = nueva;
	cout<<" Se inserto "<< ultima->usuario <<endl;
}

int Lista::compararNombres(char * usuarioA, char * usuarioB){
	int sonIguales = 1;
	int palabrasComparadas = 0;
	int i = 0;
	while(!palabrasComparadas){
		if(*(usuarioA + i) != *(usuarioB + i)){
			sonIguales = 0;
			palabrasComparadas = 1;
		}
		if(sonIguales && (*(usuarioA + i) =='\0') && (*(usuarioB + i) == '\0') ){
			palabrasComparadas = 1;
		}	
		++i;
	}
	return sonIguales;
}

int Lista::existeEscritor(char * usuarioBuscado){
	int pos = -1;
	int encontrado = 0;
	Celda * actual = primera;
	if(actual){
	   int i = -1;
	   while(!encontrado && actual){
         ++i;
		 encontrado = compararNombres(actual->usuario, usuarioBuscado);
         actual = actual->siguiente;
	   }
	}
	else {
	  cerr << "Advertencia: <<Lista vacía>> Se retorna un valor de -1 por omisión"<<endl;
	}
	return encontrado;
  }

int Lista::existeMencion(char * escritor, char * mencion){
	int existe = 0;
	if(!existeEscritor(escritor)){
  	cerr << "Advertencia: Escritor de tweets enviado no existe en la Lista";
	}
	else{
  	Celda * actual = primera;
		while(!compararNombres(escritor,actual->usuario)){
	  	actual = actual->siguiente;
		}
		if(actual->abajo){
			actual=actual->abajo;
			while(actual && !existe){
      	existe = compararNombres(actual->usuario, mencion);
				if(existe){
					actual->cantidadMenciones+=1;
					cout<< " Se inserto mencion repetida: "<< actual->usuario <<"  Cant. Menciones: "<< actual->cantidadMenciones << endl;
				}
				actual = actual->abajo;
			}
		}
	}
	return existe;
}

Lista &  Lista::insertar(char * usuarioBuscado, int cantidadMenciones){
	if(!primera){
			pushFront(usuarioBuscado, cantidadMenciones);
		}
		else {
			if(!existeEscritor(usuarioBuscado)){
				pushBack(usuarioBuscado, cantidadMenciones);
			}
			   }
	return *this;
	}

Lista &  Lista::insertarMencion(char * escritor, char * mencion){
	if(!existeMencion(escritor,mencion)){
  	Celda * actual = primera;
	  	int encontroEscritor = 0;
		Celda * anteriorPrincipal = 0;
		while(!encontroEscritor){
			encontroEscritor = compararNombres(escritor,actual->usuario);
			anteriorPrincipal = actual;
			actual = actual->siguiente;
		}
		actual = anteriorPrincipal;
		Celda * Nueva = new Celda(mencion, 1);
    if(!actual->abajo){
			actual->abajo = Nueva;
			cout<< " Se inserto mencion: "<< actual->abajo->usuario<<endl;
		}
	  else{
			actual = actual->abajo;
			Celda * anterior = 0;
			while(actual){
				anterior = actual;
				actual = actual->abajo;
			}
			anterior->abajo = Nueva;
			cout<< " Se inserto mencion: "<< anterior->abajo->usuario<<endl;
		}
	}
	return *this;
}

void Lista::ordenarLista(){
	Celda * principal = primera; // Principal me ayudará a moverme a través de la lista en forma Horizontal, o sea moviendome a través de los escritores de tweets
	while (principal) {
    	if(principal->abajo){
				Celda * indiceColumnas = principal->abajo;
				int cantSubCeldas = 0;
				while(indiceColumnas){ // Cuenta la cantidad de Celdas hacía abajo de cada escritor
					++cantSubCeldas;
					indiceColumnas = indiceColumnas->abajo;
				}
				indiceColumnas = principal->abajo; // Reiniciando el puntero a la primera celda de mención
				int maximo; // Guarda la que se asume como la cant máxima de menciones
        Celda * celdaPorComparar_01; // Será un puntero que deberá apuntar al elemento que inicialmente tendrá las menciones que se asumen como máximo.
				// Siempre apuntará al elemento "i" inicial de forma fija en cada vuelta en el primer ciclo de adelante
				Celda * celdaPorComparar_02; // Va a servir para en caso de encontrar una celda con un numero de menciones mayor al supuesto "maximo" apuntarle a esa celda;
				for(int i = 0; i < cantSubCeldas-1; ++i){
					celdaPorComparar_01 = indiceColumnas;
					celdaPorComparar_02 = 0;
					maximo = celdaPorComparar_01->cantidadMenciones;
						for(int j = i+1; j < cantSubCeldas && indiceColumnas->abajo; ++i){
							if(indiceColumnas->siguiente->cantidadMenciones > maximo){ // Intercambio a nuevo máximo si alguien tiene más menciones
								celdaPorComparar_02 = indiceColumnas->abajo;
								maximo = indiceColumnas->abajo->cantidadMenciones;
							}
						}
						if(celdaPorComparar_02){ // se entra Sii se encontró a alguien con más menciones que la celdaPorComparar_01
							Celda *temporal = new Celda(celdaPorComparar_01->usuario, celdaPorComparar_01->cantidadMenciones);
							celdaPorComparar_01->usuario = celdaPorComparar_02->usuario;
							celdaPorComparar_01->cantidadMenciones = celdaPorComparar_02->cantidadMenciones;
							celdaPorComparar_02->usuario = temporal->usuario;
							celdaPorComparar_02->cantidadMenciones = temporal->cantidadMenciones;
							delete temporal;
						}
						indiceColumnas = indiceColumnas->abajo;
				} //Ciclo que inicia el ordenamiento propiamente
			}
			principal = principal->siguiente;
	}
}

ostream & Lista::imprimir( ostream & salida, char * escritor, int cuantasMenciones){
	if(primera){
		Celda * actual = primera;
		int escritorEncontrado = 0;
		Celda * anterior = 0;
		while(!escritorEncontrado && actual){
			if(compararNombres(escritor,actual->usuario)){
				escritorEncontrado = 1;
				salida << " Usuario Principal: " << actual->usuario<<endl;
			}	
			anterior = actual;
			actual = actual->siguiente;
		}
		actual = anterior;
		if(escritorEncontrado){	
			actual->imprimir(salida, cuantasMenciones);
			cout<< "***************************************************\n";
		}
	}
	else {
		cout << "Advertencia: NO se puede imprimir una lista vacia"<<endl;
	}
	return salida;
}
