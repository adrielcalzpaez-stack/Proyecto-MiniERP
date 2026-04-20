#include"Funciones.h"
#include "Producto.h"
#include "Cliente.h"
#include "Empleado.h"
#include "Venta.h"
#include<iostream>
#include<vector>
#include<map>
#include<string>
#include<fstream>
#include"json.hpp"
using namespace std;
using json = nlohmann::json;

extern vector<Producto>productos;
extern vector<Cliente> clientes;
extern vector<Empleado>empleados;
extern vector<Venta>ventas;
extern map<int, bool>idsProductosOcupados;
extern int nextIdVenta;

int obtenerNuevoID(){
  int nuevoId = 1;
  while(idsProductosOcupados[nuevoId]){
    nuevoId ++;
  }
  idsProductosOcupados[nuevoId]=true;
  return nuevoId;
}

void agregarProducto(){
	string nombre, categoria;
	double precio, costo;
	int stock;
	cout<<"Diga el nombre del producto: "<<endl;
	cin>>nombre;
	cout<<"Diga la categoria del producto: "<<endl;
	cin>>categoria;
	cout<<"Diga el precio del producto: "<<endl;
	cin>>precio;
	cout<<"Diga el costo del producto: "<<endl;
	cin>>costo;
	cout<<"Diga la cantidad de unidades del producto: "<<endl;
	cin>>stock;
	
	int nuevoId = obtenerNuevoID();
	productos.push_back(Producto(nuevoId,nombre, categoria, precio, costo, stock));
	cout<<"ID: "<<nuevoId<<endl;
	cout<<" "<<endl;
	
}

void mostrarProductos(){
	if(productos.empty()){
		cout<<"No hay productos registrados."<<endl;
	}else{
		cout<<"Productos registrados: "<<endl;
		for(int i=0; i<(int)productos.size(); i++){
			cout<<"ID: "<<productos[i].getId()<<endl;
			cout<<"Nombre: "<<productos[i].getNombre()<<endl;
			cout<<"Categoria: "<<productos[i].getCategoria()<<endl;
			cout<<"Precio: "<<productos[i].getPrecio()<<"$"<<endl;
			cout<<"Stock: "<<productos[i].getStock()<<endl;
			cout<<" "<<endl;
		}
	}
}

void modificarProducto(){
	int ID;
	cout<<"Diga el ID del producto que desea modificar: "<<endl;
	cin>>ID;
	string nombre, categoria;
	double precio, costo;
	int stock;
	
	for(int i=0; i<(int)productos.size(); i++){
		if(productos[i].getId()==ID){
			cout<<"Ingrese el nuevo nombre: "<<endl;
			cin>>nombre;
			cout<<"Ingrese la nueva categoria: "<<endl;
			cin>>categoria;
			cout<<"Ingrese el nuevo precio: "<<endl;
			cin>>precio;
			cout<<"Ingrese el nuevo costo: "<<endl;
			cin>>costo;
			cout<<"Ingrese el nuevo stock: "<<endl;
			cin>>stock;
			
			productos[i].setNombre(nombre);
			productos[i].setCategoria(categoria);
			productos[i].setPrecio(precio);
			productos[i].setCosto(costo);
			productos[i].setStock(stock);
			
			cout<<"----Producto modificado de manera exitosa----"<<endl;
			cout<<" "<<endl;
			return;
		}
	}
	cout<<"No se encontro un producto con ID: "<<ID<<endl;
}

void eliminarProducto(){
	int ID;
	cout<<"Ingrese el ID del producto a eliminar: ";
	cin>>ID;
	
	for(int i=0; i<(int)productos.size(); i++){
		if(productos[i].getId()==ID){
			idsProductosOcupados[ID]=false;
			productos.erase(productos.begin()+i);
			cout<<"----Producto eliminado de forma exitosa---- "<<endl;
			cout<<" "<<endl;
			return;
		}
	}
	cout<<"No se encontro un producto con ID: "<<ID<<endl;
	cout<<" "<<endl;
}

void filtrarCategoria(){
	string categoria;
	cout<<"Ingrese la categoria que desea filtrar: ";
	cin>>categoria;
	bool encontrada = false;
	cout<<"Productos de categoria: "<<categoria<<endl;
	
	for(int i=0; i<(int)productos.size(); i++){
		if(productos[i].getCategoria()==categoria){
			cout<<"ID: "<<productos[i].getId()<<endl;
			cout<<"NOmbre: "<<productos[i].getNombre()<<endl;
			cout<<"Precio: "<<productos[i].getPrecio()<<"$ "<<endl;
			cout<<"Stock: "<<productos[i].getStock()<<endl;
			cout<<" "<<endl;
			encontrada = true;
		}
	}
	if(encontrada==false){
		cout<<"----No hay productos en la categoria----"<<endl;
		cout<<" "<<endl;
	}
}

void filtrarNombreParcial(){
    string texto, nombre;
    bool encontrado = false;
    bool contiene = false;
    bool encabezado = false;
    bool letrasIguales = true;
     int ultimaPosicion;
    cout<<"Ingrese el nombre parcial del producto(ten en cuenta minusculas y mayusculas) : "<<endl;
    cin>>texto;
    
    
    for(int i = 0; i < (int)productos.size(); i++) {
         nombre = productos[i].getNombre();
         contiene = false; 
         ultimaPosicion = (int)nombre.length()-(int)texto.length();
        
        if(ultimaPosicion>=0){
        for(int j = 0; j <= ultimaPosicion; j++) {
        	letrasIguales = true;
        	
            for(int k = 0; k < (int)texto.length(); k++) {
                if(nombre[j + k] != texto[k]) {
                    letrasIguales = false;
                     break;
                }
            }
    
            if(letrasIguales==true){
                contiene = true;
                break;
            }
         }
		}
       
        if(contiene==true){
        	if(encabezado==false){
        	cout<<"Productos que contienen: "<<texto<<endl;
			encabezado = true;	
			}
		    cout<<"ID: "<<productos[i].getId()<<endl; 
            cout<<"Nombre: "<<nombre<<endl;
            cout<<"Precio: "<<productos[i].getPrecio()<<endl;
            cout<<" "<<endl;
            encontrado = true;
        }
    }
    
    if(encontrado==false) {
        cout<<"NO se encontraron productos que contengan: "<<texto<<endl;
        cout<<" "<<endl;
    }
}

