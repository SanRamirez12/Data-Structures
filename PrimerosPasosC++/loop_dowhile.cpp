#include <iostream>

//Ciclos dp-while: sehace un grupo de codigo en la sentencia do y se rompe el ciclo si no se satisface el while
int main(){

    int numero;

    do{
        std::cout << "Introduzca un numero positivo: ";
        std::cin >> numero;
    }while(numero < 0);
    
    std::cout << "El # es: " << numero;
    

    
    return 0;
}