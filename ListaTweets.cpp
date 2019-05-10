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

//@Descripcion:Libera la memoría en caso de que una celda tenga punteros a celdas hacía "abajo" de ella
void Lista::Celda::liberadorColumnas( ){
	if(abajo){
		delete abajo;
	}
}

//@Descripcion: Libera la memoria usada por las celdas en caso de que existan
Lista::Celda::~Celda(){
	if(siguiente){
		delete siguiente;
	}
}

//@Descripcion: El imprimir de celda, se usa para imprimir los usuarios mencionados por otro, en este caso imprime las celdas que están hacía abajo de una celda principal.
//@param: Tipo ostream y nombre salida, se usa para manejar el flujo de salida de los datos
//@param: Tipo int y nombre cuantasMenciones , se usa para saber cuantas menciones hechas por el escritor debo imprimir
//@return: Se retorna un objeto ostream por referencia, que me permite continuar el manejo del flujo de salida a través de otro metodo externo.
ostream & Lista::Celda::imprimir(ostream & salida, int cuantasMenciones){
	if(abajo && cuantasMenciones){
		salida << " Usuario Mencionado: " << abajo->usuario;
		salida << " Cantidad de Menciones: " << abajo->cantidadMenciones << endl;
		abajo->imprimir(salida, cuantasMenciones-1);
	}
	return salida;
}

Lista::Lista(){
  primera = 0;
  ultima = 0;
}
//@Descripcion: Libera la memoria que usan las celdas de la lista
Lista::~Lista(){
	Celda * actual = primera;
	if(actual){
	while(actual){
		actual->liberadorColumnas(); // Para cada celda de la fila principal, se revisa si tiene celdas hacía abajo a traves de liberadorColumnas() y de ser así se borran
		actual = actual->siguiente;
	  }
	}
	if(primera){ // Libera la memoria de las celdas de la fila principal propiamente
		delete primera;
	}
}

//@Descripcion: Crea una nueva celda y la pone de primera en la lista
//@param: Tipo char* y nombre nuevo_Usuario , me da el nombre del nuevo usuario a insertar
//@param:Tipo int y nombre cantidadMencionesRecibidadas, indica la cantidad de Menciones que tiene cada usuario con respecto a otro , en este caso zl escritor se le pasa 0 por omision, se le deja con el fin de volver el metodo más reutilizable.
//@return: Retorna una Lista por referencia, eso permite que el metodo se pueda usar de forma encadenada
Lista & Lista::pushFront(char * nuevo_Usuario, int cantidadMencionesRecibidadas){
    Celda * nueva = new Celda(nuevo_Usuario, cantidadMencionesRecibidadas );
    nueva->siguiente = primera;
    if(primera){ // SE VA A COLAR ANTES DEL QUE ESTA DE PRIMERO
		primera->anterior = nueva;
	}
	else { // LISTA ESTA VACIA
		ultima = nueva;
	}
	primera = nueva;
	//cout<<" Se inserto "<< primera->usuario<<endl; Se puede usar para verificar que se están insertando los usuarios
	return *this;
}

//@Descripcion: Crea una nueva celda y la pone de ultima en la lista
//@param: Tipo char* y nombre nuevo_Usuario , me da el nombre del nuevo usuario a insertar
//@param:Tipo int y nombre cantidadMencionesRecibidadas, indica la cantidad de Menciones que tiene cada usuario con respecto a otro , en este caso zl escritor se le pasa 0 por omision, se le deja con el fin de volver el metodo más reutilizable.
//@return: Retorna una Lista por referencia, eso permite que el metodo se pueda usar de forma encadenada
Lista & Lista::pushBack(char * nuevo_Usuario, int cantidadMencionesRecibidadas){
	Celda * nueva = new Celda(nuevo_Usuario, cantidadMencionesRecibidadas);
	nueva->anterior = ultima;
	if(ultima){
	   ultima->siguiente = nueva;
	}
	else {
		primera = nueva;
	}
	ultima = nueva;
	//cout<<" Se inserto "<< ultima->usuario <<endl; // Se puede usar para verificar que se están insertando los usuarios
	return *this;
}
//@Descripcion:Compara dos nombres para saber si son iguales
//@param: usuarioA de tipo char * , es la variable que le apunta al nombre que voy a comparar con otro.
//@param: usuarioB de tipo char * , es la variable que le apunta al nombre que voy a comparar con otra
//@return: Retorna un entero que me indica si el nombre de ambos usuarios es igual, 1 si es cierto 0 si es falso
int Lista::compararNombres(char * usuarioA, char * usuarioB){
	int sonIguales = 1;
	int palabrasComparadas = 0;
	int i = 0;
	while(!palabrasComparadas){
		if(*(usuarioA + i) != *(usuarioB + i)){ //Compara caracter por caracter de ambos usuarios
			sonIguales = 0;
			palabrasComparadas = 1;
		}
		if(sonIguales && (*(usuarioA + i) =='\0') && (*(usuarioB + i) == '\0') ){ // Este if sirve para revisar si dos usuarios sonIguales y ambos ya acabaron sus caracteres o sea llegaron al caraccter '\0'.
			palabrasComparadas = 1; // Me hace salir del while                                                //
		}
		++i;
	}
	return sonIguales;
}

