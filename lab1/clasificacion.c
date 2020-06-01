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

	double total_pixeles = filas*columnas;
	int num_pixeles_negros = 0;
	float porcentaje_pixeles_negros;
	int i, j;

	for(i = 0; i < filas; i++){
		for(j = 0; j < columnas; j++){

			if(matriz[i][j].pixel == 0){
				num_pixeles_negros++;
			}
		}
	}
	porcentaje_pixeles_negros = (num_pixeles_negros/total_pixeles)*100;
	printf("\n\ntotal pixeles: %.0f",total_pixeles);
	printf("\nnumero_pixeles_negros: %i",num_pixeles_negros);
	printf("\nporcentaje_pixeles_negros: %f",porcentaje_pixeles_negros);

	if(porcentaje_pixeles_negros >= umbral){
		printf("\n%s is nearly black\n",nombre_imagen);
	}
	else{
		printf("\n%s is NOT nearly black\n",nombre_imagen);
	}
}