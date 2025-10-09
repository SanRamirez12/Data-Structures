#include<iostream>

//Pedir dos valores desde consola , luego intercambiar su contenido y mostrarlo por pantalla

using namespace std;

int main()
{
	int a=25,b=17,aux=0;
	cout<<"Ingrese valor 1\n";
	cin>>a;//25->35
	cout<<"Ingrese valor 2\n";
	cin>>b;//17->12
	aux=a;//35
	a=b;//a=35->12
	b=aux;//b=12->35
	cout<<"el contenido de a es:"<<a<<"\n";//12
	cout<<"el contenido de b es:"<<b<<"\n";//35
	return 0;
}
