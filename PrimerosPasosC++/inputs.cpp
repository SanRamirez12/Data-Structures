#include <iostream>

typedef std::string str;

//cout << y cin >>
int main(){

    //inicializacion de variables
    str nombre;
    int edad;


    std::cout << "Cuantos ahnos tienes?: ";
    std::cin >> edad;

    std::cout << "Cual es tu nombre?: ";
    //usamos no solo la sentencia de input sino para obtener todos los valores de la linea
    std::getline(std::cin >> std::ws, nombre); 

    std::cout << "Hola " << nombre<< ", tienes "<< edad <<" ahnos";

    return 0;
}
