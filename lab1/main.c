#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "argumentos.h"
#include "lectura.h"
#include "conversion.h"
#include "filtro.h"
#include "binarizacion.h"
#include "clasificacion.h"
#include "escritura.h"
#include "estructura.h"

int main(int argc, char * argv[]){

	int num_img;
	float umbral_bin,umbral_clasif;
	int flag = 0;
	char * nombre_archivo_mascara = (char*)malloc(sizeof(char));

	//Se obtienen los argumentos ingresados al ejecutar el programa.
	recibirArgumentos(argc,argv,&num_img,&umbral_bin,&umbral_clasif,nombre_archivo_mascara,&flag);
	printf("\nNumero de imagenes: %i\n",num_img);
	printf("Umbral binarizacion: %f\n",umbral_bin);
	printf("Umbral clasificacion %f\n",umbral_clasif);
	printf("Nombre archivo mascara: %s\n",nombre_archivo_mascara);
	printf("flag: %i\n",flag);
	
//--------------------------------------------------------------------------------------------------------------------------------
	//Variable para indicar si se pudo leer el archivo, la matriz que contiene los pixeles de la imagen y el nombre de archivo
	int retorno, i;
	//Variables para cambiar el nombre del archivo a leer
	char numero_imagen[100];
	char nombre_imagen[100];
	char nombre_imagen_procesada[100];
	//Matriz que contendra el contenido de la imagen
	rgb ** matriz = (rgb**)malloc(sizeof(rgb*)*0);
	//Matriz de la mascara que se aplica a la imagen
	float ** mascara = (float**)malloc(sizeof(float*)*0);
	//Se obtiene la mascara laplaciana
	mascara = leerArchivoMascara(nombre_archivo_mascara,mascara);
	//Se crea el loop para leer la cantidad de imagenes solicitadas por comando
	for(i = 1; i <= num_img; i++){
		strcpy(nombre_imagen, "imagen_");
		//Se convierte el numero de la imagen actual a caracter
		sprintf(numero_imagen, "%d", i);
		//Se modifica el nombre del archivo de entrada
		strcat(nombre_imagen, numero_imagen);
		strcat(nombre_imagen, ".jpg");

		//Funcion que abre y lee un archivo jpg, descomprimiendo la imagen obteniendo los valores RGB de cada pixel
		retorno = obtenerRGBDeCadaPixel(nombre_imagen);
		if(retorno == 1){
			printf("El archivo %s no existe\n", nombre_imagen);
			return 1;
		}
		else if (retorno == 2){
			printf("El encabezado de la imagen no es normal, no se puede leer el archivo\n");
			return 2;
		}
		//Se crea la matriz con los valores RGB
		matriz = crearMatriz(alto_bmp, ancho_bmp);
		matriz = matrizContenido(matriz, alto_bmp, ancho_bmp);
		//imprimir(matriz, alto_bmp, ancho_bmp);

		//------------------------------------------------------------------------------------------------------------
		// Conversion de RGB a gris	
		matriz = conversionRGBAGris(matriz,alto_bmp,ancho_bmp);
		//imprimirGris(matriz,alto_bmp,ancho_bmp);

		//se aplica el filtro laplaciano a la imagen.
		matriz = filtroLaplaciano(matriz,alto_bmp,ancho_bmp,mascara);
		//imprimirFiltro(matriz,alto_bmp,ancho_bmp);

		//se binariza la imagen.
		matriz = binarizar(matriz,alto_bmp,ancho_bmp,umbral_bin);
		//imprimirFiltro(matriz,alto_bmp,ancho_bmp);

		//Si se puso el argumento '-b', se muestra el resultado de la clasficación.
		if(flag == 1){
			clasificar(matriz,alto_bmp,ancho_bmp,umbral_clasif,nombre_imagen);
		}
		//Se crea el nombre del arhivo de salida
		strcpy(nombre_imagen_procesada, "salida_");
		//Se convierte el numero de la imagen actual a caracter
		sprintf(numero_imagen, "%d", i);
		//Se modifica el nombre del archivo de salida
		strcat(nombre_imagen_procesada, numero_imagen);
		strcat(nombre_imagen_procesada, ".jpg");
		//Se escribe un archivo en formato jpg con el procesamiento de la imagen
		retorno = escribirImagenProcesada(matriz, nombre_imagen_procesada);
		if (retorno == 1){
			fprintf(stderr, "El archivo %s no se puede abrir o crear.\n", nombre_imagen_procesada);
			return 0;
		}
		//Se libera espacio de la matriz para almacenar otra imagen
		matriz = actualizarMatriz(matriz, alto_bmp);
	}
	//Se libera memoria de la matriz contenido y de la variable contenido;
	liberarMatriz(matriz, 0);
	free(contenido);
	free(contenidoBinarizado);
//--------------------------------------------------------------------------------------------------------------------------------

	free(nombre_archivo_mascara);
	for(i = 0; i < 3; i++){
		free(mascara[i]);
	}
	free(mascara);
	
	return 0;
}
