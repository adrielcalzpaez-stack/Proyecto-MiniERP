#include<fstream>
#include<iostream>
#include<vector>
#include<map>
#include"Producto.h"
#include"Cliente.h"
#include"Empleado.h"
#include"Venta.h"
#include"Funciones.h"
#include"json.hpp"
using namespace std;
using json = nlohmann::json;

 vector<Producto>productos;
 vector<Cliente> clientes;
 vector<Empleado>empleados;
 vector<Venta>ventas;
 map<int, bool>idsProductosOcupados;
 map<int, bool>idsClientesOcupados;
 map<int, bool>idsEmpleadosOcupados;
 int nextIdVenta = 1;

int main(int argc, char** argv) {
	cargarProductos();
	cargarClientes();
	cargarEmpleados();
	cargarVentas();
	
	int opcion;
	system("Color 1E");
	
	
	do{
		cout<<"            Mini-ERP        "<<endl;
		cout<<"-------- Menu Principal --------"<<endl;
		cout<<"1. Productos "<<endl;
		cout<<"2. Clientes "<<endl;
		cout<<"3. Empleados "<<endl;
		cout<<"4. Ventas "<<endl;
		cout<<"5. Reportes y Estadisticas "<<endl;
		cout<<"6. Salir "<<endl;
		cout<<"Seleccione una opcion : ";
						cin>> opcion;
						cout<<" "<<endl;
						
						switch(opcion){
							case 1: menuProductos();
							break;
							
							case 2: menuClientes();
							break;
							
							case 3: menuEmpleados();
							break;
							
							case 4: menuVentas();
							break;
							
							case 5: menuReportes();
							break;
							
							case 6: cout<<" Saliendo del sistema...  ): "<<endl;
							break;
							
							default: cout<<"Opcion no disponible "<<endl;
							
						}
	}while(opcion != 6);
	
	guardarProductos();
	guardarClientes();
	guardarEmpleados();
	guardarVentas();
	
	return 0;
}