#ifndef PRODUCTO_H
#define PRODUCTO_H

#include<iostream>
#include<string>
using namespace std;
	
	class Producto {
private:
    int ID, stock; 
    string nombre, categoria;
    double precio, costo;
    
public:
    Producto(int i , string n , string cat ,  double p , double c , int s ){
        ID= i;
        nombre = n;
        categoria = cat;
        precio = p;
        costo = c;
        stock = s;
         }
             
     string getNombre() {
	 	return nombre;
	 }
    string getCategoria() {
    	return categoria;
	}
    int getId() {
    return ID;	
	}
    double getPrecio() {
    	return precio;
	}
	double getCosto() {
    	return costo;
	}
	int getStock() {
    	return stock;
	}
      
	   void setNombre(string n){
	   	nombre = n;
	   }
    void setCategoria(string cat){
    	categoria = cat;
	}
    void setPrecio(double p){
    	precio= p;
	}
    void setCosto(double c){
    	costo = c;
	}
    void setStock(int s){
    	stock = s;
	}
	
	void actualizarStock(int cantidad);
	void mostrar();
	double margen();
};


#endif