#include <iostream>


//Metodos para variables de tipo string
int main() {

    std::string nombre;
    std::cout << "Introduzca su nombre: ";
    std::getline(std::cin, nombre);

    if(nombre.length()> 12){//lenght para el tamahno del string
        std::cout << "Su nombre no puede tener mas de 12 caracteres  \n";
    }
    else if(nombre.empty()){//empty es para valores vacios
        std::cout << "Su nombre esta vacio, porfavor digite un valor  \n";
    }
    else{
        std::cout << "Bienvenido " << nombre << "\n";
    }

    //nombre.clear(); //limpiamos la variable

    nombre.append("@gmail.com"); //concatenamos un string a la variable
    std::cout << "Su correo es: " << nombre << "\n";

    std::cout << nombre.at(0) << "\n"; //devuelve el valor del caracter en esa posicion del string
    nombre.insert(0, "@"); //se inserta un string en la posicion indicada

    std::cout << "SOS " << nombre << "\n";
    return 0;
}