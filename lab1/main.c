#include <stdio.h>
#include <stdlib.h>
#include "argumentos.h"

int main(int argc, char * argv[]){

	int num_img;
	float umbral_bin,umbral_clasif;
	int flag = 0;
	char * nombre_archivo = (char*)malloc(sizeof(char));

	recibirArgumentos(argc,argv,&num_img,&umbral_bin,&umbral_clasif,nombre_archivo,&flag);

	
	printf("\nNumero imagenes: %i\nUmbral binarizacion: %f\nUmbral clasificacion: %f\nnombre archivo: %s\nflag: %i\n",num_img,umbral_bin,umbral_clasif,nombre_archivo,flag);
	free(nombre_archivo);
	return 0;
}