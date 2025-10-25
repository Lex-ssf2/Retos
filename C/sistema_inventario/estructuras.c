#include "estructuras.h"

int inicializarInventario(Inventario *i){
	if((*i).cabeza != NULL){
		printf("Ya esta inicializado");
		return -1;
	}
	NodoInventario *cabecera = (NodoInventario*)malloc(sizeof(NodoInventario));
	creaProducto(&(*cabecera).producto,0,"null",.0,0);
	(*cabecera).sig = NULL;	
	(*cabecera).ant = NULL;
	(*i).cabeza = cabecera;
	(*i).cola = cabecera;
	(*i).total_productos = 0;
	printf("No tiene cabecera");
	return 0;
};

void creaProducto(Producto **p, unsigned int id, const char *nombre, float precio, unsigned int cantidad){
	*p = (Producto*)malloc(sizeof(Producto));
	(**p).id = id;
	strlcpy((**p).nombre,nombre,MAX_CADENA);
	(**p).precio = precio;
	(**p).cantidad = cantidad;
}

void eliminaProducto(Producto *p){
	free(p);
}

void agregarProducto(Inventario* inv, unsigned int id, const char* nombre, float precio, unsigned int cantidad){
	NodoInventario *actual = (*inv).cabeza;
	NodoInventario *nuevo;
	Producto *pActual;
	if(id == 0) {
		printf("Coloca un valor valido");
		return;
	}
	
	while((*actual).sig != NULL){
		pActual = (*actual).producto;
		if((*pActual).id == id){
			printf("Son iguales");
			(*pActual).cantidad += cantidad;
			return;
		}
		actual = (*actual).sig;
	};
	// No me gusta pero imaginemos que es una prueba entonces por el apuro
	pActual = (*actual).producto;
	if((*pActual).id == id){
		printf("Son iguales");
		(*pActual).cantidad += cantidad;
		return;
	}
	
	nuevo = (NodoInventario*)malloc(sizeof(NodoInventario));
	creaProducto(&(*nuevo).producto,id,nombre,precio,cantidad);
	(*nuevo).sig = NULL;
	(*nuevo).ant = actual;
	(*actual).sig = nuevo;
	(*inv).cola = nuevo;
	(*inv).total_productos++;
}

void eliminar_producto(Inventario* inv, unsigned int id){
	NodoInventario *actual = (*inv).cabeza;
	NodoInventario *nuevo;
	Producto *pActual;
	if(id == 0) {
		printf("Coloca un valor valido");
		return;
	}
	while((*actual).sig != NULL){
		pActual = (*actual).producto;
		if((*pActual).id == id){
			(*(*actual).ant).sig = (*actual).sig;
			(*(*actual).sig).ant = (*actual).ant;
			free((*actual).producto);
			free(actual);
			return;
		}
		actual = (*actual).sig;
	};
	pActual = (*actual).producto;
	if((*pActual).id == id){
		(*(*actual).ant).sig = (*actual).sig;
		(*(*actual).sig).ant = (*actual).ant;
		free((*actual).producto);
		free(actual);
		return;
	}
}

void mostrar_inventario(const Inventario* inv){
	NodoInventario *actual = (*inv).cola;
	Producto *pActual;
	while(actual != (*inv).cabeza){
		pActual = (*actual).producto;
		printf("\n\n %s %d", (*pActual).nombre ,(*pActual).id);
		actual = (*actual).ant;
	}
}

void liberar_inventario(Inventario* inv){
	NodoInventario *actual = (*inv).cola;
	NodoInventario *tmp;
	Producto *pActual;
	while(actual != (*inv).cabeza){
		tmp = (*actual).ant;
		free((*actual).producto);
		free(actual);
		actual = tmp;
	}
	(*(*inv).cabeza).sig = NULL;
}