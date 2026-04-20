#include "Cliente.h"
#include"Venta.h"
using namespace std; 

void Cliente::agregarCompra(Venta& venta){
	historialCompras.push_back(venta);
}

double Cliente::totalGastado(){
	double suma = 0.0;
	for(int i=0; i<(int)historialCompras.size();i++){
		suma = suma + historialCompras[i].getTotal();
	}
	return suma;
}

int Cliente::getNumeroCompras(){
	return (int)historialCompras.size();
}

void Cliente::mostrarHistorial(){
	if(historialCompras.empty()){
		cout<<"El cliente no tiene compras registradas. "<<endl;
		cout<<" "<<endl;
		return;
	}
	
	cout<<"Historial de "<<getNombre()<<" "<<getApellido()<<":"<<endl;
	for(int i = 0; i<(int)historialCompras.size();i++){
		historialCompras[i].mostrarResumen();
	}
}

void Cliente :: eliminarVentaHistorial(int idVenta){
	for(int i=0; i<(int)historialCompras.size(); i++){
		if(historialCompras[i].getId()==idVenta){
			historialCompras.erase(historialCompras.begin()+1);
			cout<<"Venta eliminada del historial del cliente."<<endl;
			return;
		}
	}
}

bool Cliente::tieneCompras(){
	return !historialCompras.empty();
}