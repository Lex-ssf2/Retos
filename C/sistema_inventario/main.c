#include <stdio.h>
#include "estructuras.h"

int main(int argc, int *argv[]){
	Inventario i;
	inicializarInventario(&i);
	inicializarInventario(&i);
	agregarProducto(&i,7,"hola",0.5,10);
	agregarProducto(&i,5,"test",0.5,10);
	agregarProducto(&i,5,"test",0.5,10);
	agregarProducto(&i,5,"test",0.5,10);
	agregarProducto(&i,8,"adios",0.5,10);
	mostrar_inventario(&i);
	eliminar_producto(&i,5);
	agregarProducto(&i,5,"test",0.5,10);
	agregarProducto(&i,5,"test",0.5,10);
	agregarProducto(&i,5,"test",0.5,10);
	mostrar_inventario(&i);
	liberar_inventario(&i);
	agregarProducto(&i,8,"sonic",0.5,10);
	mostrar_inventario(&i);
	return 0;
}