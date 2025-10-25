#define MAX_CADENA 50

typedef struct {
	unsigned int id;
	char nombre[MAX_CADENA];
	float precio;
	unsigned int cantidad;
} Producto;

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