#include "estructura.h"

#ifndef FILTRO_H
#define FILTRO_H

int ** leerArchivoMascara(char * nombre_archivo, int ** mascara);
void imprimirFiltro(rgb ** matriz, int filas, int columnas);
rgb ** filtroLaplaciano(rgb ** matriz, int filas, int columnas, int ** mascara);

#endif