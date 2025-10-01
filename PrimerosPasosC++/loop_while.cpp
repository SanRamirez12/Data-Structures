#include <iostream>

//Ciclos while
int main(){

    std::string nombre;

    //ciclo infinito hasta que se satisfaga la condicion 
    while(nombre.empty()){
        std::cout<< "Indroduzca su nombre: ";
        std::getline(std::cin, nombre);

    }
    std::cout << "Hola " << nombre;


    return 0;
}