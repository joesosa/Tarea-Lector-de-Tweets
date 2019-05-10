#include "Lector.h"

#include <iostream>
#include <ctype.h>
#include <fstream>
#include <string.h>
using namespace std;
#define MAX 30

/*@Descrip:al encontrar una arroba lee los caracteres hasta algo que no pertenezca a una mencion
@Param:
@Return:un puntero a char que almacena toda la palabra
*/
char* Lector::lectorArrobas(ifstream& entrada){
	cout<<"entre lec arr"<<endl;
	char caracter = ' ';
	entrada.get(caracter);
	char * palabra = 0;
	palabra = new char[10];
	int cont = 0;
    while( ((int)caracter >= 0 && (int)caracter < 10) || isalpha(caracter) || caracter == '_'){
		cout<<caracter<<endl;
		palabra[cont] = caracter;
		cont++;
		entrada.get(caracter);
	}
	cout<<palabra << " arroba" <<endl;
	return palabra;
}

/*@Descrip:lee las comas de cada tweet, con el fin de buscar el escritor del tweet y sus menciones
a partir de la primera coma se sabe que es texto y a partir de la tercera se sabe que es el escritor
*/
void Lector::lectorDeComas(ifstream& entrada){
	char coma = ',', caracter = ' ';
	int cont = 0, indice = 1, cantMenciones=0;
	char **menciones = new char*[MAX];
	for(int i = 0; i<MAX;++i){
		menciones[i]= new char[MAX];
	}
	cout<<"entre lec comas"<<endl;
	while(cont<14){
		entrada.get(caracter);
		if(caracter == ','){
			cont++;
			
			cout<<caracter<<endl;
		}
		if(cont==1){
			cout<<"entre lec comas 1"<<endl;
			while(cont == 1){
				entrada.get(caracter);
				cout<<caracter<<endl;
				if(caracter == ','){
					cont++;
				}
				else{ 
					if(caracter == '@'){
						menciones[indice] = lectorArrobas(entrada);
						indice++;
					}
				}
			}
		}
		if(cont == 3){
			cout<<"entre lec comas 3"<<endl;
			entrada.get(caracter);
			entrada.get(caracter);
			menciones[0] = lectorArrobas(entrada);
			cout<<"el escritor es "<<menciones[0]<<endl;
			entrada.get(caracter);
			cont++;

		}
		if(cont == 13){//arreglar
			cout<<"entre lec comas 13"<<endl;
			if(lista.existeEscritor(menciones[0])){ //inserta menciones y escritor
				for(int i = 1; i<indice;++i){
					lista.insertarMencion(menciones[0], menciones[i]);
				}	
			}
			else{									
				lista.insertar(menciones[0],0); //meciones[0] contiene al escritor del tweet
				for(int i = 1; i<indice;++i){
					lista.insertarMencion(menciones[0], menciones[i]);
				}
			}
			
			for(int j = cantMenciones-1; j>= 0; --j){
				delete menciones[j];
			}
			delete[] menciones;
			cont++;
		}
	}
}


	
		
