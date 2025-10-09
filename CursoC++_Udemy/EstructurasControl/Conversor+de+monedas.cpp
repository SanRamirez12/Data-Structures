#include<iostream>

//Hacer un conversor de dinero de dolar-euro, euro-dolar,dolar-clp,clp-dolar,clp-euro,euro-clp
//sabiendo que
//1 dolar= 807 clp
//1 dolar= 0.91euros
//1 euro=1.1dolar
//1 euro=862clp
//1 clp=0.0013 dolares
//1 clp=0.0012 euros 
using namespace std;

int main()
{
	float dolar=0,euro=0,clp=0,cantidad=0;
	int resp=0;
	cout<<"Ingrese un opcion\n";
	cout<<"1)Dolar-Euro\n";
	cout<<"2)Euro-Dolar\n";
	cout<<"3)Dolar-Clp\n";
	cout<<"4)Clp-Dolar\n";
	cout<<"5)Euro-Clp\n";
	cout<<"6)Clp-Euro\n";
	cin>>resp;
	cout<<"Ingrese cantidad\n";
	cin>>cantidad;
	switch(resp)
	{
		case 1 :euro=cantidad*0.91 ;cout<<"La cantidad ingresada equivale a:"<<euro<<"euros";break;
		case 2 :dolar=1.1*cantidad ;cout<<"La cantidad ingresada equivale a:"<<dolar<<"dolares";break;
		case 3 :clp=807*cantidad ;cout<<"La cantidad ingresada equivale a:"<<clp<<"clp";break;
		case 4 :dolar=0.0013*cantidad ;cout<<"La cantidad ingresada equivale a:"<<dolar<<"dolares";break;
		case 5 :clp=862*cantidad ;cout<<"La cantidad ingresada equivale a:"<<clp<<"clp";break;
		case 6 :euro=0.0012*cantidad ;cout<<"La cantidad ingresada equivale a:"<<euro<<"euros";break;
		default: cout<<"Opcion Invalida\n";break;
	}
	return 0; 
}
