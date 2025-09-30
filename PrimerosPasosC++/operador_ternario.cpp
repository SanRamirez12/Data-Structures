#include <iostream>


//operador ternario ?: = cambiar una sentencia if/else
//Formato:  condicion ? expresion1 : expresion 2; 
int main() {
    double nota;
    std::cout << "Nota del curso: ";
    std::cin >> nota;

    (nota >= 70) ? (std::cout << "¡Pasaste el curso!")
                 : ((nota >= 60) ? (std::cout << "Debes ir a ampliación")
                                 : (std::cout << "¡Reprobaste!"));
    std::cout << '\n';
    return 0;
}


//Otros operadores:
// && = and, dos condiciones son verdsaderas
// || = or, al menos una es verdadera
// ! = not, niega el valor de la variable, usado para booleans 