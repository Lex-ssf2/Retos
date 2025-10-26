#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <arpa/inet.h>

#define NUM_PAQUETES 2
#define TAMANO_PAQUETE 4

typedef struct {
    unsigned int id_sensor;     // 4 bits
    unsigned int estado_alerta; // 1 bit
    unsigned int codigo_error;  // 3 bits
    unsigned int temperatura;   // 8 bits
    unsigned int nivel_bateria; // 8 bits
    unsigned char checksum;     // 8 bits
} DatosTelemetria;

uint32_t convertir_endianness(uint32_t valor);
DatosTelemetria decodificar_paquete(uint32_t paquete_raw);
int procesar_telemetria(const unsigned char *buffer, size_t buffer_len, DatosTelemetria *resultados, size_t max_resultados);

int main(int argc, char *argv[]){
	const unsigned char entrada_buffer[NUM_PAQUETES * TAMANO_PAQUETE] = {
        0x41, 0x85, 0x5E, 0x2F,
        0x70, 0x40, 0xAA, 0x10
    };
	
	DatosTelemetria resultados[NUM_PAQUETES];
	int cantidad = procesar_telemetria(entrada_buffer,sizeof(entrada_buffer)/sizeof(entrada_buffer[0]),resultados,NUM_PAQUETES);
	printf("El total de datos procesados son : %d\n",cantidad);
	for(size_t i = 0; i < NUM_PAQUETES; ++i){
		DatosTelemetria actual = resultados[i];
		printf("\nID del sensor: %d\nEstado Alerta: %d\nCodigo Error: %d\nTemperatura: %d\nNivel de Bateria: %d\n Checksum: %d\n",actual.id_sensor,actual.estado_alerta,actual.codigo_error,actual.temperatura,actual.nivel_bateria,actual.checksum);
	}
	return 0;
}

uint32_t convertir_endianness(uint32_t valor){
	uint32_t resultado = 0;
	resultado = ((valor >> 24) & 0xFF) | ((valor >> 8) & 0xFF00) | ((valor << 8) & 0xFF0000) | ((valor << 24) & 0xFF000000);
	return resultado;
}
DatosTelemetria decodificar_paquete(uint32_t paquete_raw){
	DatosTelemetria salida;
	salida.checksum = paquete_raw & 0xFF;
	salida.nivel_bateria = (paquete_raw >> 8) & 0xFF;
	salida.temperatura = (paquete_raw >> 8*2) & 0xFF;
	salida.codigo_error = (paquete_raw >> 8*3) & 0x08;
	salida.estado_alerta = (paquete_raw >> (8*3 + 3)) & 0x02;
	salida.id_sensor = (paquete_raw >> (8*3 + 4)) & 0xF;
	return salida;
}
int procesar_telemetria(const unsigned char *buffer, size_t buffer_len, DatosTelemetria *resultados, size_t max_resultados){
	if(buffer_len % TAMANO_PAQUETE != 0)
		return -1;
	size_t i = 0;
	while(i < max_resultados){
		uint32_t valor;
		const unsigned char *entrada = buffer + (i * sizeof(uint32_t));
		memcpy(&valor,entrada,sizeof(uint32_t));
		valor = ntohl(valor);
		valor = convertir_endianness(valor);
		resultados[i] = decodificar_paquete(valor);
		++i;
	}
	return i;
}