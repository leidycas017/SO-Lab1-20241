
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
void escribaLineasReversa(FILE *salida, char **lineas, int cuentaLinea);
void liberaMemoria(char **lineas, int cuentaLinea);
int archivosDiferentes(char *archivoInput, char *archivoOutput);
void procesoArchivos(char *entradaNombreArchivo, char *salidaNombreArchivo);
char *asignarMemoriaLinea(unsigned int longitud);
char **leerArchivo(FILE *archivo, int *numLineas);
void invertirLineas(char **lineas, int numLineas);
char **leerLineas(int numLineas);
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

void opcionUno()
{
    textInputUser();
}

/**
 * La funcion corresponde a la opcion "./reverse input.txt output.txt"
 */
void opcionDos(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "usage: reverse <input> <output>\n");
        exit(1);
    }

    FILE *archivo = fopen(argv[1], "r");
    if (archivo == NULL)
    {
        fprintf(stderr, "reverse: cannot open file '%s'\n", argv[1]);
        exit(1);
    }

    int numLineas;
    char **lineas = leerArchivo(archivo, &numLineas);
    fclose(archivo);
    invertirLineas(lineas, numLineas); // Invierte lineas de texto
    imprimirLineas(lineas, numLineas); // Imprime salida estandar
    liberarMemoria(lineas, numLineas); // libera memoria
}

/**
 * La funcion corresponde a la opcion "./reverse namefile.txt nemefile.txt"
 */
void opcionTres(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "usage: reverse <input> <output>\n");
        exit(1);
    }

    procesoArchivos(argv[1], argv[2]);
}

