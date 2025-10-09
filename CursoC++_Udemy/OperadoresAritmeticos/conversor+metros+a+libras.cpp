#include<iostream>

//Cree un conversor de kilogramos a libras y de libras a metros sabiendo que
//1 kg= 2.205libras

using namespace std;

int main()
{
	float kilogramos=0,libras=0;
	cout<<"ingrese cantidad en kg\n";
	cin>>kilogramos;
    libras=2.205*kilogramos;
	cout<<"la cantidad en libras es:"<<libras<<" libras\n";
	
	cout<<"ingrese cantidad en libras\n";
	cin>>libras;
	kilogramos=libras/2.205;
	cout<<"la cantidad ingresada es equivalente a:"<<kilogramos<<" kilogramos\n";
	return 0;
}
