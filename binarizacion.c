#include <stdio.h>
#include "estructura.h"

/*
	Función que realiza la binarización de la imagen.

	Entradas: - Matriz de rgb que representa la imagen.
			  - Entero como el número de filas.
			  - Entero como el número de columnas.
			  - Flotante como el umbral de binarización.

	Salida: Matriz de rgb que representa la imagen binarizada.
*/
rgb ** binarizar(rgb ** matriz, int filas, int columnas, float umbral){

	int i,j;
	for(i = 0; i < filas; i++){
		for(j = 0; j < columnas; j++){

			if(matriz[i][j].pixel > umbral){

				matriz[i][j].pixel = 255;
			}
			else{
				matriz[i][j].pixel = 0;
			}
		}
	}
	return matriz;
}