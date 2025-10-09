#include<iostream>

//Dado dos numeros ingresados por el usuario , obtener la sumatoria de todos los numeros entre ellos

using namespace std;

int main()
{
	int num=0,num2=0,suma=0,aux=0;//2+3+4+5+6+7+8+9+10=54
	cout<<"Ingrese un valor\n";
	cin>>num;
	aux=num;
	cout<<"Ingrese un segundo valor\n";
	cin>>num2;//2,3,4--->10->11
	for(num==0;num<=num2;num++)
	{//0+2=2, 2+3=5  5+4=9
		suma=suma+num;
	}
	cout<<"La sumatoria desde:"<<aux<<"hasta:"<<num2<<"es:"<<suma;
	return 0;
}
