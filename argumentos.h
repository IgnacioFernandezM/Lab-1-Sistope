//#include "estructura.h"
#ifndef ARGUMENTOS_H
#define ARGUMENTOS_H

void recibirArgumentos(int argc, char *argv[], int *num_img, float *umbral_bin, float *umbral_clasif,char * nombre_archivo, int *flag);

/*int obtenerRGBDeCadaPixel(char * nombre_archivo);
rgb ** crearMatriz(int filas, int columnas);
rgb ** matrizContenido(rgb ** matriz, int filas, int columnas);
void imprimir(rgb ** matriz, int filas, int columnas);
void liberarMatriz(rgb ** matriz, int filas);*/

#endif
