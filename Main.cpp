#include "ListaTweets.h"
#include "Lector.h"
#include<iostream>
#include <fstream>
using namespace std;
int main(int argc, char * * argv){
  int opcion = 1;
  Lector lector(argv[1]);
  while(opcion != 2){
    if(opcion == 1){
      int cantMenciones = 0;
      char* nombre  = new char[30];
      cout<<"Digite el usuario por ser consultado: "<<endl; cin>>nombre;
      cout<<"Digite la cantidad de menciones que desea ver de tal usuario... "<<endl; cin>>cantMenciones;
      //lista.devuelveMenciones(nombre,cantMenciones);
      cout<<"******************************************"<<endl;
      delete nombre;
      opcion = 3;
    }
    cout<<"Que desea hacer?"<<endl;
    cout<<"1. Consultar menciones \n2. Salir"<<endl; cin>>opcion;
  }
 
return 0;
}