#ifndef VENTA_H
#define VENTA_H
#include<iostream>
#include<string>
#include<vector>
#include "Producto.h"
#include "Cliente.h"


class Venta {
private:
    int ID;
    string fecha, idCliente;
    vector<Producto> productos;
    double total;
public:
    Venta(int id , string f , string idCli){
    	ID = id;
    	fecha = f;
    	idCliente = idCli;
    	total = 0.0;
	}
     
    int getId(){
    	return ID;
	}             
	string getFecha(){
		return fecha;
	}
	string getIdCliente(){
		return idCliente;
	}
	double getTotal(){
		return total;
	}
	vector<Producto>& getProductos(){
		return productos;
	}
	void setFecha(string f){
		fecha = f;
	}
	void setIdCliente(string idCli){
		idCliente = idCli;
	}

 void agregarProducto(Producto& p);
 void calcularTotal();
 void mostrarResumen();
 
	};
	
#endif	