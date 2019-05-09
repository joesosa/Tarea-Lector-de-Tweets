#include "Lector.h"
#include "ListaTweets.h"
#include <iostream>
#include <ctype.h>
#include <fstream>
#include <string.h>
using namespace std;
#define MAX 30
Lector::Lector(ifstream& entrada){
	lectorTexto(entrada);
}

/*@Descrip:al encontrar una arroba lee los caracteres hasta algo que no pertenezca a una mencion
@Param:
@Return:un puntero a char que almacena toda la palabra
*/
char* Lector::lectorArrobas(ifstream& entrada){
	char caracter = ' ';
	entrada.get(caracter);
	char * palabra = 0;
	palabra = new char[MAX];
	int cont = 0;
    while( ((int)caracter >= 0 && (int)caracter < 10) || isalpha(caracter) || caracter == '_'){
		palabra[cont++] = caracter;
		entrada.get(caracter);
	}
	return palabra;
}

/*@Descrip:lee las comas de cada tweet, con el fin de buscar el escritor del tweet y sus menciones
a partir de la primera coma se sabe que es texto y a partir de la tercera se sabe que es el escritor
*/
void Lector::lectorDeComas(ifstream& entrada){
	char coma = ',', caracter = ' ';
	int cont = 0, indice = 0, cantMenciones=0;
	char * escritorTweet;
	char **menciones = new char *[MAX];
	while(cont<14){
		entrada.get(caracter);
		if(caracter == ','){
			cont++;
			entrada.get(caracter);
		}
		if(cont==1){
			while(cont == 1){
				entrada.get(caracter);
				if(caracter == '@'){
					char * mencionRecibida;//revisar
					strcpy(mencionRecibida,lectorArrobas(entrada)); //revisar
					if(mencionRecibida){
						strcpy(menciones[indice++],mencionRecibida); 
					}
				}
				if(caracter == ','){
					cont++;
				}
			}
		}
		if(cont == 3){
			strcpy(escritorTweet,lectorArrobas(entrada));//revisar
		}
		if(cont == 13){
			entrada>>cantMenciones;
			for(int i = 0; i < MAX;++i){
				menciones[i] = new char[cantMenciones];
			}
			if(lista.existeEscritor(escritorTweet)){ //inserta menciones y escritor
				for(int i = 0; i<indice;++i){
					lista.insertarMencion(escritorTweet, menciones[i]);
				}	
			}
			else{									
				lista.insertar(escritorTweet,0);
				for(int i = 0; i<indice;++i){
					lista.insertarMencion(escritorTweet, menciones[i]);
				}
			}
			for(int j = cantMenciones-1; j>= 0; --j){
				delete menciones[j];
			}
			delete[] menciones;
		}
	}
}

void Lector::lectorTexto(ifstream& entrada){
	while(entrada.eof()){
		lectorDeComas(entrada);
	}
}

	
		
