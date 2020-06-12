#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estructura.h"

/*
	Entradas: Vacío.

	Funcionamiento: Crea una matriz de flotantes con memoría dinámica con valores 0.

	Salida: Una matriz de flotantes representando la mascara.
*/
float ** crearMatrizMascara(){

	int i,j;
	float ** mascara = (float**)malloc(sizeof(float*)*3);
	for(i = 0; i < 3; i++){
		mascara[i] = (float*)malloc(sizeof(float)*3);
	}
	//Se rellena con 0
	for(i = 0; i < 3; i++){
		for(j = 0; j < 3; j++){
			mascara[i][j] = 0;
		}
	}
	return mascara;
}

/*
	Entradas: -*nombre_archivo: Puntero a char representando el nombre del archivo que contiene la máscara de filtro Laplaciano
	          - mascara: Matriz de flotantes que representa la máscara del filtro Laplaciano

	Funcionamiento: Abre el archivo con la máscara de filtro para almacenar sus valores en la matriz mascara.

	Salida: Una matriz de enteros representando la mascara.
*/
float ** leerArchivoMascara(char * nombre_archivo, float ** mascara){
	
	//Apertura de archivo.
	FILE * archivo = fopen(nombre_archivo,"r");

	//Si no se pudo abrir el archivo se termina el programa.
	if(archivo==NULL){
		perror("\nError al intentar leer el archivo de entrada.\n\n");
		exit(1);
	}

	int i;
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

	//Se cierra archivo.
	fclose(archivo);

	return mascara;
}

/*
	Entradas: -mascara: Matriz de flotantes que representa la mascara laplaciana

	Funcionamiento: Libera la memoría de la matriz

	Salida: Vacío.
*/
void liberarMemoriaMascara(float ** mascara){

	for(int i = 0; i < 3; i++){
		free(mascara[i]);
	}
	free(mascara);
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