void filtrarRango(){
    double inferior, superior;
    cout<<"Ingrese el precio inferior del rango: "<<endl;
    cin>>inferior;
    cout<<"Ingrese el precio superior del rango:"<<endl;
    cin>>superior; 
    
    bool existe = false;
    cout<<"Productos entre: "<<inferior<<"$ y "<<superior<<"$"<<endl;
    
    for(int i=0; i<(int)productos.size(); i++){
    	double precio = productos[i].getPrecio();
		if(precio >= inferior && precio<= superior){
			cout<<"ID: "<<productos[i].getId()<<endl;
			cout<<"Nombre: "<<productos[i].getNombre()<<endl;
			cout<<"Categoria: "<<productos[i].getCategoria()<<endl;
			cout<<"Precio: "<<precio<<"$"<<endl;
			cout<<"Stock: "<<productos[i].getStock()<<endl;
			cout<<" "<<endl;
			existe = true;
		} 
	}
    if(existe == false){
    	cout<<"No hay productos en ese rango de precios "<<endl;
    	cout<<" "<<endl;
	}
}

void stockCritico(){
	int limite;
	cout<<"Ingrese el limite del stock: "<<endl;
	cin>>limite;
	bool existe = false;
	cout<<"Productos con stock menor a: "<<limite<<endl;
	
	for(int i=0; i<(int)productos.size(); i++){
		if(limite>=productos[i].getStock()){
			cout<<"ID: "<<productos[i].getId()<<endl;
			cout<<"Nombre: "<<productos[i].getNombre()<<endl;
			cout<<"Stock: "<<productos[i].getStock()<<endl;
			cout<<"Precio: "<<"$ "<<productos[i].getPrecio()<<endl;
			cout<<" "<<endl;
			existe = true;
			
		}
	}
	if(existe==false){
		cout<<"No hay productos con stock menor a: "<<limite<<endl;
		cout<<" "<<endl;
	}
} 

void calcularProducto(){
	int indice  = 0;
	double barato = 99999999999999;
	double caro = 0;
	if(productos.empty()){
		cout<<"No hay productos registrados "<<endl;
	}else{
		for(int i=0; i<(int)productos.size(); i++){
			if(productos[i].getPrecio() > caro){
				caro = productos[i].getPrecio();
				indice = i;
			}
		}
		cout<<"Producto mas caro: "<<endl;
		cout<<"ID: "<<productos[indice].getId()<<endl;
		cout<<"Nombre: "<<productos[indice].getNombre()<<endl;
		cout<<"Precio: "<<productos[indice].getPrecio()<<"$ "<<endl;
		
		for(int i=0; i<(int)productos.size(); i++){
			if(productos[i].getPrecio() < barato){
				barato = productos[i].getPrecio();
				indice = i;
			}
		}
		cout<<"Producto mas barato: "<<endl;
		cout<<"ID: "<<productos[indice].getId()<<endl;
		cout<<"Nombre: "<<productos[indice].getNombre()<<endl;
		cout<<"Precio: "<<productos[indice].getPrecio()<<"$"<<endl;
		cout<<" "<<endl;
	}
}

void menuProductos(){
	
	int opcion;
	
	do{
		cout<<"--- Menu Productos ---"<<endl;
		cout<<"1. Agregar producto "<<endl;
		cout<<"2. Mostrar lista de productos "<<endl;
	    cout<<"3. Modificar producto"<<endl;
	    cout<<"4. Eliminar producto"<<endl;
	    cout<<"5. Filtrar por categoria"<<endl;
	    cout<<"6. Filtrar por nombre parcial"<<endl;
	    cout<<"7. Filtrar por rango de precios "<<endl;
	    cout<<"8. Stock critico"<<endl;
	    cout<<"9. Calcular producto mas caro y mas barato"<< endl;
		cout<<"10. Volver al menu principal "<<endl;
		cout<<"Seleccione una opcion: ";
		cin>>opcion;
		cout<<" "<<endl;
		
		switch(opcion){
			
			case 1: agregarProducto();
			break;
			
			case 2: mostrarProductos();
			break;
			
			case 3: modificarProducto();
			break;
			
			case 4: eliminarProducto();
			break;
			
			case 5: filtrarCategoria();
			break;
			
			case 6: filtrarNombreParcial();
			break;
			
			case 7: filtrarRango();
			break;
			
			case 8: stockCritico();
			break;
					
			case 9: calcularProducto();
			break;
					
			case 10: cout<<"Volviendo al menu principal... "<<endl;
			         cout<<" "<<endl;
			break;
			
			default: cout<<"Opcion no disponible "<<endl;
			cout<<" "<<endl;
		}
		
	}while(opcion !=10);
}

void agregarCliente(){
	string nombre, apellido, ID, telefono, email;
	cout<<"Ingrese el nombre del cliente que desea agregar: "<<endl;
	cin>>nombre;
	cout<<"Ingrese el apellido: "<<endl;
	cin>>apellido;
	cout<<"Ingrese el telefono: "<<endl;
	cin>>telefono;
	cout<<"Ingrese el email "<<endl;
	cin>>email;
	
	bool existe;
	do{
		existe = false;
		cout<<"Ingrese el ID del cliente: ";
		cin>>ID;
		for(int i=0; i<(int)clientes.size(); i++){
			if(clientes[i].getId()==ID){
				cout<<"Ya existe un cliente con ese ID. Seleccione otro. "<<endl;
				existe = true;
				break;
			}
		}
	}while(existe == true);
	
	clientes.push_back(Cliente(nombre, apellido,ID, telefono, email)); 
	cout<<"----Cliente agregado con exito---- "<<endl;
	cout<<" "<<endl;
	
}

