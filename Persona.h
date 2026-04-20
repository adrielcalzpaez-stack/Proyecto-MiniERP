#ifndef PERSONA_H
#define PERSONA_H

#include<iostream>
#include<string>
using namespace std;

class Persona  {
		
		protected:
			string nombre, apellido, ID, telefono;
		
		public:
			Persona(string n, string a, string id, string t){
				nombre = n;
				apellido = a;
				ID = id;
				telefono = t;
			}
			
	 string getNombre() {
	 	return nombre;
	 }
    string getApellido() {
    	return apellido;
	}
    string getId() {
    return ID;	
	}
    string getTelefono() {
    	return telefono;
	}
    
    
    void setNombre(string n){
    	nombre = n;
	}
    void setApellido(string a){
    	apellido = a;
	}
    void setTelefono(string t){
    	telefono = t;
	}
	
	void mostrarInfo();
	
};

 #endif