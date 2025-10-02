#include <iostream>
#include <ctime>

//pseudo-random
int main(){
    
    srand(time(NULL)); //Funcion de randomizacion con una semilla de tiempo 

    int num = (rand() % 6)+1; //inicializacion del numero para un dado de 6 caras 
    
    std::cout << num;

    
    return 0;
}