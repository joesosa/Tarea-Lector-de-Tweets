#ifndef _Lector
#define _Lector
using namespace std;
class Lector{
    public:
        void lectorDeComas(ifstream& entrada);
		char* lectorArrobas(ifstream&);
        Lector(char*);
        void lectorTexto();
		
		
	private:	
		ifstream entrada;
        
};
#endif
