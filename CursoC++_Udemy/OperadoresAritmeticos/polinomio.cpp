#include<iostream>
#include<math.h>
using namespace std;

//Resolver el polinomio dado

int main()
{
	int x=0,resultado=0;
	cout<<"Ingrese valor de x\n";
	cin>>x;
	resultado=(5*pow(x,3))+(7*pow(x,2))+(3*x)+9;
	cout<<"El resultado es: "<<resultado<<"\n";
	return 0;
}