void mostrarClientes(){
		if(clientes.empty()){
		cout<<"No hay clientes registrados."<<endl;
	}else{
		cout<<"Clientes registrados: "<<endl;
		for(int i=0; i<(int)clientes.size(); i++){
			cout<<"ID: "<<clientes[i].getId()<<endl;
			cout<<"Nombre: "<<clientes[i].getNombre()<<" "<<clientes[i].getApellido()<<endl;
			cout<<"Telefono: "<<clientes[i].getTelefono()<<endl;
			cout<<"Correo: "<<clientes[i].getCorreo()<<endl;
		cout<<" "<<endl;
		}
	}
}

void modificarCliente(){
	string ID, nombre, apellido, telefono, email;
	cout<<"ingrese el ID del cliente que desea modificar: "<<endl;
	cin>>ID;
	
	for(int i=0; i<(int)clientes.size(); i++){
		if(clientes[i].getId()==ID){
			cout<<"Ingrese el nuevo nombre: "<<endl;
			cin>>nombre;
			cout<<"Ingrese el nuevo apellido: "<<endl;
			cin>>apellido;
			cout<<"Ingrese el nuevo telefono: "<<endl;
			cin>>telefono;
			cout<<"Ingrese el nuevo correo: "<<endl;
			cin>>email;
			
			clientes[i].setNombre(nombre);
			clientes[i].setApellido(apellido);
			clientes[i].setTelefono(telefono);
			clientes[i].setCorreo(email);
	
			cout<<"----Cliente modificado de manera exitosa----"<<endl;
			cout<<" "<<endl;
			return;
		}
	}
	cout<<"No se encontro un cliente con ID: "<<ID<<endl;
	cout<<" "<<endl;
	
}

void eliminarCliente(){
	string ID;
	cout<<"Ingrese el ID del cliente a eliminar: ";
	cin>>ID;
	
	for(int i=0; i<(int)clientes.size(); i++){
		if(clientes[i].getId()==ID){
			if(clientes[i].tieneCompras()){
			cout<<"No se puede eliminar el cliente porque tiene compras registradas "<<endl;
			cout<<" "<<endl;
			return;	
			}
			clientes.erase(clientes.begin()+i);
			cout<<"----Cliente eliminado de forma exitosa.---- "<<endl;
			cout<<" "<<endl;
			return;
		}
	}
	cout<<"No se encontro un cliente con ID: "<<ID<<endl;
	cout<<" "<<endl;
}

 void consultarHistorial(){
 	string ID;
 	cout<<"Ingrese el ID del cliente: ";
 	cin>>ID;
 	
 	for(int i=0; i<(int)clientes.size(); i++){
 		if(clientes[i].getId()==ID){
 			clientes[i].mostrarHistorial();
 			return;
		 }
	 }
 	cout<<"Cliente no encontrado."<<endl;
 	cout<<" "<<endl;
 }

void filtrarMonto(){
	double monto;
	cout<<"Ingrese el monto minimo gastado "<<endl;
	cin>>monto;
	bool encontrado = false;
	
	cout<<"Clientes que han gastado mas de $"<<monto<<endl;
	for(int i=0; i<(int)clientes.size(); i++){
		if(clientes[i].totalGastado()>= monto){
			cout<<"ID:"<<clientes[i].getId()<<endl;
			cout<<"Nombre:"<<clientes[i].getNombre()<<" "<<clientes[i].getApellido()<<endl;
			cout<<"Total gastado: $ "<<clientes[i].totalGastado()<<endl;
			cout<<" "<<endl;
			encontrado = true;
		}
	}
	if(encontrado==false){
		cout<<"No hay clientes que hayan gastado mas de: $"<<monto<<endl;
		cout<<" "<<endl;
	}
}

void filtrarCompras(){
	int numero;
	cout<<"Ingrese el numero minimo de compras: "<<endl;
	cin>>numero;
	bool encontrado = false;
	cout<<"Clientes con al menos "<<numero<<" compras"<<endl;
	
	for(int i=0; i<(int)clientes.size(); i++){
		if(clientes[i].getNumeroCompras()>=numero){
			cout<<"ID:"<<clientes[i].getId()<<endl;
			cout<<"Nombre:"<<clientes[i].getNombre()<<" "<<clientes[i].getApellido()<<endl;
			cout<<"Compras: "<<clientes[i].getNumeroCompras()<<endl;
			cout<<" "<<endl;
			encontrado = true;
		}
	}
   	if(encontrado==false){
		cout<<"No hay clientes con al menos "<<numero<<" compras."<<endl;
		cout<<" "<<endl;
	}	
}

void totalGastado(){
	string ID;
	double total;
	cout<<"Ingrese el ID del cliente: "<<endl;
	cin>>ID;
	
	for(int i=0; i<(int)clientes.size(); i++){
		if(clientes[i].getId()==ID){
			total = clientes[i].totalGastado();
			cout<<"El cliente "<<clientes[i].getNombre()<<" "<<clientes[i].getApellido()
			<<" ha gastado un total de $"<<total<<endl;
			cout<<" "<<endl;
			return;
		}
	}
	cout<<"Cliente no encontrado."<<endl;
	cout<<" "<<endl;
}

void menuClientes(){
	int opcion;
	
	do{
		cout<<"Menu Clientes"<<endl;
		cout<<"1. Agregar cliente "<<endl;
		cout<<"2. Mostrar clientes "<<endl;
	    cout<<"3. Modificar cliente "<<endl;
	    cout<<"4. Eliminar cliente "<<endl;
	    cout<<"5. Consultar historial de compras de un cliente"<<endl;
	    cout<<"6. Filtrar clientes por monto gastado"<<endl;
	    cout<<"7. Filtrar clientes por numero de compras"<<endl;
	    cout<<"8. Calcular total gastado por cliente"<<endl;
		cout<<"9. Volver al menu principal  "<<endl;
		cout<<"Seleccione una opcion: ";
		cin>>opcion;
		cout<<" "<<endl;
		
		switch(opcion){
			
			case 1: agregarCliente();
			break;
			
			case 2: mostrarClientes();
			break;
			
			case 3: modificarCliente();
			break;
			
			case 4: eliminarCliente();
			break;
			
			case 5: consultarHistorial();
			break;
			
			case 6: filtrarMonto();
			break;
			
			case 7: filtrarCompras();
			break;
			
			case 8: totalGastado();
			break;
			
			case 9: cout<<"Volviendo al menu principal..."<<endl;
			cout<<" "<<endl;
			break;
			
			default: cout<<"Opcion no disponible "<<endl;
			cout<<" "<<endl;
		}
	}while(opcion != 9);
}

