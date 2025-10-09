#include<iostream>

using namespace std;

int main()
{
	//+,-,*,/,%
	int a=12,b=5,suma=0,resta=0,mult=0,mod=0;
	float div=0;
	suma=a+b;
	resta=a-b;
	mult=a*b;
	div=a/(float)b;
	mod=a%b;
	cout<<"la suma es:"<<suma<<"\n";
	cout<<"la resta es:"<<resta<<"\n";
	cout<<"la multiplicacion es:"<<mult<<"\n";
	cout<<"la division es:"<<div<<"\n";
	cout<<"el resto es"<<mod<<"\n";
	
	return 0;
}
