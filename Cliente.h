#ifndef CLIENTE_H
#define CLIENTE_H
#include"Persona.h"
#include<vector>
#include<string>

class Venta;

class Cliente : public Persona {
private:
    string correo;
    vector<Venta> historialCompras;
public:
    Cliente(string n , string a , string id, string t , string email )
    :Persona(n,a,id,t){
    	correo = email;
	}
	
	string getCorreo(){
		return correo;
	}
	void setCorreo(string email){
		correo = email;
	}
	
	void agregarCompra(Venta& venta);
	void eliminarVentaHistorial(int idVenta);
	double totalGastado();
	void mostrarHistorial();
	bool tieneCompras();
	
	int getNumeroCompras();
	
	};
	
	#endif