void agregarEmpleado(){
	
	string nombre, apellido, ID, telefono, cargo;
	double salario;
	cout<<"Ingrese el nombre del empleado que desea agregar: "<<endl;
	cin>>nombre;
	cout<<"Ingrese el apellido: "<<endl;
	cin>>apellido;
	cout<<"Ingrese el telefono: "<<endl;
	cin>>telefono;
	cout<<"Ingrese el cargo "<<endl;
	cin>>cargo;
	cout<<"Ingrese el salario "<<endl;
	cin>>salario;
	
	bool existe;
	do{
		existe = false;
		cout<<"Ingrese el ID del empleado: "<<endl;
		cin>>ID;
		for(int i=0; i<(int)empleados.size(); i++){
			if(empleados[i].getId()==ID){
				cout<<"Ya existe un empleado con ese ID. Seleccione otro. "<<endl;
				existe = true;
				break;
			}
		}
	}while(existe == true);
	
	empleados.push_back(Empleado(nombre, apellido,ID, telefono, cargo, salario)); 
	cout<<"----Empleado agregado con exito---- "<<endl;
	cout<<" "<<endl;
		
}

void mostrarEmpleados(){
		if(empleados.empty()){
		cout<<"No hay empleados registrados."<<endl;
		cout<<" "<<endl;
	}else{
		cout<<"Empleados registrados: "<<endl;
		for(int i=0; i<(int)empleados.size(); i++){
			cout<<"ID: "<<empleados[i].getId()<<endl;
			cout<<"Nombre: "<<empleados[i].getNombre()<<" "<<empleados[i].getApellido()<<endl;
    cout<<" "<<endl;
		}
	}
}

void modificarEmpleado(){
	string ID, nombre, apellido, telefono, cargo;
	double salario;
	cout<<"ingrese el ID del empleado que desea modificar: "<<endl;
	cin>>ID;
	
	for(int i=0; i<(int)empleados.size(); i++){
		if(empleados[i].getId()==ID){
			cout<<"Ingrese el nuevo nombre: "<<endl;
			cin>>nombre;
			cout<<"Ingrese el nuevo apellido: "<<endl;
			cin>>apellido;
			cout<<"Ingrese el nuevo telefono: "<<endl;
			cin>>telefono;
			cout<<"Ingrese el nuevo cargo: "<<endl;
			cin>>cargo;
			cout<<"Ingrese el nuevo salario: "<<endl;
			cin>>salario;
			
			empleados[i].setNombre(nombre);
			empleados[i].setApellido(apellido);
			empleados[i].setTelefono(telefono);
			empleados[i].setCargo(cargo);
			empleados[i].actualizarSalario(salario);
	
			cout<<"----Empleado modificado de manera exitosa.----"<<endl;
			cout<<" "<<endl;
			return;
		}
	}
	cout<<"No se encontro un empleado con ID: "<<ID<<endl;
	cout<<" "<<endl;
}

void eliminarEmpleado(){
	string ID;
	cout<<"Ingrese el ID del empleado a eliminar: ";
	cin>>ID;
	
	for(int i=0; i<(int)empleados.size(); i++){
		if(empleados[i].getId()==ID){
			empleados.erase(empleados.begin()+i);
			cout<<"----Empleado eliminado de forma exitosa.---- "<<endl;
			cout<<" "<<endl;
			return;
		}
	}
	cout<<"No se encontro un empleado con ID: "<<ID<<endl;
	cout<<" "<<endl;
}

void consultarInformacionCompleta() {
    string ID;
    cout<<"Ingrese el ID del empleado: ";
    cin>>ID;
    
    for(int i=0; i<(int)empleados.size(); i++){
        if(empleados[i].getId()==ID){
            cout<<" INFORMACION COMPLETA "<<endl;
            cout<<"ID: "<<empleados[i].getId()<<endl;
            cout<<"Nombre: "<<empleados[i].getNombre()<<endl;
            cout<<"Apellido: "<<empleados[i].getApellido()<<endl;
            cout<<"Telefono: "<< empleados[i].getTelefono()<<endl;
            cout<<"Cargo: "<<empleados[i].getCargo()<<endl;
            cout<<"Salario: $"<<empleados[i].getSalario()<<endl;
            cout<<" "<<endl;
            return;
        }
    }
    cout<<"No se encontro un empleado con ID: "<<ID<<endl;
    cout<<" "<<endl;
}

void estadisticasEmpleados(){
	double mayor = 0;
	int indice;
	double suma = 0;
	map<string, int>conteoCargos;
	double promedio = 0;

	if(empleados.empty()){
		cout<<"No hay empleados registrados."<<endl;
	}else{
	for(int i=0; i<(int)empleados.size(); i++){
		suma = suma + empleados[i].getSalario();
		conteoCargos[empleados[i].getCargo()] = conteoCargos[empleados[i].getCargo()]+1;
		if(empleados[i].getSalario()>mayor){
			mayor = empleados[i].getSalario();
			indice = i;
		}
	}
	promedio = suma/empleados.size();	
	
	cout<<"Estadisticas de empleados"<<endl;
	cout<<"-Empleado con mayor salario: "<<endl;
	cout<<"ID: "<<empleados[indice].getId()<<endl;
	cout<<"Nombre: "<<empleados[indice].getNombre()<<" "<<empleados[indice].getApellido()<<endl;
	cout<<"Cargo: "<<empleados[indice].getCargo()<<endl;
	cout<<"Salario: $"<<empleados[indice].getSalario()<<endl;
	cout<<" "<<endl;
	cout<<"- Salario Promedio: $"<<promedio<<endl;
	cout<<" "<<endl;
	cout<<"- Conteo por cargos: "<<endl;
	for(auto& par : conteoCargos){
		cout<<par.first<<": "<<par.second<<" empleados"<<endl;
		cout<<" "<<endl;
	}
	}	
}

