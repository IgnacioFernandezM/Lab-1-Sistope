#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estructura.h"

/*
	Entradas: -*nombre_archivo: Puntero a char representando el nombre del archivo que contiene la máscara de filtro Laplaciano

	Funcionamiento: Abre el archivo con la máscara de filtro para almacenarla.

	Salida: Una matriz de enteros representando la mascara.
*/
int ** leerArchivoMascara(char * nombre_archivo, int ** mascara){
	
	//Apertura de archivo.
	FILE * archivo = fopen(nombre_archivo,"r");

	if(archivo==NULL){
		perror("\nError al intentar leer el archivo de entrada.\n\n");
		exit(1);
	}

	int i;
	mascara = (int**)malloc(sizeof(int*)*3);
	for(i = 0; i < 3; i++){
		mascara[i] = (int*)malloc(sizeof(int)*3);
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
			printf("%i ",mascara[i][j]);
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
	Función que aplica el filtro laplaciano a la imagen

	Entradas: -Matriz de rgb representando la imagen
			  - Entero como el número  de filas de la imagen.
			  - Entero como el número de columnas de la imagen.
			  -Matriz de enteros representando la mascara espacial.

	Salida: La matriz de rgb que representa a la imagen.		  
*/
rgb ** filtroLaplaciano(rgb ** matriz, int filas, int columnas, int ** mascara){

	int i,j,x,y;
	float P;
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
			//pixel fuera de bordes
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
}