//@Descripcion:Sirve para verificar si una escritor de tweets ya está dentro de la lista
//@param: usuarioBuscado es un char* que apunta al nombre del usuario que quiero revisar si ya esta en la lista
//@return: Retorna un int que tendrá el valor 1 si ya existe el usuario, si no existe 0.
int Lista::existeEscritor(char * usuarioBuscado){
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
	  cerr << "Advertencia: <<Lista vacía>> Se retorna un valor de 0 por omision"<<endl;
	}
	return encontrado;
  }

//@Descripcion:Sirve para verificar si una mencion hecha por un usuario ya está dentro de la lista
//@param: escritor es un char* que apunta al nomre del que escribió la mencion, sirve oara ubicarlo en la lista
//@param: escritor es un char* que apunta al nombre de la mencion que se va a verificar si ya ha sido hecha
//@return: Retorna un int que tendrá el valor 1 si ya existe el usuario, si no existe 0.
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
					actual->cantidadMenciones+=1; // Si la mención ya existe le suma 1 a su contador de menciones
					//cout<< " Se inserto mencion repetida: "<< actual->usuario <<"  Cant. Menciones: "<< actual->cantidadMenciones << endl;
					//El cout anterior Puede funcionar si se quiere probar que efectivamente las menciones repetidas están siendo insertadas
				}
				actual = actual->abajo;
			}
		}
	}
	return existe;
}

//@Descripcion: Inserta un usuario escritor de tweets en la lista, si no existe ya en la misma
//@param: Tipo char* y nombre usuarioBuscado , me da el nombre del nuevo usuario a insertar
//@param:Tipo int y nombre cantidadMencionesRecibidadas, indica la cantidad de Menciones que tiene cada usuario con respecto a otro , en este caso zl escritor se le pasa 0 por omision, se le deja con el fin de volver el metodo más reutilizable.
//@return: Retorna una Lista por referencia, eso permite que el metodo se pueda usar de forma encadenada
Lista &  Lista::insertar(char * usuarioBuscado, int cantidadMencionesRecibidadas){
	if(!primera){
			pushFront(usuarioBuscado, cantidadMencionesRecibidadas);
		}
		else {
			if(!existeEscritor(usuarioBuscado)){
				pushBack(usuarioBuscado, cantidadMencionesRecibidadas);
			}
			   }
	return *this;
	}

//@Descripcion: Inserta una mencion hecha por un usuario en la lista
//@param: Tipo char* y nombre escritor , me da el nombre del usuario que escribio la mención a insertar
//@param: Tipo char* y nombre mencion , me da el nombre de la mencion a insertar en la lista
//@return: Retorna una Lista por referencia, eso permite que el metodo se pueda usar de forma encadenada
Lista &  Lista::insertarMencion(char * escritor, char * mencion){
	if(!existeMencion(escritor,mencion) && existeEscritor(escritor)){
  	Celda * actual = primera;
	  	int encontroEscritor = 0;
		Celda * anterior = 0; // Este puntero le va a quedar apuntando a la celda que tiene el escritor que estoy buscando, ya que actual luego del while estará apuntando a la siguiente de anterior
		while(!encontroEscritor){
			encontroEscritor = compararNombres(escritor,actual->usuario);
			anterior = actual;
			actual = actual->siguiente;
		}
		actual = anterior;
		anterior = 0;
		Celda * Nueva = new Celda(mencion, 1);
    if(!actual->abajo){
			actual->abajo = Nueva;
			// cout<< " Se inserto mencion: "<< actual->abajo->usuario<<endl;
			//El cout puede ayudar a revisar que las menciones si se están insertando
		}
	  else{
			actual = actual->abajo;
			while(actual){
				anterior = actual;
				actual = actual->abajo;
			}
			anterior->abajo = Nueva;
			//cout<< " Se inserto mencion: "<< anterior->abajo->usuario<<endl;
			//El cout puede ayudar a revisar que las menciones si se están insertando
		}
	}
	return *this;
}

