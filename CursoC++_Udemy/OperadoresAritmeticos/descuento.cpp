#include<iostream>

using namespace std;
//Un cliente compra tres productos con descuento , dado el precio y su descuento calcular el total a pagar
//////////////////////////////////
int main()
{
	int precio1=0,precio2=0,precio3=0,descuento1=0,descuento2=0,descuento3=0,total=0;
	cout<<"Ingrese precio1\n";//10/100=0.1--->10000*(1-0.1)=9000
	cin>>precio1;
	cout<<"Ingrese precio2\n";
	cin>>precio2;
	cout<<"Ingrese precio3\n";
	cin>>precio3;
	cout<<"Ingrese descuento1\n";
	cin>>descuento1;
	cout<<"Ingrese descuento2\n";
	cin>>descuento2;
	cout<<"Ingrese descuento3\n";
	cin>>descuento3;
	total=precio1*(1-descuento1/(float)100)+precio2*(1-descuento2/(float)100)+precio3*(1-descuento3/(float)100);
	cout<<"El total a pagar es de:"<<total;
	return 0;
}
