#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <jpeglib.h>
#include "estructura.h"

/*Funcion que abre una archivo en formato jpg y lo descomprime obteniendo los valores RGB de cada pixel
Entrada: -Nombre del archivo jpg
Salida: Numero entero que permite saber si el archivo no existe (1), si el encabezado del archivo jpg no es normal (2) o si el archivo
	fue leido correctamente (0)*/
int obtenerRGBDeCadaPixel(char * nombre_archivo){
	int retorno, i;
	// Se verifica si el archivo existe, de no existir se finaliza el programa
	retorno = stat(nombre_archivo, &info_archivo);
	if (retorno == -1){
		return 1;
	}
	tamano_jpg = info_archivo.st_size;
	contenido_jpg = (unsigned char*) malloc(tamano_jpg + 100);
	//Se abre el archivo en modo read
	int fd = open(nombre_archivo, O_RDONLY);
	//Se lee la imagen y almacena el contenido en la variable contenido_jpg
	for (i = 0; i < tamano_jpg; i++) {
		retorno = read(fd, contenido_jpg + i, tamano_jpg - i);
		i += retorno;
	}
	//Se cierra el archivo
	close(fd);
	//Se comienza a descomprimir la imagen
	cinfoLectura.err = jpeg_std_error(&jerr);	
	jpeg_create_decompress(&cinfoLectura);
	//Se manipulan los datos de la imagen almacenados en contenido_jpg
	jpeg_mem_src(&cinfoLectura, contenido_jpg, tamano_jpg);
	//Se verifica que el encabezado del contenido de la imagen es valido, de no ser valido se finaliza el programa
	retorno = jpeg_read_header(&cinfoLectura, TRUE);
	if (retorno != 1) {
		return 2;
	}
	// Se reasignan las variables de ancho alto tamaño del pixel y maximo de filas
	jpeg_start_decompress(&cinfoLectura);
	ancho_bmp = cinfoLectura.output_width;
	alto_bmp = cinfoLectura.output_height;
	tamano_pixel = cinfoLectura.output_components;
	tamano_bmp = ancho_bmp * alto_bmp * tamano_pixel;
	contenido = (unsigned char*) malloc(tamano_bmp);
	max_filas = ancho_bmp * tamano_pixel;
	//Se leen todas las lineas escaneadas de la imagen, estas aparecen de forma R G B R G B...
	//Por lo que cada posicion del arreglo contenido contiene un valor de cada pixel
	while (cinfoLectura.output_scanline < cinfoLectura.output_height) {
		unsigned char *buffer_array[1];
		buffer_array[0] = contenido + (cinfoLectura.output_scanline) * max_filas;
		jpeg_read_scanlines(&cinfoLectura, buffer_array, 1);
	}
	//Se termina de descomprimir la imagen
	jpeg_finish_decompress(&cinfoLectura);
	jpeg_destroy_decompress(&cinfoLectura);
	//Se libera memoria de la variable utilizada
	free(contenido_jpg);
	
	return 0;
}

/*Funcion que crea una matriz con las dimensiones de la imagen jpg (ancho x alto)
Entrada:- Cantidad de filas de la matriz (anchura)
	- Cantidad de columnas de la matriz (altura)
Salida: -Matriz que contiene los valores RGB de la imagen*/
rgb ** crearMatriz(int filas, int columnas){
	int i;
	//Se asigna memoria a la matriz
	rgb ** matrizNueva = (rgb**)malloc(sizeof(rgb*)*filas);
	for (i = 0; i < filas; i++){
		matrizNueva[i] = (rgb*)malloc(sizeof(rgb)*columnas);
	}
	return matrizNueva;
}

/*Funcion que almacena los valores RGB de cada pixel en una matriz
Entrada:- Matriz vacia 
	- Cantidad de filas de la matriz
	- Cantidad de columnas de la matriz
Salida: - Matriz con los valores RGB de la imagen*/
rgb ** matrizContenido(rgb ** matriz, int filas, int columnas){
	int i, j, k = 0;
	for(i = 0; i < filas; i++){
		for(j = 0; j < columnas; j++){
			matriz[i][j].red = contenido[k];
			matriz[i][j].green = contenido[k+1];
			matriz[i][j].blue = contenido[k+2];
			matriz[i][j].grey = 0;
			matriz[i][j].pixel = 0;
			k = k + 3;
		}
	}
	return matriz;
}

/*Funcion que muestra el valor RGB de cada pixel
Entrada:- Matriz con el contenido de la imagen
	- Cantidad de filas de la matriz
	- Cantidad de columnas de la matriz*/
void imprimir(rgb ** matriz, int filas, int columnas){
	int i, j;
	for(i = 0; i < filas; i++){
		for(j = 0; j < columnas; j++){
			printf("%d/%d/%d ", matriz[i][j].red, matriz[i][j].green, matriz[i][j].blue);
		}
		//printf("\n");
	}
}

/*Funcion que libera memoria de una matriz
Entrada:-Matriz a liberar memoria
	-Cantidad de filas de la matriz*/
void liberarMatriz(rgb ** matriz, int filas){
	int i;
	for (i = 0; i < filas; i++){
		free(matriz[i]);
	}
	free(matriz);
}

/*Funcion que libera memoria de la matriz que contiene los valores RGB y el procesamiento de esta para ingresar otra imagen
Entrada: -Matriz a liberar memoria
	-Cantidad de filas de la matriz
Salida: Matriz actualizada
*/
rgb ** actualizarMatriz(rgb ** matriz, int alto_bmp){
	liberarMatriz(matriz, alto_bmp);
	rgb ** matrizNueva = (rgb**)malloc(sizeof(rgb*)*0);
	return matrizNueva;
}