#include <stdio.h>        //Entradas y salidas estandar
#include <stdlib.h>       //Para manejo dinámico de datos
#include <string.h>       //Manejo de cadenas de caracteres

#define LONGITUD_ARCHIVO 4096     //Tamaño del buffer
/**
 *  La funcion recibe un archivo de entrada y el numero de lineas de texto retorna un apuntador a lieas de texto
*/
char **leerLinea(FILE *input, int *numLineas) {
    char **lineas = NULL;                        //Arreglo lineas de texto
    char memoria[LONGITUD_ARCHIVO];

    *numLineas = 0;

    while (fgets(memoria, sizeof(memoria), input) != NULL) {  //Si la operacion de recupera cadena de input es exito repite
        unsigned int longitud = (unsigned int)strlen(memoria);  //Se calcula el tamaño del buffer
        if (longitud > 0 && memoria[longitud - 1] == '\n') {  //Se elimina los saltos de linea
            memoria[longitud - 1] = '\0';
        }

        char *linea = strdup(memoria);                  //Retorna copia de la cadena

        lineas = realloc(lineas, (*numLineas + 1) * sizeof(char *));//Si bloque de memoria no es suficiente redimenciona buffer
        if (lineas == NULL) {
            fprintf(stderr, "error malloc failed\n");
            exit(1);
        }
        lineas[*numLineas] = linea;       //Se almacena linea de texto en una posicion del array lineas

        (*numLineas)++;                  //Incrementa en uno al contenido de lo apuntado por
    }

    return lineas;
}
//Se recibe como parametros unapuntador al archivo de salida, un apuntador a cadena de caracteres y la cantidad de lineas de texto
void escribaLineasReversa(FILE *salida, char **lineas, int cuentaLinea) {
    for (int i = cuentaLinea - 1; i >= 0; i--) { //Se recorre el array en sentido inverso
        fprintf(salida, "%s", lineas[i]);     // Se almacena linea de texto en el archivo de salida
    }
}
//Se libera la memoria dinamica para optimizar el uso de memoria
void liberaMemoria(char **lineas, int cuentaLinea) {
    for (int i = 0; i < cuentaLinea; i++) {
        free(lineas[i]);
    }
    free(lineas);
}