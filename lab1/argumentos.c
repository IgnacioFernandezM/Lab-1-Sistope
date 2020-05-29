#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <jpeglib.h>
#include "estructura.h"

/*	
	Entradas: -argc: Entero que indica el número de argumentos ingresados en la linea de comandos
			  -argv: Arreglo con las entradas ingresadas por linea de comandos
			  -*num_img: Puntero a variable entera que representa el número de imagenes a leer.
			  -*umbral_bin: Puntero a variable entera que representa el umbral de binarización.
			  -*umbral_clasif: Puntero a variable entera que representa el umbral de clasificación.
			  -*nombre_archivo: Puntero a char que representa el nombre del archivo de texto que contiene la máscara
			  -*flag: Puntero a variable entera que representa una bandera indicando si se muestran resultados por pantalla o no.
	
	Funcionamiento: Esta función lee los argumentos ingresados por la línea de comandos.

	Salida: Vacío.			  

*/
void recibirArgumentos(int argc, char *argv[], int *num_img, float *umbral_bin, float *umbral_clasif, char * nombre_archivo, int *flag){

	//Si se ingresaron menos de 9 argumentos, se termina el programa.
	if(argc < 9){

		printf("Se ingreso un numero incorrecto de argumentos\n");
		fprintf(stderr, "Uso correcto: %s [-c numero entero] [-u numero entero] [-n numero entero] [-m nombre_archivo] [-b]\n",argv[0]);
		exit(EXIT_FAILURE);
	}

	int opt;
	//Mientras aún queden argumentos por leer.
	while((opt = getopt(argc, argv, "c:u:n:m:b")) != -1){
		switch(opt){

			case 'c':
				sscanf(optarg,"%d",num_img);
				break;

			case 'u':
				sscanf(optarg,"%f",umbral_bin);
				break;	

			case 'n':
				sscanf(optarg,"%f",umbral_clasif);
				break;

			case 'm':
				sscanf(optarg,"%s",nombre_archivo);
				break;

			case 'b':
				*flag = 1;
				break;

			case '?': //Opción inválida.

				fprintf(stderr,"\nUso correcto: %s [-c numero entero] [-u numero entero] [-n numero entero] [-m nombre_archivo] [-b]\n",argv[0]);
				exit(EXIT_FAILURE);

      		default:
        		abort();
		}		

	}
}

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
	cinfo.err = jpeg_std_error(&jerr);	
	jpeg_create_decompress(&cinfo);
	//Se manipulan los datos de la imagen almacenados en contenido_jpg
	jpeg_mem_src(&cinfo, contenido_jpg, tamano_jpg);
	//Se verifica que el encabezado del contenido de la imagen es valido, de no ser valido se finaliza el programa
	retorno = jpeg_read_header(&cinfo, TRUE);
	if (retorno != 1) {
		return 2;
	}
	// Se reasignan las variables de ancho alto tamaño del pixel y maximo de filas
	jpeg_start_decompress(&cinfo);
	ancho_bmp = cinfo.output_width;
	alto_bmp = cinfo.output_height;
	tamano_pixel = cinfo.output_components;
	tamano_bmp = ancho_bmp * alto_bmp * tamano_pixel;
	contenido = (unsigned char*) malloc(tamano_bmp);
	max_filas = ancho_bmp * tamano_pixel;
	//Se leen todas las lineas escaneadas de la imagen, estas aparecen de forma R G B R G B...
	//Por lo que cada posicion del arreglo contenido contiene un valor de cada pixel
	while (cinfo.output_scanline < cinfo.output_height) {
		unsigned char *buffer_array[1];
		buffer_array[0] = contenido + (cinfo.output_scanline) * max_filas;
		jpeg_read_scanlines(&cinfo, buffer_array, 1);
	}
	//Se termina de descomprimir la imagen
	jpeg_finish_decompress(&cinfo);
	jpeg_destroy_decompress(&cinfo);
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
Entrada:- Matriz vacia con las dimensiones de la imagen jpg
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
			k = k+3;
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
