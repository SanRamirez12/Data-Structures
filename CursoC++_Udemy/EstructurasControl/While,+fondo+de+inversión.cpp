#include<iostream>

//Un usuario decide dejar sus ahorros en un fondo de inversión que le ofrece una rentabilidad del 9% anual
//¿Cuanto dinero tendria este usuario al cabo de 5 años sin retirar dinero?

using namespace std;

int main()
{
	float inversion=0,plazo=5,i=0;
	int total=0;
	cout<<"Ingrese inversion\n";
	cin>>inversion;
	while(i<plazo)//1000000*1.09=10900000*1.09
	{
		inversion=inversion*1.09;
		total=(int)inversion;
		cout<<"inversion:"<<total<<"\n";
		i++;
	}
	total=(int)inversion;
	cout<<"la cantidad final es de:"<<total;
	return 0;
}
