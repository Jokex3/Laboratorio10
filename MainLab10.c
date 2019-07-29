#ifndef stdio_h
#include <stdio.h>
#define stdio_h
#endif

#ifndef stdlib_h
#include <stdlib.h>
#define stdlib_h
#endif

#ifndef time_h
#include <time.h>
#define time_h
#endif

#ifndef string_h
#include "string.h"
#define string_h
#endif

#ifndef math_h
#include "math.h"
#define math_h
#endif

#ifndef Lab10_h
#include "Lab10.h"
#define Lab10_h
#endif


int main(){
    char *nombreArchivo;
    nombreArchivo = (char *)malloc(sizeof(char)*50);
    int porcentajeDeUso;
    printf("Ingrese el nombre del archivo: ");
    scanf("%s",nombreArchivo);
    printf("\nIngrese el porcentaje que usar%c: ",160);
    scanf("%i",&porcentajeDeUso);

    int tamHash = creaTablaHash(nombreArchivo,porcentajeDeUso);

    Nodo *tablaHash[tamHash];
    iniciarTabla(tablaHash,tamHash);

    return 0;    
}