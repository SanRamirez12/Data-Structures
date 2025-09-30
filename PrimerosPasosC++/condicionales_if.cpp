#include <iostream>

//condicionales if
int main(){
    int edad;

    std::cout << "Ingresa tu edad: ";
    std::cin >> edad;

    if(edad >= 18 && edad <= 100){
        std::cout << "Bienvenido al bar";
    }
    else if(edad < 0){
        std::cout << "Aun no has nacido";
    }
    else if(edad > 100){
        std::cout << "Tas muy viejo pa";
    }
    else{
        std::cout << "No puede pasar papi";
    }

    return 0;
}