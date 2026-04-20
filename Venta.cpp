#include "Venta.h"
#include "Cliente.h"
using namespace std;

void Venta::agregarProducto(Producto& p){
	productos.push_back(p);
	calcularTotal();
}

  void Venta::calcularTotal(){
  	total = 0.0;
  	for(int i=0; i < (int)productos.size(); i++ ){
  		total = total + productos[i].getPrecio();
	  }
  }
  
  void Venta::mostrarResumen(){
  	cout<<"ID Venta: "<<ID<<endl;
  	cout<<"Fecha: "<<fecha<<endl;
    cout<<"ID Cliente: "<<idCliente<<endl;  	
  	cout<<"Total: "<<total<<"$"<<endl;
  	cout<<" "<<endl;
  }