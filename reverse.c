
/**
 *  Taller procesamiento de archivos Semestre 1 2024
 *  Yuly Yesenia Albear
 *  Leidy Castaño
 *  Omar Alberto Torres
 * 
*/
//Bloque de librerías usadas
#include <stdio.h>     
#include <stdlib.h>
#include <string.h>
#define LONGITUD_ANCHO_ARCHIVO 1000     //Ancho del buffer

/**
 * Firmas de las funciones del programa
*/
void flujoPrograma(int argc, char *argv[]);
char **leerLinea(FILE *input, int *numLineas) ;
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
void textInputUser() ;
void opcionUno();
void opcionDos();
void opcionTres();
