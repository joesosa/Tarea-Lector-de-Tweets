#ifndef _Lector
#define _Lector
#include <fstream>
using namespace std;
class Lector{
    public:
        void lectorDeComas();
		char* lectorArrobas();
        Lector(char*);
        void lectorTexto();
		
		
	private:	
		ifstream entrada;
        
};
#endif
