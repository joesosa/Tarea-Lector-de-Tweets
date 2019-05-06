#include "Lector.h"
#include <iostream>
#include <ctype.h>
#include <fstream>
using namespace std;
#define MAX 30
Lector::Lector(char* nombre){
	ifstream entrada(nombre);
}


char* Lector::lectorArrobas(){
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

void Lector::lectorDeComas(){
	char coma = ',', caracter = ' ';
	int cont = 0, indice = 0;
	char * escritorTweet;
	char **menciones = new char *[MAX];
	//entrada.open(*nombre,ios::in);
	while(cont<14){
	//if(archivo.fail()){
		//exit(1);
	//}
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
					mencionRecibida = lectorArrobas(); //revisar
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
			escritorTweet = lectorArrobas();//revisar
		}
		//if que revisa si la lista del escritor del tweet, crea o no crea
		//despuese se mete a esa lista y suma a los del vector o los crea
		//mismo metodo con los del vector
		//y se le suma al atributo de escritor
		/*if(!lista.primera){
			lista.pushFront(escritorTweet);
		}
		else{
			if(!lista.existe(escritorTweet)){
				lista.pushBack(escritorTweet);
			}
		}*/
		for(int j = 50; j>= 0; --j){
			delete menciones[j];
		}
		delete[] menciones;
	}
}

void Lector::lectorTexto(){
	while(entrada.eof()){
		lectorDeComas();
	}
}
	
		
