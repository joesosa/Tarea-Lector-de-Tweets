#include "Lector.h"
#include "ListaTweets.h"
#include <iostream>
#include <ctype.h>
#include <fstream>
using namespace std;
#define MAX 30
Lector::Lector(ifstream& entrada){
	lectorTexto(entrada);
}


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

void Lector::lectorDeComas(ifstream& entrada){
	char coma = ',', caracter = ' ';
	int cont = 0, indice = 0;
	char * escritorTweet;
	char **menciones = new char *[MAX];
	while(cont<14){
		entrada.get(caracter);
		if(caracter == ','){
			cont++;
			entrada.get(caracter);
		}
		if(cont==1){
            for(int i = 0; i < MAX;++i){
			    menciones[i] = new char[MAX];
		    }
			while(cont == 1){
				entrada.get(caracter);
				if(caracter == '@'){
					char * mencionRecibida;//revisar
					mencionRecibida = lectorArrobas(entrada); //revisar
					if(mencionRecibida){
						menciones[indice++] = mencionRecibida; 
					}
				}
				if(caracter == ','){
					cont++;
				}
			}
		}
		if(cont == 3){
			escritorTweet = lectorArrobas(entrada);//revisar
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
		
		for(int j = 50; j>= 0; --j){
			delete menciones[j];
		}
		delete[] menciones;
	}
}

void Lector::lectorTexto(ifstream& entrada){
	while(entrada.eof()){
		lectorDeComas(entrada);
	}
}

	
		
