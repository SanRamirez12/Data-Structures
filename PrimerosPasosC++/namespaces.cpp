#include <iostream>

//Creamos espacios de variables que pueden tener diferentes valores de acuerdo a su espacio
namespace primero{
    int x = 1;
}

namespace segundo{
    int x = 5;
}

int main(){
    //si no se especifica en la sentencia del print, tenemos que usar el using namespace
    using namespace segundo; 

    //std::cout << x << '\n'; //imprimimos el x del main
    // std::cout << primero::x << '\n'; //imprimimos el x del primer namespace
    // std::cout << segundo::x; //imprimimos el x del segundo namespace


    //Esto es otra alternativa para acortar las sentencias standar, pero no se recomienda.
    using std::cout;
    using std::string;

    string nombre = "Pepe";
    cout << "Holi "<< nombre << " Como estas?";
    return 0;
}