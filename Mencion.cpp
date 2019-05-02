#include "Mencion.h"

Mencion::Mencion(char* nombre){
    this->nombre = nombre;
    cantMencionadas = 0;
}

Mencion::~Mencion(){
    delete nombre;
}