void flujoPrograma(int argc, char *argv[])
{
    switch (argc)
    {
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

/**
 * Se recibe como parametros un apuntador al archivo de salida, un apuntador a cadena de caracteres y la cantidad de lineas de texto
 * Anexar el caracter salto de linea '\n' evita que las lineas se traslapen
 **/
void escribaLineasReversa(FILE *salida, char **lineas, int cuentaLinea)
{
    for (int i = cuentaLinea - 1; i >= 0; i--)
    {                                       // Se recorre el array en sentido inverso
        fprintf(salida, "%s\n", lineas[i]); // Se almacena linea de texto en el archivo de salida
    }
}

// Se libera la memoria dinamica para optimizar el uso de memoria
void liberaMemoria(char **lineas, int cuentaLinea)
{
    for (int i = 0; i < cuentaLinea; i++)
    {
        free(lineas[i]);
    }
    free(lineas);
}
/**
 *  La función verifica si dos archivos tienen el mismo nombre
 */
int archivosDiferentes(char *archivoInput, char *archivoOutput)
{
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
void procesoArchivos(char *entradaNombreArchivo, char *salidaNombreArchivo)
{
    const char *modo;
    int ret = archivosDiferentes(entradaNombreArchivo, salidaNombreArchivo); // Codigo en prueba
    if (ret == 0)
    {
        modo = "r";
    }
    else
        modo = "w";
    FILE *entrada = fopen(entradaNombreArchivo, "r"); // Error de apertura archivo de entrada

    if (entrada == NULL)
    {
        fprintf(stderr, "reverse: cannot open file %s\n", entradaNombreArchivo);
        exit(1);
    }

    FILE *salida = fopen(salidaNombreArchivo, modo);
    if (salida == NULL)
    {
        fprintf(stderr, "reverse: cannot open file %s\n", salidaNombreArchivo); // Error de apertura archivo de salida
        fclose(salida);
        exit(1);
    }

    if (strcmp(entradaNombreArchivo, salidaNombreArchivo) == 0)
    {
        fprintf(stderr, "reverse: input and output file must differ\n"); // Error archivos tienen el mismo nombre
        fclose(entrada);
        fclose(salida);
        exit(1);
    }

    int cuentaLinea;                                  // Variable  pensada para tener el numero de lineas de texto
    char **lineas = leerArchivo(entrada, &cuentaLinea); //  Retorna array con lineas de texto y cantidad delineas de texto
   
    escribaLineasReversa(salida, lineas, cuentaLinea); // Se invoca funcion que almacena lineas de texto en forma invertida en salida fisica

    liberaMemoria(lineas, cuentaLinea); // libera memoria

    fclose(entrada); // Se cierra archivo de entrada
    fclose(salida);  // Se cierra archivo de salida
}

/**
 * La función asigna memoria dinámica
 */
char *asignarMemoriaLinea(unsigned int longitud)
{
    char *linea = (char *)malloc((longitud + 1) * sizeof(char)); // El array linea se construye dinamicamente
    if (linea == NULL)
    {
        fprintf(stderr, "error malloc failed\n");
        exit(1);
    }
    return linea; // Retorno del array a lineas de texto
}

/**
 * Funcion que recibe como parametro un archivo y el numero de lineas del archivo
 */
char **leerArchivo(FILE *archivo, int *numLineas)
{
    char **lineas = NULL;
    char buffer[LONGITUD_ANCHO_ARCHIVO];

    *numLineas = 0;

    while (fgets(buffer, LONGITUD_ANCHO_ARCHIVO, archivo) != NULL)
    { // Lectura de lineas de texto
        unsigned int longitud = strlen(buffer);
        if (longitud > 0 && buffer[longitud - 1] == '\n')
        { // Se quita salto de linea
            buffer[longitud - 1] = '\0';
        }

        char *linea = asignarMemoriaLinea(longitud); // Se asigna memoria
        strcpy(linea, buffer);                       // EL contenido buffer pasa a linea

        lineas = realloc(lineas, (*numLineas + 1) * sizeof(char *)); // SE redimenciona el array si buffer se desborda
        if (lineas == NULL)
        {
            fprintf(stderr, "error malloc failed\n");
            exit(1);
        }
        lineas[*numLineas] = linea; // Se almacena nueva linea de texto en array lineas

        (*numLineas)++; // Se actualiza valor de lo apuntado por
    }

    return lineas;
}

/**
 * La funcion lee una cantidad de lineas de texto entrada estandar
 */
char **leerLineas(int numLineas)
{
    char **lineas = (char **)malloc(numLineas * sizeof(char *)); // Se asigna memoria al array de lineas
    if (lineas == NULL)
    {
        fprintf(stderr, "error malloc failed\n");
        exit(1);
    }

    for (int i = 0; i < numLineas; ++i)
    {
        lineas[i] = (char *)malloc(LONGITUD_ANCHO_ARCHIVO * sizeof(char)); // Se asigna memoria a cada posicion del array
        if (lineas[i] == NULL)
        {
            fprintf(stderr, "error malloc failed\n");
            exit(1);
        }
        fgets(lineas[i], LONGITUD_ANCHO_ARCHIVO, stdin); // L,leido de la entrada standar se almace en el array lineas
        unsigned int longitud = strlen(lineas[i]);
        if (longitud > 0 && lineas[i][longitud - 1] == '\n')
        { // Se elina el salto de linea
            lineas[i][longitud - 1] = '\0';
        }
    }

    return lineas;
}

/**
 * La función invierte el orden de las líneas de un array iterando sobre la mitad del array
 */
void invertirLineas(char **lineas, int numLineas)
{
    char *temporal;
    for (int i = 0; i < numLineas / 2; ++i)
    {
        temporal = lineas[i]; // Siguientes lineas intercambian el contenido
        lineas[i] = lineas[numLineas - i - 1];
        lineas[numLineas - i - 1] = temporal;
    }
}

/**
 * Imprime lineas de texto en la salida estandar en forma inversa, recibe un puntero de puntero a cadena de caracteres
 */
void imprimirLineasInvertidas(char **lineas, int numLineas)
{
    for (int i = numLineas - 1; i >= 0; --i)
    {
        fprintf(stdout, "%s\n", lineas[i]);
    }
}
// Se imprime lineas texto salida estandar , recibe un arreglo de puntero a cadena de caracteres
void imprimirLineas(char **lineas, int numLineas)
{
    for (int i = 0; i < numLineas; ++i)
    {
        fprintf(stdout, "%s\n", lineas[i]);
    }
}

/**
 * La funcion recibe un array de punteros a cadena de caracteres y el numero de lineas o longitud del array
 */
void liberarMemoria(char **lineas, int numLineas)
{
    for (int i = 0; i < numLineas; ++i)
    { // Libera la memoria de cada apuntador a cadenas
        free(lineas[i]);
    }
    free(lineas); // Libera la memoria del array
}
/**
 * La funcion textInputUser()   da respuesta  a la opcion "./pgr"
 * Cada linea de texto se almacena en u arrray dinamico
 * En el ciclo se lee cadenas con fgets()  Si se detecta un final de archi vo o  Ctrl +D retorna un null
 *
 */
void textInputUser()
{
    char **lineas = NULL; // Declaración arreglo para almacenar las líneas de texto
    int numLineas = 0;
    char buffer[LONGITUD_ANCHO_ARCHIVO];
    // Tolo leido desde el teclado se almacena en buffer, la funcion recibe el tamaño del buffer evita desborde y recibe fuente
    while (fgets(buffer, sizeof(buffer), stdin) != NULL)
    { // Ciclo para la erntrada de texto
        unsigned int longitud = (unsigned int)strlen(buffer);
        if (longitud > 0 && buffer[longitud - 1] == '\n')
        { // Se borra el salto de linea
            buffer[longitud - 1] = '\0';
        }

        char *linea = strdup(buffer);                               // Realiza copia cadena asigna memoria dinamica y retorna puntero (bufer o cadena de entrada)
        lineas = realloc(lineas, (numLineas + 1) * sizeof(char *)); // Redimenciona bloque de memorias de lineas
        if (lineas == NULL)
        {
            fprintf(stderr, "error malloc failed\n");
            exit(1);
        }
        lineas[numLineas] = linea; // SE preserva nueva linea de texto en array de lineas
        numLineas++;
    }

    // Invertir y imprimir las líneas
    for (int i = numLineas - 1; i >= 0; --i)
    { // Imprime en inverso
        fprintf(stdout, "%s\n", lineas[i]);
    }

    // Liberar memoria
    for (int i = 0; i < numLineas; ++i)
    { // Libera memoria de cada elemento del array lineas[i]
        free(lineas[i]);
    }
    free(lineas); // Libera bloque lineas
}
