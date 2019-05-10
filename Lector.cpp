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
	int cont = 0, indice = 0, cantMenciones=0;
	char * escritorTweet = new char[MAX];
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

			while(cont == 3){
				char x[5];
				entrada.getline(x,5,',');

				//entrada.get(caracter);
				//cout<<caracter<<endl;
				cout<<x<<endl;
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

			cout << caracter << endl;
		//	if(caracter == '@'){
		//		escritorTweet = lectorArrobas(entrada);
		//		cout<<"entre lec comas 3 if"<<endl;
		//	}
		//	cout<<"sali lec comas 3"<<endl;
		//	entrada.get(caracter);
		//	cout<<caracter<<endl;
		//	cont++;
		//	cout<<"chao "<< cont <<endl;
		}
		if(cont == 13){//arreglar
			cout<<"entre lec comas 13"<<endl;
			if(caracter == ','){
				cont++;
			}
			cout<<"entre lec comas 13"<<endl;
			/*if(lista.existeEscritor(escritorTweet)){ //inserta menciones y escritor
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
			delete[] menciones;*/
		}
	}
}


	
		
