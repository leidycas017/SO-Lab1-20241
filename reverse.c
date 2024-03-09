
/**
 *  Taller procesamiento de archivos Semestre 1 2024
 *  Yuly Yesenia Albear
 *  Leidy Castaño
 *  Omar Alberto Torres
 *
 */
// Bloque de librerías usadas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LONGITUD_ANCHO_ARCHIVO 1000 // Ancho del buffer

/**
 * Firmas de las funciones del programa
 */
void flujoPrograma(int argc, char *argv[]);
char **leerLinea(FILE *input, int *numLineas);
void escribaLineasReversa(FILE *salida, char **lineas, int cuentaLinea);
void liberaMemoria(char **lineas, int cuentaLinea);
int archivosDiferentes(char *archivoInput, char *archivoOutput);
void procesoArchivos(char *entradaNombreArchivo, char *salidaNombreArchivo);
char *asignarMemoriaLinea(unsigned int longitud);
char **leerArchivo(FILE *archivo, int *numLineas);
char **leerArchivo(FILE *archivo, int *numLineas);
char **leerLineas(int numLineas);
void invertirLineas(char **lineas, int numLineas);
char **leerLineas(int numLineas);
void invertirLineas(char **lineas, int numLineas);
void imprimirLineasInvertidas(char **lineas, int numLineas);
void imprimirLineas(char **lineas, int numLineas);
void liberarMemoria(char **lineas, int numLineas);
void textInputUser();
void opcionUno();
void opcionDos();
void opcionTres();

/**
 * Función principal
 */
int main(int argc, char *argv[])
{
    flujoPrograma(argc, argv);
    return 0;
}

/**
 *     La funcion corresponde a la opcion "./reverse"
*/

void opcionUno() {
    textInputUser();
}

/**
 * La funcion corresponde a la opcion "./reverse input.txt output.txt"
*/
void opcionDos(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <archivo>\n", argv[0]);
        exit(1);
    }

    FILE *archivo = fopen(argv[1], "r");
    if (archivo == NULL) {
        fprintf(stderr, "error: cannot open file '%s'\n", argv[1]);
        exit(1);
    }

    int numLineas;
    char **lineas = leerArchivo(archivo, &numLineas);
    fclose(archivo);
    invertirLineas(lineas, numLineas);      //Invierte lineas de texto
    imprimirLineas(lineas, numLineas);      //Imprime salida estandar
    liberarMemoria(lineas, numLineas);      //libera memoria 
}

/**
 * La funcion corresponde a la opcion "./reverse namefile.txt nemefile.txt"
*/
void opcionTres(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "usage: %s reverse <input> <output>", argv[0]);
        exit(1);
    }

    procesoArchivos(argv[1], argv[2]);
}

