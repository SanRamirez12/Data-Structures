#include<iostream>

//Crear un login de usuario, pedir un nombre y una contrase�a, volver a pedir contrase�a 
//una y otra vez hasta que la contrase�a sea validada

using namespace std;

int main()
{
	string nombre="Admin";
	int password1=0,password2=0;
	cout<<"Ingrese nombre de cuenta a crear\n";
	cin>>nombre;
	cout<<"ingrese clave\n";
	cin>>password1;
	do
	{
		cout<<"ingrese nuevamente clave\n";
		cin>>password2;
		if(password1!=password2)
			cout<<("contrasena invalida\n");
	}while(password1!=password2);
	cout<<("La cuenta a sido creada con exito\n");
	
	return 0;
}
