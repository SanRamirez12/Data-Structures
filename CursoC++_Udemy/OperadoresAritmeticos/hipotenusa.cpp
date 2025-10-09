#include<iostream>
#include<math.h>
using namespace std;

//Calcular la hipotenusa de una rectangulo rectangulo sabiendo sus lados a y b
//a2+b2=c2----->c=raiz(a2+b2)
int main()
{
	int a=0,b=0;
	float hip;
	cout<<"Ingrese lado a\n";
	cin>>a;
	cout<<"Ingrese lado b\n";
	cin>>b;
	hip=sqrt(pow(a,2)+pow(b,2));
	cout<<"la hipotenusa es: "<<hip<<"\n";
	return 0;
}
