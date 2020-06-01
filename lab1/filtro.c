#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estructura.h"

/*
	Entradas: -*nombre_archivo: Puntero a char representando el nombre del archivo que contiene la máscara de filtro Laplaciano

	Funcionamiento: Abre el archivo con la máscara de filtro para almacenarla.

	Salida: Una matriz de enteros representando la mascara.
*/
float ** leerArchivoMascara(char * nombre_archivo, float ** mascara){
	
	//Apertura de archivo.
	FILE * archivo = fopen(nombre_archivo,"r");

	if(archivo==NULL){
		perror("\nError al intentar leer el archivo de entrada.\n\n");
		exit(1);
	}

	int i;
	mascara = (float**)malloc(sizeof(float*)*3);
	for(i = 0; i < 3; i++){
		mascara[i] = (float*)malloc(sizeof(float)*3);
	}
	char buffer[100];
	char * str = (char*)malloc(sizeof(char));

	//Por cada línea del archivo.
	for(i = 0; i < 3; i++){

		fgets(buffer,10000,archivo);

		str = strtok(buffer," ");
		mascara[i][0] = atoi(str);

		str = strtok(NULL," ");
		mascara[i][1] = atoi(str);

		str = strtok(NULL,"\n");
		mascara[i][2] = atoi(str);
	}

	fclose(archivo);

	int j;
	printf("\nMascara laplaciano\n\n");
	for(i = 0; i < 3; i++){
		for(j = 0; j < 3; j++){
			printf("%.2f ",mascara[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	return mascara;

}


void imprimirFiltro(rgb ** matriz, int filas, int columnas){

	int i,j;
	for(i = 0; i < filas; i++){
		for(j = 0; j < columnas; j++){
			printf("%.2f ",matriz[i][j].pixel);
		}
	}
}

/*	
	Función que determina si un par de valores fila y columna se encuentran dentro de los límites de la imagen

	Entradas: -fila_actual: Entero que representa la fila a evaluar.
			  -columna_actual: Entero que representa la columna a evaluar.
			  -filas: Entero que representa el número de filas de la imagen.
			  -columnas: Entero que representa el número de columnas de la imagen.

	Salida:	Entero como flag  
*/
int dentroDeLimites(int fila_actual, int columna_actual, int filas, int columnas){

	return fila_actual >= 0 && fila_actual <= filas-1 && columna_actual >= 0 && columna_actual <= columnas-1;

}

/*
	Función que aplica el filtro laplaciano a la imagen

	Entradas: -Matriz de rgb representando la imagen
			  - Entero como el número  de filas de la imagen.
			  - Entero como el número de columnas de la imagen.
			  -Matriz de enteros representando la mascara espacial.

	Salida: La matriz de rgb que representa a la imagen.		  
*/
rgb ** filtroLaplaciano(rgb ** matriz, int filas, int columnas, float ** mascara){

	int i,j;
	float pixel;
	
	for(i = 0; i < filas; i++){
		for(j = 0; j < columnas; j++){

			pixel = matriz[i][j].grey*mascara[1][1];

			//Para cada posición adyacente al pixel actual se verifica si se encuentra dentro de la imagen.
			if(dentroDeLimites(i-1,j-1,filas,columnas)){
				pixel += matriz[i-1][j-1].grey*mascara[0][0];
			}
			if(dentroDeLimites(i-1,j,filas,columnas)){
				pixel += matriz[i-1][j].grey*mascara[0][1];
			}
			if(dentroDeLimites(i-1,j+1,filas,columnas)){
				pixel += matriz[i-1][j+1].grey*mascara[0][2];
			}
			if(dentroDeLimites(i,j-1,filas,columnas)){
				pixel += matriz[i][j-1].grey*mascara[1][0];
			}
			if(dentroDeLimites(i,j+1,filas,columnas)){
				pixel += matriz[i][j+1].grey*mascara[1][2];
			}
			if(dentroDeLimites(i+1,j-1,filas,columnas)){
				pixel += matriz[i+1][j-1].grey*mascara[2][0];
			}
			if(dentroDeLimites(i+1,j,filas,columnas)){
				pixel += matriz[i+1][j].grey*mascara[2][1];
			}
			if(dentroDeLimites(i+1,j+1,filas,columnas)){
				pixel += matriz[i+1][j+1].grey*mascara[2][2];
			}
			matriz[i][j].pixel = pixel;		
		}
	}
	return matriz;
}
/*
	Función que aplica el filtro laplaciano a la imagen

	Entradas: -Matriz de rgb representando la imagen
			  - Entero como el número  de filas de la imagen.
			  - Entero como el número de columnas de la imagen.
			  -Matriz de enteros representando la mascara espacial.

	Salida: La matriz de rgb que representa a la imagen.		  
*/
/*rgb ** filtroLaplaciano(rgb ** matriz, int filas, int columnas, int ** mascara){

	int i,j,x,y;
	float P;

	//Matriz para representar los valores adyacentes a un pixel (0 en caso de que el pixel se encuentre en un borde)
	float aux[3][3];

	for(i = 0; i < filas; i++){
		for(j = 0; j < columnas; j++){

			aux[1][1] = matriz[i][j].grey;
			P = 0;

			//esquina superior izquierda
			if(i == 0 && j == 0){
				aux[0][0] = 0;
				aux[0][1] = 0;
				aux[0][2] = 0;
				aux[1][0] = 0;
				aux[1][2] = matriz[i][j+1].grey;
				aux[2][0] = 0;
				aux[2][1] = matriz[i+1][j].grey;
				aux[2][2] = matriz[i+1][j+1].grey;
			}
			//esquina superior derecha.
			else if(i == 0 && j == columnas - 1){
				aux[0][0] = 0;
				aux[0][1] = 0;
				aux[0][2] = 0;
				aux[1][0] = matriz[i][j-1].grey;
				aux[1][2] = 0;
				aux[2][0] = matriz[i+1][j-1].grey;
				aux[2][1] = matriz[i+1][j].grey;
				aux[2][2] = 0;
			}
			//primera fila
			else if(i == 0){
				aux[0][0] = 0;
				aux[0][1] = 0;
				aux[0][2] = 0;
				aux[1][0] = matriz[i][j-1].grey;
				aux[1][2] = matriz[i][j+1].grey;
				aux[2][0] = matriz[i+1][j-1].grey;
				aux[2][1] = matriz[i+1][j].grey;
				aux[2][2] = matriz[i+1][j+1].grey;
			}
			//esquina inferior izquierda
			else if(i == filas-1 && j == 0){
				aux[0][0] = 0;
				aux[0][1] = matriz[i-1][j].grey;
				aux[0][2] = matriz[i-1][j+1].grey;
				aux[1][0] = 0;
				aux[1][2] = matriz[i][j+1].grey;
				aux[2][0] = 0;
				aux[2][1] = 0;
				aux[2][2] = 0;
			}
			//esquina inferior derecha
			else if(i == filas-1 && j == columnas-1){
				aux[0][0] = matriz[i-1][j-1].grey;
				aux[0][1] = matriz[i-1][j].grey;
				aux[0][2] = 0;
				aux[1][0] = matriz[i][j-1].grey;
				aux[1][2] = matriz[i][j+1].grey;
				aux[2][0] = 0;
				aux[2][1] = 0;
				aux[2][2] = 0;
			}
			//ultima fila
			else if(i == filas-1){
				aux[0][0] = matriz[i-1][j-1].grey;
				aux[0][1] = matriz[i-1][j].grey;
				aux[0][2] = matriz[i-1][j+1].grey;
				aux[1][0] = matriz[i][j-1].grey;
				aux[1][2] = matriz[i][j+1].grey;
				aux[2][0] = 0;
				aux[2][1] = 0;
				aux[2][2] = 0;
			}
			//primera columna
			else if(j == 0){
				aux[0][0] = 0;
				aux[0][1] = matriz[i-1][j].grey;
				aux[0][2] = matriz[i-1][j+1].grey;
				aux[1][0] = 0;
				aux[1][2] = matriz[i][j+1].grey;
				aux[2][0] = 0;
				aux[2][1] = matriz[i+1][j].grey;
				aux[2][2] = matriz[i+1][j+1].grey;
			}
			//ultima columna
			else if(j == columnas-1){
				aux[0][0] = matriz[i-1][j-1].grey;
				aux[0][1] = matriz[i-1][j].grey;
				aux[0][2] = 0;
				aux[1][0] = matriz[i][j-1].grey;
				aux[1][2] = 0;
				aux[2][0] = matriz[i+1][j-1].grey;
				aux[2][1] = matriz[i+1][j].grey;
				aux[2][2] = 0;
			}
			//pixel que no se encuentra en algun borde
			else{
				aux[0][0] = matriz[i-1][j-1].grey;
				aux[0][1] = matriz[i-1][j].grey;
				aux[0][2] = matriz[i-1][j+1].grey;
				aux[1][0] = matriz[i][j-1].grey;
				aux[1][2] = matriz[i][j+1].grey;
				aux[2][0] = matriz[i+1][j-1].grey;
				aux[2][1] = matriz[i+1][j].grey;
				aux[2][2] = matriz[i+1][j+1].grey;
			}

			//Finalmente se calcula el Laplaciano y se agrega a la matriz.
			for(x = 0; x < 3; x++){
				for(y = 0; y < 3; y++){

					P = P + aux[x][y]*mascara[x][y];
				}
			}
			matriz[i][j].pixel = P;

		}
	}	
	return matriz;
}*/

