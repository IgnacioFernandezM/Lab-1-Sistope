#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "argumentos.h"

/*	
	Entradas: -argc: Entero que indica el número de argumentos ingresados en la linea de comandos
			  -argv: Arreglo con las entradas ingresadas por linea de comandos
			  -*num_img: Puntero a variable entera que representa el número de imagenes a leer.
			  -*umbral_bin: Puntero a variable entera que representa el umbral de binarización.
			  -*umbral_clasif: Puntero a variable entera que representa el umbral de clasificación.
			  -*nombre_archivo: Puntero a char que representa el nombre del archivo de texto que contiene la máscara
			  -*flag: Puntero a variable entera que representa una bandera indicando si se muestran resultados por pantalla o no.
	
	Funcionamiento: Esta función lee los argumentos ingresados por la línea de comandos.

	Salida: Vacío.			  

*/
void recibirArgumentos(int argc, char *argv[], int *num_img, float *umbral_bin, float *umbral_clasif, char * nombre_archivo, int *flag){

	//Si se ingresaron menos de 9 argumentos, se termina el programa.
	if(argc < 9){

		printf("Se ingreso un numero incorrecto de argumentos\n");
		fprintf(stderr, "Uso correcto: %s [-c numero entero positivo] [-u numero entero] [-n numero entero] [-m nombre_archivo] [-b]\n",argv[0]);
		exit(EXIT_FAILURE);
	}

	int opt;
	float aux;
	//Mientras aún queden argumentos por leer.
	while((opt = getopt(argc, argv, "c:u:n:m:b")) != -1){
		switch(opt){

			case 'c':

				sscanf(optarg,"%f",&aux);
				*num_img = aux;

				/*if(aux - *num_img != 0){
					printf("\nnumero decimal\n");
					exit(EXIT_FAILURE);
				}*/
				//sscanf(optarg,"%d",num_img);

				if(*num_img <= 0 || aux - *num_img != 0){
					printf("\nArgumento -c incorrecto\n");
					//fprintf(stderr,"\nUso correcto: %s [-c numero entero positivo] [-u numero entero] [-n numero entero] [-m nombre_archivo] [-b]\n",argv[0]);
					mostrarUsoCorrecto(argv);
					exit(EXIT_FAILURE);
				}
				break;

			case 'u':

				sscanf(optarg,"%f",umbral_bin);

				if(*umbral_bin < 0){
					printf("\nArgumento -u incorrecto\n");
					mostrarUsoCorrecto(argv);
					exit(EXIT_FAILURE);
				}
				break;	

			case 'n':

				sscanf(optarg,"%f",umbral_clasif);

				if(*umbral_clasif < 0){
					printf("\nArgumento -n incorrecto.\n");
					mostrarUsoCorrecto(argv);
					exit(EXIT_FAILURE);
				}
				break;

			case 'm':
				sscanf(optarg,"%s",nombre_archivo);
				break;

			case 'b':
				*flag = 1;
				break;

			case '?': //Opción inválida.

				mostrarUsoCorrecto(argv);
				//fprintf(stderr,"\nUso correcto: %s [-c numero entero positivo] [-u numero entero] [-n numero entero] [-m nombre_archivo] [-b]\n",argv[0]);
				exit(EXIT_FAILURE);

      		default:
        		abort();
		}		

	}
}

void mostrarUsoCorrecto(char * argv[]){

	fprintf(stderr,"\nUso correcto: %s [-c numero entero positivo] [-u numero entero] [-n numero entero] [-m nombre_archivo] [-b]\n",argv[0]);
}
