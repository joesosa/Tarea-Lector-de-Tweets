#ifndef _Lector
#define _Lector
#include <fstream>
#include "ListaTweets.h"
using namespace std;
class Lector{
    public:
        void lectorDeComas(ifstream&);
		char* lectorArrobas(ifstream&);
        Lector(ifstream&);
        void lectorTexto(ifstream&);
        void leer();
		
		
	private:	
		ifstream entrada;
        char letra;
        Lista lista;
        
};
#endif
