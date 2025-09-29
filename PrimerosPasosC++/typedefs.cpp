#include <iostream>
#include <vector>

//Los typedef son aliases para variables, se le agrega al final: _t
typedef std::vector<std::pair<std::string, int >> listadoble_t;
typedef std::string text_t;



int main(){

    //listadoble_t listadoble1;
    text_t nombre =" Santiago";
    text_t apellido ="Ramirez";

    std::cout << "Mi nombre es: " << nombre << " " << apellido ;
    return 0;
}