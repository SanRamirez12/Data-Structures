#include<iostream>
using namespace std;


//determinar si el numero es primo o no lo es
int main()
{


	int num=0, i=2;
	cout << "Ingrese un numero: ";
	cin>> num;
	while(i<num){
		if(num%i==0){
			cout<<"El numero "<<i<< " no es primo \n";
		}
		i++;
	}
	cout<<"El numero es primo \n";
	return 0;
}
//chekear