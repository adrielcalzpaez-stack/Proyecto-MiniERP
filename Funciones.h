#ifndef FUNCIONES_H
#define FUNCIONES_H
 
//menu 
void menuProductos();
void menuClientes();
void menuEmpleados();
void menuVentas();
void menuReportes();

//Producto
void agregarProducto();
void mostrarProductos();
void modificarProducto();
void eliminarProducto();
void filtrarCategoria();
void filtrarNombreParcial();
void filtrarRango();
void stockCritico();
void calcularProducto();
int obtenerNuevoId();//Producto

//Cliente
void agregarcliente();
void mostrarClientes();
void modificarCliente();
void eliminarCliente();
void mostrarHistorial();
void filtrarMonto();
void filtrarCompras();
void totalGastado();

//Empleado
void agregarEmpleado();
void modificarEmpleado();
void eliminarEmpleado();
void mostrarEmpleados();
void consultarInformacionCompleta();
void estadisticasEmpleados();

//Ventas
void registrarVenta();
void eliminarVenta();
void filtrarVentasClientes();
void filtrarVentasFecha();
void estadisticasVentas();

//Reportes
void costoTotalInventario();
void promedioVentasCliente();
void promedioPreciosCategoria();
void filtrarMargen();

//Persistencia		
void guardarProductos();
void cargarProductos();
void guardarClientes();
void cargarClientes();
void guardarEmpleados();
void cargarEmpleados();
void guardarVentas();
void cargarVentas();					

#endif