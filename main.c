#include <stdio.h>
#include <stdlib.h>
#include "argumentos.h"
#include "lectura.h"
#include "conversion.h"
#include "filtro.h"
#include "binarizacion.h"
#include "clasificacion.h"
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
	int retorno;
	rgb ** matriz = (rgb**)malloc(sizeof(rgb*)*0);
	char * archivo_imagen = "imagen_1.jpg";
	//Funcion que abre y lee un archivo jpg, descomprimiendo la imagen obteniendo los valores RGB de cada pixel
	retorno = obtenerRGBDeCadaPixel(archivo_imagen);
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
	//imprimir(matriz, alto_bmp, ancho_bmp);

//------------------------------------------------------------------------------------------------------------
// Conversion de RGB a gris	
	matriz = conversionRGBAGris(matriz,alto_bmp,ancho_bmp);
	//imprimirGris(matriz,alto_bmp,ancho_bmp);

	int ** mascara = (int**)malloc(sizeof(int*)*0);
	//Se obtiene la mascara laplaciana
	mascara = leerArchivoMascara(nombre_archivo_mascara,mascara);

	//se aplica el filtro laplaciano a la imagen.
	matriz = filtroLaplaciano(matriz,alto_bmp,ancho_bmp,mascara);
	//imprimirFiltro(matriz,alto_bmp,ancho_bmp);

	//se binariza la imagen.
	matriz = binarizar(matriz,alto_bmp,ancho_bmp,umbral_bin);
	//imprimirFiltro(matriz,alto_bmp,ancho_bmp);

	//Si se puso el argumento '-b', se muestra el resultado de la clasficación.
	if(flag == 1){
		clasificar(matriz,alto_bmp,ancho_bmp,umbral_clasif,archivo_imagen);
	}
	//Se libera memoria de la matriz contenido y de la variable contenido;
	liberarMatriz(matriz, alto_bmp);
	free(contenido);
//--------------------------------------------------------------------------------------------------------------------------------

	free(nombre_archivo_mascara);
	int i;
	for(i = 0; i < 3; i++){
		free(mascara[i]);
	}
	free(mascara);
	
	return 0;
}
