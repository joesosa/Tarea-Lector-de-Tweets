#ifndef _Lector
#define _Lector
#include <fstream>
using namespace std;
class Lector{
    public:
        void lectorDeComas(ifstream&);
		char* lectorArrobas(ifstream&);
        void lectorTexto(ifstream&);
        void leer();
		
		
	private:	
		ifstream entrada;
        char letra;
        
};
#endif
