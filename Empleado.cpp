#include "Empleado.h"
#include<iostream>
using namespace std;

void Empleado::mostrarInfoCompleta(){
	mostrarInfo();
	cout<<"Cargo: "<<cargo<<endl;
	cout<<"Salario: "<<salario<<"$"<<endl; 
}

void Empleado::actualizarSalario(double nuevoSalario){
	salario = nuevoSalario;
}