#include<iostream>

using namespace std;
//Dado tres numeros calcular su promedio

int main()
{
	int num1=0,num2=0,num3=0;
	float prom=0;
	cout<<"Ingrese num1\n";
	cin>>num1;
	cout<<"Ingrese num2\n";
	cin>>num2;
	cout<<"Ingrese num3\n";
	cin>>num3;
	prom=(num1+num2+num3)/(float)3;
	cout<<"El promedio es:"<<prom<<"\n";
	
	return 0;
}
