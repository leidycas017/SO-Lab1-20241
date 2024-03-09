
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

void flujoPrograma(int argc, char *argv[]) {
    switch (argc) {
        case 1:
            opcionUno();
            break;
        case 2:
            opcionDos(argc, argv);

            break;
        case 3:
            opcionTres(argc, argv);
            break;
        default:
            fprintf(stderr, "usage: reverse <input> <output>\n");
            exit(1);
    }
}

/**
 *  La funcion recibe un archivo de entrada y el numero de lineas de texto
 * El puntero FiLE *input represente el apuntador a una estructura FILE
 *  retorna un apuntador a lieas de texto
*/
char **leerLinea(FILE *input, int *numLineas) {
    char **lineas = NULL;                        //Arreglo lineas de texto
    char memoria[LONGITUD_ANCHO_ARCHIVO];

    *numLineas = 0;

    while (fgets(memoria, sizeof(memoria), input) != NULL) {  //Si la operacion de recupera cadena de input es exito repite
        //longitud nunca será negativo
        unsigned int longitud = (unsigned int)strlen(memoria);  //Se calcula el tamaño del buffer
        if (longitud > 0 && memoria[longitud - 1] == '\n') {  //Truco para eliminar los saltos de linea
            memoria[longitud - 1] = '\0';                 //Se coloca un null
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

/**
* Se recibe como parametros un apuntador al archivo de salida, un apuntador a cadena de caracteres y la cantidad de lineas de texto
* Anexar el caracter salto de linea '\n' evita que las lineas se traslapen
**/
void escribaLineasReversa(FILE *salida, char **lineas, int cuentaLinea) {
    for (int i = cuentaLinea - 1; i >= 0; i--) { //Se recorre el array en sentido inverso
        fprintf(salida, "%s\n", lineas[i]);     // Se almacena linea de texto en el archivo de salida
    }
}

//Se libera la memoria dinamica para optimizar el uso de memoria
void liberaMemoria(char **lineas, int cuentaLinea) {
    for (int i = 0; i < cuentaLinea; i++) {
        free(lineas[i]);
    }
    free(lineas);
}
/**
 *  La función verifica si dos archivos tienen el mismo nombre
*/
int archivosDiferentes(char *archivoInput, char *archivoOutput) {
    return strcmp(archivoInput, archivoOutput);
}
/**
 *  
 * 
 * 
 * 
 * 
 * la funcion procesa el archivo de entrada y de salida, hace validaciones
*/
void procesoArchivos(char *entradaNombreArchivo, char *salidaNombreArchivo) {
    const char *modo;
    int ret = archivosDiferentes(entradaNombreArchivo, salidaNombreArchivo); //Codigo en prueba
    if(ret==0){
        modo = "r";
    }
    else modo = "w";
    FILE *entrada = fopen(entradaNombreArchivo, "r");                      //Error de apertura archivo de entrada
    
    if (entrada == NULL) {
        fprintf(stderr, "error: cannot open file %s\n", entradaNombreArchivo);
        exit(1);
    }

    FILE *salida = fopen(salidaNombreArchivo, modo);
    if (salida == NULL) {
        fprintf(stderr, "error: cannot open file%s\n", salidaNombreArchivo);  //Error de apertura archivo de salida
        fclose(salida);
        exit(1);
    }

    if (strcmp(entradaNombreArchivo, salidaNombreArchivo) == 0) {
        fprintf(stderr, "El archivo de entrada y salida deben diferir\n");  //Error archivos tienen el mismo nombre
        fclose(entrada);
        fclose(salida);
        exit(1);
    }

    int cuentaLinea;                                //Variable  pensada para tener el numero de lineas de texto
    char **lineas = leerLinea(entrada, &cuentaLinea);  //  Retorna array con lineas de texto y cantidad delineas de texto

    escribaLineasReversa(salida, lineas, cuentaLinea);  //Se invoca funcion que almacena lineas de texto en forma invertida en salida fisica

    liberaMemoria(lineas, cuentaLinea);                  //libera memoria  

    fclose(entrada);                                //Se cierra archivo de entrada
    fclose(salida);                               //Se cierra archivo de salida
}

/**
 * La función asigna memoria dinámica 
*/
char *asignarMemoriaLinea(unsigned int longitud) {
    char *linea = (char *)malloc((longitud + 1) * sizeof(char));     //El array linea se construye dinamicamente 
    if (linea == NULL) {
        fprintf(stderr,"error malloc failed\n");
        exit(1);
    }
    return linea;                                                            //Retorno del array a lineas de texto
}

/**
 * Funcion que recibe como parametro un archivo y el numero de lineas del archivo
*/