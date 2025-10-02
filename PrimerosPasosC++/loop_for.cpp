#include <iostream>

//Ciclos for: de A a B
int main(){
    //Tres partes de la sentencia (inicio del conteo, condicion para acabar, pasos)
    for(int i = 1; i <= 10; i++){
        if(i==7){
            continue;//basicamente se salta el 7
        }
        std::cout << "El valor actual es: " << i <<'\n';
    }

    
    return 0;
}