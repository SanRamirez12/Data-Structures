#include<iostream>

using namespace std;
//Escribir un programa que solicite los km recorridos por un automovil y la cantidad de combustible
//consumido, mostrar cuanto combustible gasta por kilometro recorrido
//Asumiendo que el valor del combustible es de 880CLP , mostrar el costo por km recorrido

int main()
{
	float km=0,comb=0,gasto=0,costo=0;
	cout<<"Ingrese cantidad de km recorridos\n";
	cin>>km;
	cout<<"Ingrese cantidad de combustible consumido\n";
	cin>>comb;
	gasto=comb/km;
	costo=gasto*880;
	cout<<"El gasto de combustible por km es:"<<gasto<<"Litro/km\n";
	cout<<"El costo por km recorrido es de:"<<costo<<"costo/km\n";
	
	return 0;
}
