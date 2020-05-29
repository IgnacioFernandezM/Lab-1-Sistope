#include <fcntl.h>
#include <jpeglib.h>
#ifndef estructura_h_
#define estructura_h_

//Estructura utilizada para descomprimir el archivo jpg
struct stat info_archivo;
	unsigned long tamano_jpg;
	unsigned char * contenido_jpg;
	unsigned long tamano_bmp;
	unsigned char * contenido;
	int max_filas, ancho_bmp, alto_bmp, tamano_pixel;

struct jpeg_decompress_struct cinfo;
struct jpeg_error_mgr jerr;


//Estructura para almacenar los valores RGB en una matriz
typedef struct rgb rgb;

struct rgb{
	int red;
	int green;
	int blue;
    
 };
 
 #endif