void menuEmpleados(){
	
	int opcion;
	
	do{
		cout<<"Menu Empleados"<<endl;
		cout<<"1. Agregar empleado "<<endl;
		cout<<"2. Mostrar empleados"<<endl;
		cout<<"3. Modificar Empleados"<<endl;
		cout<<"4. Eliminar empleados"<<endl;
		cout<<"5. Consultar informacion completa"<<endl;
		cout<<"6. Estadisticas"<<endl;
		cout<<"7. Volver al menu principal"<<endl;
		cout<<"Seleccione una opcion: ";
		cin>>opcion;
		cout<<" "<<endl;
		
		switch(opcion){
			
			case 1: agregarEmpleado();
			break;
			
			case 2: mostrarEmpleados();
			break;
			
			case 3: modificarEmpleado();
			break;
			
			case 4: eliminarEmpleado();
			break;
				
		    case 5: consultarInformacionCompleta();
		    break;
				
			case 6: estadisticasEmpleados();
			break;
				
			case 7: cout<<"Volviendo al menu principal..."<<endl;
			cout<<" "<<endl;
			break;
			
			default: cout<<"Opcion no disponible "<<endl;
			cout<<" "<<endl;
		}
		
	}while(opcion !=7);
	
}

void registrarVenta() {
    string idCliente, fecha;
    int nuevoIdVenta, idProducto, cantidad, seguir, indiceCliente, indiceProducto;
    
    if(clientes.empty()){
        cout<<"No hay clientes registrados. No se puede registrar la venta."<<endl;
        cout<<" "<<endl;
        return;
    }
    
    if(productos.empty()){
        cout<<"No hay productos registrados. No se puede registrar la venta."<<endl;
        cout<<" "<<endl;
        return;
    }
    
    cout<<"Clientes Disponibles:"<<endl;
    for(int i = 0; i<(int)clientes.size(); i++){
        cout<<"ID: "<<clientes[i].getId()<<endl;
        cout<<"Nombre: "<<clientes[i].getNombre()<<" "<<clientes[i].getApellido()<<endl;
        cout<<" "<<endl;
    }
    cout<<"Ingrese el ID del cliente: ";
    cin>>idCliente;
    indiceCliente = -1;
   
    for(int i=0; i<(int)clientes.size(); i++){
        if(clientes[i].getId() == idCliente){
            indiceCliente = i;
            break;
        }
    }
    
    if(indiceCliente == -1){
        cout<<"Cliente no encontrado."<<endl;
        cout<<" "<<endl;
        return;
    }
    
    nuevoIdVenta = nextIdVenta;
    nextIdVenta++;
    cout<<"Ingrese la fecha (YYYY-MM-DD): ";
    cin>>fecha;
    Venta nuevaVenta(nuevoIdVenta, fecha, idCliente);  
    seguir = 1;
    
    do{
        cout<<"Productos disponibles:"<<endl;
        for(int i=0; i<(int)productos.size(); i++){
            cout<<"ID: "<<productos[i].getId()<<endl; 
            cout<<"Nombre: "<<productos[i].getNombre()<<endl; 
            cout<<"Precio: $"<< productos[i].getPrecio()<<endl; 
            cout<<"Stock: "<<productos[i].getStock()<<endl;
            cout<<" "<<endl;
        }
        
        cout<<"Ingrese el ID del producto (0 para terminar): "<<endl;;
        cin>>idProducto;
        
        if(idProducto == 0){
            seguir = 0;
        }else{
            cout<<"Ingrese la cantidad: "<<endl;
            cin>>cantidad;
            indiceProducto = -1;
            
            for(int i = 0; i<(int)productos.size(); i++){
                if(productos[i].getId() == idProducto){
                    indiceProducto = i;
                    break;
                }
            }
            
            if(indiceProducto == -1) {
            cout<<"Producto no encontrado"<<endl;
            cout<<" "<<endl;
            }else if(productos[indiceProducto].getStock()<cantidad){
                cout<<"Stock insuficiente. Stock disponible: "<<productos[indiceProducto].getStock()<<endl;
                cout<<" "<<endl;
            }else{
                productos[indiceProducto].actualizarStock(-cantidad);
                
                for(int j=0; j<cantidad; j++){
                    nuevaVenta.agregarProducto(productos[indiceProducto]);
                }
                
                cout<<"Producto agregado. Stock restante: "<<productos[indiceProducto].getStock()<<endl;
                cout<<" "<<endl;
            }
        }
    } while(seguir == 1);
    
    nuevaVenta.calcularTotal();
    ventas.push_back(nuevaVenta);
    clientes[indiceCliente].agregarCompra(nuevaVenta);
    
    cout<<"----Venta Registrada de forma exitosa.---- "<<endl;
    nuevaVenta.mostrarResumen();
}

void eliminarVenta() {
    int id;
    string idCliente;
    cout<<"Ingrese el ID de la venta a eliminar: "<<endl;
    cin>>id;
    
    for(int i=0; i<(int)ventas.size(); i++){
        if(ventas[i].getId()==id){
             idCliente = ventas[i].getIdCliente();
            
        
             vector<Producto>& productosVendidos = ventas[i].getProductos();
            for(int j=0; j<(int)productosVendidos.size(); j++){
                int idProducto = productosVendidos[j].getId();
                for(int k=0; k<(int)productos.size(); k++){
                    if(productos[k].getId()==idProducto){
                        productos[k].actualizarStock(1);  
                        break;
                    }
                }
            }
            for(int c=0; c<(int)clientes.size(); c++){
                if(clientes[c].getId() == idCliente){
                    clientes[c].eliminarVentaHistorial(id);
                    break;
                }
            }
            ventas.erase(ventas.begin() + i);
            cout<<"Venta eliminada correctamente. Stock revertido."<<endl;
            cout<<" "<<endl;
            return;
        }
    }
    cout<<"No se encontró una venta con ID "<<id<<endl;
    cout<<" "<<endl;
}

