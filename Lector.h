#ifndef _Lector
#define _Lector
#include <fstream>
#include "ListaTweets.h"
using namespace std;
class Lector{
    public:
        void lectorDeComas(ifstream&);
		char* lectorArrobas(ifstream&);
        void lectorTexto(ifstream&);
        void leer();
        Lista lista;
		
		
	private:	
		ifstream entrada;
        char letra;
        
};
#endif
