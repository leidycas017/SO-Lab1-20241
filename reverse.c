#include <stdio.h>  //Entradas y salidas estandar
#include <stdlib.h> //Para manejo dinámico de datos
#include <string.h> //Manejo de cadenas de caracteres

#define LONGITUD_ARCHIVO 4096 // Tamaño del buffer
/**
 *  La funcion recibe un archivo de entrada y el numero de lineas de texto retorna un apuntador a lieas de texto
 */
char **leerLinea(FILE *input, int *numLineas)
{
    char **lineas = NULL; // Arreglo lineas de texto
    char memoria[LONGITUD_ARCHIVO];

    *numLineas = 0;

    while (fgets(memoria, sizeof(memoria), input) != NULL)
    {                                                          // Si la operacion de recupera cadena de input es exito repite
        unsigned int longitud = (unsigned int)strlen(memoria); // Se calcula el tamaño del buffer
        if (longitud > 0 && memoria[longitud - 1] == '\n')
        { // Se elimina los saltos de linea
            memoria[longitud - 1] = '\0';
        }

        char *linea = strdup(memoria); // Retorna copia de la cadena

        lineas = realloc(lineas, (*numLineas + 1) * sizeof(char *)); // Si bloque de memoria no es suficiente redimenciona buffer
        if (lineas == NULL)
        {
            fprintf(stderr, "error malloc failed\n");
            exit(1);
        }
        lineas[*numLineas] = linea; // Se almacena linea de texto en una posicion del array lineas

        (*numLineas)++; // Incrementa en uno al contenido de lo apuntado por
    }

    return lineas;
}
// Se recibe como parametros unapuntador al archivo de salida, un apuntador a cadena de caracteres y la cantidad de lineas de texto
void escribaLineasReversa(FILE *salida, char **lineas, int cuentaLinea)
{
    for (int i = cuentaLinea - 1; i >= 0; i--)
    {                                     // Se recorre el array en sentido inverso
        fprintf(salida, "%s", lineas[i]); // Se almacena linea de texto en el archivo de salida
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

int resolverConflicto(char *archivoInput, char *archivoOutput)
{
    return strcmp(archivoInput, archivoOutput);
}

void procesoArchivos(char *entradaNombreArchivo, char *salidaNombreArchivo)
{
    const char *modo;
    int ret = resolverConflicto(entradaNombreArchivo, salidaNombreArchivo); // Codigo en prueba
    if (ret == 0)
    {
        modo = "r";
    }
    else
        modo = "w";
    FILE *entrada = fopen(entradaNombreArchivo, "r"); // Error de apertura archivo de entrada

    if (entrada == NULL)
    {
        fprintf(stderr, "error: cannot open file %s\n", entradaNombreArchivo);
        exit(1);
    }

    FILE *salida = fopen(salidaNombreArchivo, modo);
    if (salida == NULL)
    {
        fprintf(stderr, "error: cannot open file%s\n", salidaNombreArchivo); // Error de apertura archivo de salida
        fclose(salida);
        exit(1);
    }

    if (strcmp(entradaNombreArchivo, salidaNombreArchivo) == 0)
    {
        fprintf(stderr, "El archivo de entrada y salida deben diferir\n"); // Error archivos tienen el mismo nombre
        fclose(entrada);
        fclose(salida);
        exit(1);
    }

    int cuentaLinea;                                  // Variable  pensada para tener el numero de lineas de texto
    char **lineas = leerLinea(entrada, &cuentaLinea); //  Retorna array con lineas de texto y cantidad delineas de texto

    escribaLineasReversa(salida, lineas, cuentaLinea); // Se invoca funcion que almacena lineas de texto en forma invertida en salida fisica

    liberaMemoria(lineas, cuentaLinea); // libera memoria

    fclose(entrada); // Se cierra archivo de entrada
    fclose(salida);  // Se cierra archivo de salida
}
int pedirNumeroDeLineas() {
    int numLineas;
    fprintf(stdout, "Ingrese el número de líneas de texto: ");
    scanf("%d", &numLineas);                                         //Se captura el número de lineas entrada estandar
    while (getchar() != '\n');                                       // Eliminar salto de líneas
    return numLineas;
}

//La función asigna memoria dinámica 
char *asignarMemoriaLinea(size_t longitud) {
    char *linea = (char *)malloc((longitud + 1) * sizeof(char));     //El array linea se construye dinamicamente 
    if (linea == NULL) {
        fprintf(stderr,"error malloc failed\n");
        exit(1);
    }
    return linea;                                                            //Retorno del array a lineas de texto
}