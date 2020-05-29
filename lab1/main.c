#include <stdio.h>
#include <stdlib.h>
#include "argumentos.h"
#include "estructura.h"

int main(int argc, char * argv[]){

	int num_img;
	float umbral_bin,umbral_clasif;
	int flag = 0;
	char * nombre_archivo = (char*)malloc(sizeof(char));

	recibirArgumentos(argc,argv,&num_img,&umbral_bin,&umbral_clasif,nombre_archivo,&flag);
	
//--------------------------------------------------------------------------------------------------------------------------------
	//Variable para indicar si se pudo leer el archivo, la matriz que contiene los pixeles de la imagen y el nombre de archivo
	int retorno;
	rgb ** matriz = (rgb**)malloc(sizeof(rgb*)*0);
	char * archivo = "imagen_1.jpg";
	//Funcion que abre y lee un archivo jpg, descomprimiendo la imagen obteniendo los valores RGB de cada pixel
	retorno = obtenerRGBDeCadaPixel(archivo);
	if(retorno == 1){
		printf("El archivo .jpg no existe\n");
		return 1;
	}
	else if (retorno == 2){
		printf("El encabezado de la imagen no es normal, no se puede leer el archivo\n");
		return 2;
	}
	//Se crea la matriz con los valores RGB
	matriz = crearMatriz(alto_bmp, ancho_bmp);
	matriz = matrizContenido(matriz, alto_bmp, ancho_bmp);
	imprimir(matriz, alto_bmp, ancho_bmp);
	//Se libera memoria de la matriz contenido y de la variable contenido;
	liberarMatriz(matriz, alto_bmp);
	free(contenido);
//--------------------------------------------------------------------------------------------------------------------------------

	
	printf("\nNumero imagenes: %i\nUmbral binarizacion: %f\nUmbral clasificacion: %f\nnombre archivo: %s\nflag: %i\n",num_img,umbral_bin,umbral_clasif,nombre_archivo,flag);
	free(nombre_archivo);
	
	return 0;
}
