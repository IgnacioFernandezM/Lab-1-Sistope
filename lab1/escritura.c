#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <jpeglib.h>
#include "estructura.h"

/*Funcion que escribe en un archivo en formato jpg el contenido de una imagen procesada
Entrada: -Matriz con el contenido de la imagen
	- Nombre del archivo a crear
Salida: Numero entero que permite saber si el archivo no se pudo crear o abir (1) o si el archivo fue 
	creado correctamente (0)*/
int escribirImagenProcesada(rgb ** matriz, char * nombre_archivo){

	//Se almacena la matriz con el contenido de la imagen procesada en un arreglo
	contenidoBinarizado = (unsigned char*) malloc(tamano_bmp);
	int i, j, k = 0; 
	for(i = 0; i < alto_bmp; i++){
		for(j = 0; j < ancho_bmp; j++){
			contenidoBinarizado[k] = matriz[i][j].pixel;
			k++;
		}
	}
    //Variables utilizadas para escribrir la imagen procesada
	FILE * archivo;
	JSAMPROW buffer_array[1];
	int max_filas;
	//Se comienza a comprimir la imagen
	cinfoEscritura.err = jpeg_std_error(&jerr);
	jpeg_create_compress(&cinfoEscritura);
	//Se verifica que el archivo pueda ser creado o modificado, sino se finaliza el programa
	if ((archivo = fopen(nombre_archivo, "wb")) == NULL) {
		return(1);
	}
	jpeg_stdio_dest(&cinfoEscritura, archivo);
	//Variables utilizadas para la compresion de la imagen
	cinfoEscritura.image_width = ancho_bmp;
	cinfoEscritura.image_height = alto_bmp;
	//Cantida de pixeles, en este caso es 1 dado que la imagen es binaria
	cinfoEscritura.input_components = 1;
	cinfoEscritura.in_color_space = JCS_GRAYSCALE;
	//Se establecen los valores predeterminados para comprimir
	jpeg_set_defaults(&cinfoEscritura);

	//Se inicia a comprimir la imagen
	jpeg_start_compress(&cinfoEscritura, TRUE);
	//Se escriben todos los pixeles de la imagen almacenada en contenidoBinarizado
	max_filas = ancho_bmp;
	while (cinfoEscritura.next_scanline < cinfoEscritura.image_height) {
		buffer_array[0] = & contenidoBinarizado[cinfoEscritura.next_scanline * max_filas];
		(void) jpeg_write_scanlines(&cinfoEscritura, buffer_array, 1);
	}
	//Se finaliza la compresion de la imagen
	jpeg_finish_compress(&cinfoEscritura);
	//Se cierra el archivo que contiene la imagen binarizada
	fclose(archivo);
	//Se libera memoria del objeto creado para comprimir
	jpeg_destroy_compress(&cinfoEscritura);
    return 0;
}
