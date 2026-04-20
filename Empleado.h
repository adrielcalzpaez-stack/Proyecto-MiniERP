#ifndef EMPLEADO_H
#define EMPLEADO_H
#include "Persona.h"
#include<string>
using namespace std;


	class Empleado : public Persona {
private:
    string cargo;
    double salario;
public:
    Empleado(string n , string a , string id , string t  , string c , double s = 0.0)
    :Persona(n,a,id,t){
    cargo = c;
	salario = s;	
	}
	
	string getCargo(){
		return cargo;
	}
	double getSalario(){
		return salario;
	}
	void setCargo(string c){
		cargo = c;
	}
	void setSalario(double s){
	salario = s;	
	}
	
	void mostrarInfoCompleta();
	void actualizarSalario(double nuevoSalario);
	
	};
	
#endif	