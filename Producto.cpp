#include"Producto.h"
using namespace std;

void Producto::actualizarStock(int cantidad){
	stock= stock + cantidad;
	if(stock < 0){
		stock = 0;
	}
}

 double Producto::margen(){
 	return precio - costo;
 }
  
 void Producto::mostrar(){
 	cout<<" ID: "<<ID<<endl;
 	cout<<"Nombre: "<<nombre<<endl;
 	cout<<"Categoría: "<<categoria<<endl;
 	cout<<"Precio: "<<precio<<"$"<<endl;
 	cout<<"Costo: "<<costo<<"$"<<endl;
 	cout<<"Stock: "<<stock<<endl;
 	
 }