void filtrarVentasCliente() {
    string idCliente;
    bool encontrado = false;
    cout<<"Ingrese el ID del cliente: "<<endl;
    cin>> idCliente;
    
    cout<<"Ventas del cliente "<<idCliente<<endl;
    
    for(int i=0; i<(int)ventas.size(); i++){
        if (ventas[i].getIdCliente() == idCliente){
            ventas[i].mostrarResumen();
            encontrado = true;
        }
    }
    
    if (encontrado == false) {
        cout<<"No se encontraron ventas para el cliente con ID: "<<idCliente<<endl;
        cout<<" "<<endl;
    }
}

void filtrarVentasFecha(){
    string fechaInicio, fechaFin, fechaVenta;
     bool encontrado = false;
    cout<<"Ingrese la fecha de inicial (YYYY-MM-DD): "<<endl;
    cin>>fechaInicio;
    cout<<"Ingrese la fecha de final (YYYY-MM-DD): "<<endl;
    cin>>fechaFin;
    cout<<" "<<endl;
    cout<<"Ventas entre "<<fechaInicio<<" Y "<<fechaFin<<" "<<endl;
    
    for(int i = 0; i<(int)ventas.size(); i++){
         fechaVenta = ventas[i].getFecha();
        if(fechaVenta >= fechaInicio && fechaVenta <= fechaFin){
            ventas[i].mostrarResumen();
            encontrado = true;
        }
    }
    
    if(encontrado == false){
        cout<<"No hay ventas en ese rango de fechas."<<endl;
        cout<<" "<<endl;
    }
}

void estadisticasVentas(){
    if(ventas.empty()){
        cout<<"No hay ventas registradas."<<endl;
        cout<<" "<<endl;
        return;
    }
    cout<<"Total vendido por categoria"<<endl;
    map<string, double>totalPorCategoria;
    
    for(int i=0; i<(int)ventas.size(); i++){
         vector<Producto>& productosVendidos = ventas[i].getProductos();
        for(int j=0; j<(int)productosVendidos.size(); j++){
            string cat = productosVendidos[j].getCategoria();
            totalPorCategoria[cat] = totalPorCategoria[cat] + productosVendidos[j].getPrecio();
        }
    }
    
    for(auto &p : totalPorCategoria){
        cout<<p.first<<": $"<<p.second<<endl;
        cout<<" "<<endl;
    }
    
    cout<<"Producto mas vendido"<<endl;
    map<int, int>cantidadVendida;
    
    for(int i = 0; i<(int)ventas.size(); i++){
         vector<Producto>& productosVendidos = ventas[i].getProductos();
        for(int j=0; j<(int)productosVendidos.size(); j++){
            cantidadVendida[productosVendidos[j].getId()]++;
        }
    }
    
    if(cantidadVendida.empty()){
        cout<<"No hay productos vendidos."<<endl;
        cout<<" "<<endl;
    }else{
        int maxCantidad = 0;
        for(auto &p : cantidadVendida){
            if(p.second > maxCantidad){
                maxCantidad = p.second;
            }
        }
        vector<int>idsMasVendidos;
         for(auto &p : cantidadVendida){
            if(p.second == maxCantidad){
                idsMasVendidos.push_back(p.first);
            }
           } 
           if(idsMasVendidos.size() == 1){
           	int idMasVendido = idsMasVendidos[0];
           	string nombreProducto = "Desconocido";
           for(int i = 0; i<(int)productos.size(); i++) {
            if(productos[i].getId() == idMasVendido){
                nombreProducto = productos[i].getNombre();
                break;
            }
		   }
        cout<<"Producto: "<<nombreProducto<<endl;
        cout<<"Cantidad vendida: "<<maxCantidad<<" unidades"<<endl;
        
        
        }else{
        	cout<<"Productos mas vendidos (empate):"<<endl;
        	for(int i=0; i<(int)idsMasVendidos.size(); i++){
        		int id= idsMasVendidos[i];
        		string nombreProducto = "Desconocido";
        		for(int j=0; j<(int)productos.size(); j++){
			if(productos[j].getId()==id){
				nombreProducto = productos[j].getNombre();
				break;
			}
				}
				cout<<"-"<<nombreProducto<<" ("<<maxCantidad<<" unidades)"<<endl;
			}
		}
        cout<<" "<<endl;
        
    }
    cout<<"Cliente que mas compra: "<<endl;
    double maxGasto = 0;
    vector<string>nombresClientes;
    double gasto;
    
    for(int i=0; i<(int)clientes.size(); i++){
         gasto = clientes[i].totalGastado();
        if(gasto > maxGasto){
            maxGasto = gasto;
        }
    }
    for(int i=0; i<(int)clientes.size(); i++){
    	gasto = clientes[i].totalGastado();
    	if(gasto==maxGasto){
    		string nombre = clientes[i].getNombre()+" "+clientes[i].getApellido();
    		nombresClientes.push_back(nombre);
		}
	}
    if(maxGasto == 0){
        cout<<"No hay clientes con compras registradas."<<endl;
        cout<<" "<<endl;
    }else if(nombresClientes.size()==1){
        cout<<"Cliente: "<<nombresClientes[0]<<endl;
        cout<<"Total gastado: $"<<maxGasto<<endl;
        cout<<" "<<endl;
    }else{
    	cout<<"Clientes que mas compraron(empate):"<<endl;
    	for(int i=0; i<(int)nombresClientes.size(); i++){
    		cout<<"-"<<nombresClientes[i]<<" ($"<<maxGasto<<")"<<endl;
    		cout<<" "<<endl;
		}
	}
}

void menuVentas(){
	int opcion;
	
	do{
		cout<<"Menu Ventas"<<endl;
		cout<<"1. Registrar venta "<<endl;
		cout<<"2. Eliminar venta"<<endl;
		cout<<"3. Filtrar venta por cliente"<<endl;
		cout<<"4. Filtrar venta por fecha"<<endl;
		cout<<"5. Estadisticas"<<endl;
		cout<<"6. Volver al menu principal "<<endl;
		cout<<"Seleccione una opcion: ";
		cin>>opcion;
		cout<<" "<<endl;
		
		switch(opcion){
			
			case 1: registrarVenta();
			break;
			
			case 2: eliminarVenta();
			break;
				
			case 3: filtrarVentasCliente();
			break;	
				
			case 4: filtrarVentasFecha();
			break;	
				
			case 5: estadisticasVentas();
			break;	
				
			case 6: cout<<"Volviendo al menu principal..."<<endl;
			cout<<" "<<endl;
			break;
			
			default: cout<<"Opcion no disponible "<<endl;
			cout<<" "<<endl;
		}
		
	}while(opcion !=6);
	
}

