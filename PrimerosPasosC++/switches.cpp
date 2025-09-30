#include <iostream>
using namespace std;

//alternativa para usar muchos ifs
int main(){

    int mes;
    cout<< "Ingrese el mes (1-12): ";
    cin >> mes;

    switch(mes){
        case 2:
            cout << "Es Febrero";
            break;
        case 3:
            cout << "Es Marzo";
            break;
        case 4:
            cout << "Es Abril";
            break;
        case 5:
            cout << "Es Mayo";
            break;
        case 6:
            cout << "Es Junio";
            break;
        case 7:
            cout << "Es Julio";
            break;
        case 8:
            cout << "Es Agosto";
            break;
        case 9:
            cout << "Es Septiembre";
            break;
        case 10:
            cout << "Es Octubre";
            break;
        case 11:
            cout << "Es Noviembre";
            break;
        case 12:
            cout << "Es Diciembre";
            break;
        default:
            cout << "Número inválido. Debe ser entre 1 y 12.";

    }
    return 0;
}