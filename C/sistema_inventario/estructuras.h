#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CADENA 50

typedef struct {
	unsigned int id;
	char nombre[MAX_CADENA];
	float precio;
	unsigned int cantidad;
} Producto;

void creaProducto(Producto **p, unsigned int id, const char *nombre, float precio, unsigned int cantidad);
void eliminaProducto(Producto *p);

typedef struct NodoInventario {
	Producto *producto;
	struct NodoInventario *sig;
	struct NodoInventario *ant;
} NodoInventario;

typedef struct {
	NodoInventario *cabeza;
	NodoInventario *cola;
	unsigned int total_productos;
} Inventario;

int inicializarInventario(Inventario *i);
void agregarProducto(Inventario* inv, unsigned int id, const char* nombre, float precio, unsigned int cantidad);
void eliminar_producto(Inventario* inv, unsigned int id);
void mostrar_inventario(const Inventario* inv);
void liberar_inventario(Inventario* inv);
#endif