void costoTotalInventario(){
    if(productos.empty()){
        cout<<"No hay productos registrados."<<endl;
        cout<<" "<<endl;
        return;
    }
    
    double total = 0.0;
    for(int i=0; i<(int)productos.size(); i++){
        total = total + (productos[i].getStock() * productos[i].getPrecio());
    }
    cout<<"Costo total del inventario: $"<<total<<endl;
    cout<<" "<<endl;
}

void promedioVentasCliente() {
    if(ventas.empty()){
        cout<<"No hay ventas registradas."<<endl;
        cout<<" "<<endl;
        return;
    }
    
    map<string, int>comprasPorCliente;
    
    for(int i = 0; i<(int)ventas.size(); i++){
        comprasPorCliente[ventas[i].getIdCliente()]++;
    }
    
    int totalCompras = 0;
    for(auto &p : comprasPorCliente){
        totalCompras = totalCompras + p.second;
    }
    
    int cantidadClientes = comprasPorCliente.size();
    if(cantidadClientes == 0){
        cout<<"No hay clientes con ventas registradas."<<endl;
        cout<<" "<<endl;
    }else{
        double promedio = (double)totalCompras / cantidadClientes;
        cout<<"Promedio de ventas por cliente: "<<promedio<<" ventas"<<endl;
        cout<<" "<<endl;
    }
}
  
void promedioPreciosCategoria(){
     string cat, categoria;
	 double precio, suma, promedio;
	 int cantidad;
    if(productos.empty()){
        cout<<"No hay productos registrados."<<endl;
        cout<<" "<<endl;
        return;
    }
    map<string, double>sumaPrecios;
    map<string, int>cantidadProductos;
    
    for(int i = 0; i<(int)productos.size(); i++){
         cat = productos[i].getCategoria();
         precio = productos[i].getPrecio();
        sumaPrecios[cat] = sumaPrecios[cat] + precio;
        cantidadProductos[cat] = cantidadProductos[cat] + 1;
    }
    
    cout<<"Promedio de precios por categoria: "<<endl;
    for(auto &p : sumaPrecios){
         categoria = p.first;
         suma = p.second;
         cantidad = cantidadProductos[categoria];
         promedio = suma / cantidad;
        cout<<categoria<< ": $"<<promedio<<endl;
        cout<<" "<<endl;
    }
}
       
void filtrarMargen() {
    if(productos.empty()){
        cout<<"No hay productos registrados."<<endl;
        cout<<" "<<endl;
        return;
    }
    double margenRef, margen;
    int opcion;
    cout<<"Ingrese el margen de referencia: "<<endl;
    cin>>margenRef;
    
    cout<<"Seleccione una opcion:"<<endl;
    cout<<"1. Filtrar productos con margen mayor a "<<margenRef<<endl;
    cout<<"2. Filtrar productos con margen menor a "<<margenRef<<endl;
    cout<<"3. Filtrar productos con margen igual a "<<margenRef<<endl;
    cout<<"Opcion: ";
    cin>>opcion;
    cout<<" "<<endl;
    
    string comparacion;
    switch(opcion){
        case 1: comparacion = "mayor a"; 
		break;
        case 2: comparacion = "menor a"; 
		break;
        case 3: comparacion = "igual a"; 
		break;
        default:
        cout<<"Opcion no disponible."<<endl;
        cout<<" "<<endl;
            return;
    }
    
    cout<<"Productos con margen "<<comparacion<<" "<<margenRef<<endl;
    bool encontrado = false;
    
    for(int i=0; i<(int)productos.size(); i++){
         margen = productos[i].margen();
        if(opcion == 1 && margen > margenRef){
            cout<<"ID: "<<productos[i].getId()<<endl;
            cout<<"Nombre: "<<productos[i].getNombre()<<endl;
            cout<<"Precio: $"<<productos[i].getPrecio()<<endl;
            cout<<"Costo: $"<<productos[i].getCosto()<<endl;
            cout<<"Margen: $"<<margen<<endl;
            cout<<" "<<endl;
            encontrado = true;
        }else if(opcion == 2 && margen < margenRef){
            cout<<"ID: "<<productos[i].getId()<<endl;
            cout<<"Nombre: "<<productos[i].getNombre()<<endl;
            cout<<"Precio: $"<<productos[i].getPrecio()<<endl;
            cout<<"Costo: $"<<productos[i].getCosto()<<endl;
            cout<<"Margen: $"<<margen<<endl;
            cout<<" "<<endl;
            encontrado = true;
        }else if(opcion == 3 && margen == margenRef){
            cout<<"ID: "<<productos[i].getId()<<endl;
            cout<<"Nombre"<<productos[i].getNombre()<<endl;
            cout<<"Precio: $"<<productos[i].getPrecio()<<endl;
            cout<<"Costo: $"<<productos[i].getCosto()<<endl;
            cout<<"Margen: $"<<margen<<endl;
            cout<<" "<<endl;
            encontrado = true;
        }
    }
    if(encontrado==false) {
        cout<<"No hay productos que cumplan la condicion."<<endl;
        cout<<" "<<endl;
    }
}


