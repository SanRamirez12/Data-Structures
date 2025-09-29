#include <iostream>
#include <cmath> // Incluir esta librería para usar pow()

int main(){
    //Sentencia de prints: std: standar, c: character, out: output, endl: end line
    // std::cout << "I like pizza" << std::endl;
    //std::cout << "Me cago en visual";


    //declaracion de variables y asignacion
    /*
    int edad = 22;
    int ahno = 2003;
    double temperatura = 26.7;
    char nota = 'A'; //solo permite un caracter
    bool decision = false; 
    std::string nombre = "Santi"; //hay que ponerlo como un un tipo de objeto

    std::cout << "Hola " << nombre << '\n';
    std::cout << "Tienes " << edad << " ahnos";
    */

    const double PI = 3.1415; //definimos pi como una constante
    double radio = 10;
    double circunferencia = 2*PI*radio;

    std::cout << "La circunferencia del circulo es: " << circunferencia << " m \n";

    double masa = 86;
    const double c = 299792458;
    double c_cuadrado = std::pow(c,2);
    double energia = masa* c_cuadrado;

    std::cout << "La energia en reposo de mi cuerpo, segun Einstein es: " << energia<< " J";


    return 0;
}