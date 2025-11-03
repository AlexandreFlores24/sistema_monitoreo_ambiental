#include <iostream>
using namespace std;
/*Sistema de Monitoreo Ambiental con Red de Sensores*/

#define MAX 10
int cola[MAX];
int frente=-1;
int final=-1; 

bool estaVacia(){
	return frente==1;
}

bool estaLlena(){
	return final==MAX-1
}

void encolar(int dato){
	if(estaLlena()){
		caout<<"La cola está llena. No se puede insertar mas elementos."<<endl;
	}else{
		if(frente==-1){//Si la cola está vacia
			frente=0;
		}
	}
}
int main(int argc, char *argv[])
{
    system("PAUSE");
    return EXIT_SUCCESS;
}
