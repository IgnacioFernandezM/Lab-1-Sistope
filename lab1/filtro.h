#include "estructura.h"

#ifndef FILTRO_H
#define FILTRO_H

float ** leerArchivoMascara(char * nombre_archivo, float ** mascara);
void imprimirFiltro(rgb ** matriz, int filas, int columnas);
int dentroDeLimites(int fila_actual, int columna_actual, int filas, int columnas);
rgb ** filtroLaplaciano(rgb ** matriz, int filas, int columnas, float ** mascara);

#endif