//@Descripcion: Ordena la lista en forma decreciente, se usa un algoritmo de seleccion adaptado a esta estructura de datos
void Lista::ordenarLista(){
	Celda * principal = primera; // Principal me ayudará a moverme a través de la lista en forma Horizontal, o sea moviendome a través de los escritores de tweets
	while (principal) {
		cout<<"entra al while hay primera \n";
      cout<<"principal es:"<< principal->usuario<<endl;
    	if(principal->abajo){ cout<< "Hay alguien abajo de principal \n";
				Celda * indiceColumnas = principal->abajo;
				int cantSubCeldas = 0;
				while(indiceColumnas){ // Cuenta la cantidad de Celdas hacía abajo de cada escritor
					++cantSubCeldas;
					indiceColumnas = indiceColumnas->abajo;
				}
				cout << "cantidad de menciones de: "<< principal->usuario<< " "<< cantSubCeldas<<endl;
				indiceColumnas = principal->abajo; // Reiniciando el puntero a la primera celda de mención
				int maximo; // Guarda la que se asume como la cant máxima de menciones
        Celda * celdaPorComparar_01; // Será un puntero que deberá apuntar al elemento que inicialmente tendrá las menciones que se asumen como máximo.
				// Siempre apuntará al elemento "i" inicial de forma fija en cada vuelta en el primer ciclo de adelante
				Celda * celdaPorComparar_02; // Va a servir para en caso de encontrar una celda con un numero de menciones mayor al supuesto "maximo" apuntarle a esa celda;
				for(int i = 0; i < cantSubCeldas-1; ++i){ cout<< "entra al for 1 vuelta  "<<i<<endl;
					celdaPorComparar_01 = indiceColumnas; cout<<"CXComp 1 es : "<< celdaPorComparar_01->usuario<<endl;
					celdaPorComparar_02 = 0;
					maximo = celdaPorComparar_01->cantidadMenciones; cout<<"CXComp 1 menciones son : "<< celdaPorComparar_01->cantidadMenciones<<endl;
						for(int j = i+1; j < cantSubCeldas && indiceColumnas->abajo; ++j){ cout<<"entro al for 2 \n";
							if(indiceColumnas->abajo->cantidadMenciones > maximo){ // Intercambio a nuevo máximo si alguien tiene más menciones
								celdaPorComparar_02 = indiceColumnas->abajo;cout<<"CXComp 2 es : "<< celdaPorComparar_02->usuario;
								maximo = indiceColumnas->abajo->cantidadMenciones; cout<<"CXComp 2 emenciones son : "<< maximo<<endl;
							}
						}
						if(celdaPorComparar_02){ // se entra Sii se encontró a alguien con más menciones que la celdaPorComparar_01
							cout<< "hay celda por comparar 2 \n";
							Celda *temporal = new Celda(celdaPorComparar_01->usuario, celdaPorComparar_01->cantidadMenciones);
							cout<< " se crea nueva celda \n";
							celdaPorComparar_01->usuario = celdaPorComparar_02->usuario;
							cout<<"celdaPorComparar_01->usuario = celdaPorComparar_02->usuario\n";
							celdaPorComparar_01->cantidadMenciones = celdaPorComparar_02->cantidadMenciones;
							cout<<"celdaPorComparar_01->cantidadMenciones = celdaPorComparar_02->cantidadMenciones; \n";
							celdaPorComparar_02->usuario = temporal->usuario;
							cout<<"celdaPorComparar_02->usuario = temporal->usuario;\n";
							celdaPorComparar_02->cantidadMenciones = temporal->cantidadMenciones;
							cout<<"celdaPorComparar_02->cantidadMenciones = temporal->cantidadMenciones;\n";
							delete temporal; cout <<"borra temporal\n";
						}
						indiceColumnas = indiceColumnas->abajo; cout<< "NUevo indice columnas :" <<indiceColumnas->usuario<<endl;
				}
			}
			cout<<"sale del for grande";
			principal = principal->siguiente;

			if(principal){cout<< "principal ahora es "<<principal->usuario<<endl; }
	}
}

//@Descripcion: Imprime un usuari de la lista, si esta en ella, y una cantidad determinada de sus menciones
//@param: Tipo ostream y nombre salida, se usa para manejar el flujo de salida de los datos
//@param: Tipo * char escritor, funciona para ubicar el escritor de tweets que quiero imprimir en la lista
//@param: Tipo int y nombre cuantasMenciones , se usa para saber cuantas menciones hechas por el escritor debo imprimir
//@return: Se retorna un objeto ostream por referencia, que me permite continuar el manejo del flujo de salida a través de otro metodo externo.
ostream & Lista::imprimir( ostream & salida, char * escritor, int cuantasMenciones){
	if(primera){
		Celda * actual = primera;
		int escritorEncontrado = 0;
		Celda * anterior = 0; //Este puntero le quedara apuntando a la celda del escritor buscado, si lo encuentra
		while(!escritorEncontrado && actual){ // Revisa si el escritor está en la lista
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
