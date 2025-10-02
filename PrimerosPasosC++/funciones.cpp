#include <iostream>
//Definicion de funciones

void happyBirthday(std::string nombre){
    std::cout << "Happy Birthday to you!  \n";
    std::cout << "Happy Birthday to you!  \n";
    std::cout << "Happy Birthday dear "<< nombre <<"!  \n";
    std::cout << "Happy Birthday to you!  \n";
}



int main(){
    
    std::string nombre;
    std::cout << "Introduzca su nombre: ";
    std::cin >>  nombre;
    happyBirthday(nombre);
    
    return 0;
}