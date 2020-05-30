#include <stdio.h>
#include "estructura.h"

/*
	Función que determina si la imagen es o no nearly black.

	Entradas: - Matriz de rgb que representa la imagen.
		      - Entero como el número de filas de la imagen.
		      - Entero como el número de columnas de la imagen.
		      - Flotante como el umbral de clasificación.
			  - Cadena de caracteres como el nombre de la imagen.

	Salida: Vacio.
*/
void clasificar(rgb ** matriz, int filas, int columnas, float umbral, char * nombre_imagen){

	int total_pixeles = filas*columnas;
	int num_pixeles_negros;
	double porcentaje_pixeles_negros = 0;
	int i, j;

	for(i = 0; i < filas; i++){
		for(j = 0; j < columnas; j++){
			if(matriz[i][j].pixel == 0){
				num_pixeles_negros++;
			}
		}
	}
	porcentaje_pixeles_negros = num_pixeles_negros/total_pixeles*100;

	if(porcentaje_pixeles_negros >= umbral){
		printf("%s is nearly black\n",nombre_imagen);
	}
	else{
		printf("%s is NOT nearly black\n",nombre_imagen);
	}
}