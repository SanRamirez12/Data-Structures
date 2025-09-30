#include <iostream>

//Conversiones de variables explicitas e implicitas
int main(){

    //char x = 100;
    //std::cout << x;

    //std::cout << (char) 100;

    int resp_correctas = 8;
    int preguntas = 10;

    //double resultado = resp_correctas/preguntas *100; //si se hace asi, se toma 0 y se multilica por 100 por ser ints
    double resultado = resp_correctas/(double)preguntas *100; //asi obtenemos el 80%
    std::cout << resultado << "%";


    return 0;
}