void menuReportes(){
	
		int opcion;
	
	do{
		cout<<"Menu Reportes y Estadisticas"<<endl;
		cout<<"1. Calcular costo total de inventario "<<endl;
		cout<<"2. Promedio de ventas por cliente"<<endl;
		cout<<"3. Promedio de precios por categoria"<<endl;
		cout<<"4. Filtrar productos segun margen de ganancia"<<endl;
		cout<<"5. Volver al menu principal "<<endl;
		cout<<"Seleccione una opcion: ";
		cin>>opcion;
		cout<<" "<<endl;
		
		switch(opcion){
			
			case 1: costoTotalInventario();
			break;
			
			case 2: promedioVentasCliente();
			break;
				
			case 3: promedioPreciosCategoria();
			break;	
				
			case 4: filtrarMargen();
			break;	
						
			case 5: cout<<"Volviendo al menu principal..."<<endl;
			cout<<" "<<endl;
			break;
			
			default: cout<<"Opcion no disponible "<<endl;
			cout<<" "<<endl;
		}
		
	}while(opcion !=5);
	
}

void guardarProductos(){
	json j=json::array();
	for(int i=0; i<(int)productos.size(); i++){
		json obj;
		obj["id"] = productos[i].getId();
		obj["nombre"] = productos[i].getNombre();
		obj["categoria"] = productos[i].getCategoria();
		obj["precio"] = productos[i].getPrecio();
		obj["costo"]=productos[i].getCosto();
		obj["stock"]= productos[i].getStock();
		j.push_back(obj);
	}
	ofstream archivo("data/productos.json");
	if(archivo.is_open()){
		archivo<<j.dump(4);
		archivo.close();
	}
}	

void cargarProductos(){
	ifstream archivo("data/productos.json");
	if(!archivo.is_open())
	return;
	json j;
	archivo >> j;
	productos.clear();
	idsProductosOcupados.clear();
	for(int i=0; i<(int)j.size(); i++){
		int id = j[i]["id"];
		string nombre = j[i]["nombre"];
		string categoria= j[i]["categoria"];
		double precio = j[i]["precio"];
		double costo = j[i]["costo"];
		int stock = j[i]["stock"];
		productos.push_back(Producto(id, nombre, categoria, precio, costo, stock));
		idsProductosOcupados[id] = true;
	}
	archivo.close();
}
 
 void guardarClientes(){
 	json j = json::array();
 	for(int i=0; i<(int)clientes.size(); i++){
 		json obj;
 		obj["id"] = clientes[i].getId();
 		obj["nombre"] = clientes[i].getNombre();
		obj["apellido"] = clientes[i].getApellido();
		obj["telefono"] = clientes[i].getTelefono();
		obj["correo"] = clientes[i].getCorreo();
		j.push_back(obj);
	 }
	 ofstream archivo("data/clientes.json");
	 if(archivo.is_open()){
	 	archivo << j.dump(4);
	 	archivo.close();
	 }
 }
 
 void cargarClientes(){
 	ifstream archivo("data/clientes.json");
	if(!archivo.is_open())
	return;
	json j;
	archivo >> j;
	clientes.clear();
	for(int i=0; i<(int)j.size(); i++){
		string id = j[i]["id"];
		string nombre = j[i]["nombre"];
		string apellido = j[i]["apellido"];
		string telefono = j[i]["telefono"];
		string correo = j[i]["correo"];
		clientes.push_back(Cliente(nombre, apellido, id, telefono, correo));	
 }
archivo.close();
}

void guardarEmpleados(){
	json j = json::array();
 	for(int i=0; i<(int)empleados.size(); i++){
 		json obj;
 		obj["id"] = empleados[i].getId();
 		obj["nombre"] = empleados[i].getNombre();
		obj["apellido"] = empleados[i].getApellido();
		obj["telefono"] = empleados[i].getTelefono();
		obj["cargo"] = empleados[i].getCargo();
		obj["salario"] = empleados[i].getSalario();
		j.push_back(obj);
	 }
	 ofstream archivo("data/empleados.json");
	 if(archivo.is_open()){
	 	archivo << j.dump(4);
	 	archivo.close();
	 }
}

void cargarEmpleados(){
ifstream archivo("data/empleados.json");
	if(!archivo.is_open())
	return;
	json j;
	archivo >> j;
	empleados.clear();
	for(int i=0; i<(int)j.size(); i++){
		string id = j[i]["id"];
		string nombre = j[i]["nombre"];
		string apellido = j[i]["apellido"];
		string telefono = j[i]["telefono"];
		string cargo = j[i]["cargo"];
		double salario = j[i]["salario"];
		empleados.push_back(Empleado(nombre, apellido, id, telefono, cargo, salario));	
 }
       archivo.close();
}

void guardarVentas(){
	json j= json::array();
	for(int i=0; i<(int)ventas.size(); i++){
		json obj;
		obj["id"] = ventas[i].getId();
 		obj["fecha"] = ventas[i].getFecha();
		obj["idCliente"] = ventas[i].getIdCliente();
		obj["total"] = ventas[i].getTotal();
		json prodIds=json ::array();
		vector<Producto>& prods=ventas[i].getProductos();
		for(int j=0; j<(int)prods.size(); j++){
			prodIds.push_back(prods[j].getId());
		}
		obj["productosIds"] = prodIds;
		j.push_back(obj);
	}
	ofstream archivo("data/ventas.json");
	if(archivo.is_open()){
		archivo<<j.dump(4);
		archivo.close();
	}
}

void cargarVentas(){
	ifstream archivo("data/ventas.json");
	if(!archivo.is_open())
	return;
	json j;
	archivo >> j;
	ventas.clear();
	int maxId=0;
	for(int i=0; i<(int)j.size(); i++){
		int id = j[i]["id"];
		if(id>maxId){
			maxId = id;
		}
		string fecha = j[i]["fecha"];
		string idCliente = j[i]["idCliente"];
		Venta venta(id, fecha, idCliente);
		json prodIds= j[i]["productosIds"];
		for(int k=0; k<(int)prodIds.size(); k++){
			int idProd=prodIds[k];
			for(int p=0; p<(int)productos.size(); p++){
				if(productos[p].getId()==idProd){
					venta.agregarProducto(productos[p]);
					break;
				}
			}
		}
		venta.calcularTotal();
		ventas.push_back(venta);
		for(int c=0; c<(int)clientes.size(); c++){
			if(clientes[c].getId()==idCliente){
				clientes[c].agregarCompra(venta);
				break;
			}
		}
	}
	archivo.close();
	nextIdVenta = maxId + 1;
}