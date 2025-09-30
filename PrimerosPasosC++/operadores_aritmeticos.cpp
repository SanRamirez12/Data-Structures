#include <iostream>

//operadores artimeticos = retornan un resultado especfico de una operacion aritmetica (+-*/)
int main(){
    int estudiantes = 20;
    int n = 3;
    //estudiantes = estudiantes + n;
    //estudiantes +=n; //sumamos a la variable
    //estudiantes++;  //le sumamos solo 1

    //estudiantes = estudiantes -n;
    //estudiantes -= n; //se resta n
    //estudiantes --; //se resta 1

    //estudiantes = estudiantes * n; //doblar la cantidad
    //estudiantes *= n; //lo mismo pero mas facil de escribir

    //estudiantes = estudiantes/n; //dividimos
    //estudiantes /=n; lo mismo pero mas facil de escribir

    //int residuo = estudiantes % 3; //calculamos el residuo de una division

    int operacion = 6 -5 + 4 * 3 / 2; 

    std::cout << operacion;
    return 0;
}