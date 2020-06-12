#include <stdio.h>
#include "estructura.h"

/*
	Función que imprime por pantalla si una imagen es nearly black o no.

	Entradas: - matriz: Matriz de rgb que representa la imagen.
		      - filas: Entero como el número de filas de la imagen.
		      - columnas: Entero como el número de columnas de la imagen.
		      - umbral: Flotante como el umbral de clasificación.
			  - nombre_imagen: Cadena de caracteres como el nombre de la imagen.
			  - num_img_actual: Entero indicando el número de la imagen a clasificar.

	Salida: Vacio.
*/
void clasificar(rgb ** matriz, int filas, int columnas, float umbral, char * nombre_imagen, int num_img_actual){

	double total_pixeles = filas*columnas;
	int num_pixeles_negros = 0;
	float porcentaje_pixeles_negros;
	int i, j;

	//Se suman los pixeles negros
	for(i = 0; i < filas; i++){
		for(j = 0; j < columnas; j++){

			if(matriz[i][j].pixel == 0){
				num_pixeles_negros++;
			}
		}
	}
	//Se obtiene el porcentaje de pixeles negros
	porcentaje_pixeles_negros = (num_pixeles_negros/total_pixeles)*100;

	//Se imprime resultado.
	if(num_img_actual == 1){
		printf("\n|      image      |  nearly black  |\n");
		printf("|----------------------------------|\n");
	}

	if(porcentaje_pixeles_negros >= umbral){
		printf("|  %s   |       yes      |\n",nombre_imagen);
	}
	else{
		printf("|  %s   |       no       |\n",nombre_imagen);
	}	
}