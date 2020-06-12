#include <stdio.h>
#include "estructura.h"

/*
	Función que transforma una imagen RGB a escala de grises.
	Entrada: Matriz con el contenido de la imagen.
	Salida: Matriz con el contenido de la imagen.
*/
rgb ** conversionRGBAGris(rgb ** matriz, int filas, int columnas){

	int i,j,R,G,B;
	float Y;
	for(i = 0; i < filas; i++){
		for(j = 0; j < columnas; j++){

			R = matriz[i][j].red;
			G = matriz[i][j].green;
			B = matriz[i][j].blue;
			Y = R*0.3 + G*0.59 + B*0.11;
			matriz[i][j].grey = Y;
		}
	}
	return matriz;
}
