#include "estructura.h"

#ifndef LECTURA_H
#define LECTURA_H

int obtenerRGBDeCadaPixel(char * nombre_archivo);
rgb ** crearMatriz(int filas, int columnas);
rgb ** matrizContenido(rgb ** matriz, int filas, int columnas);
void imprimir(rgb ** matriz, int filas, int columnas);
void liberarMatriz(rgb ** matriz, int filas);

#endif