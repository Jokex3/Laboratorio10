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

typedef struct Tnodo{
    char *palabra;
    int totalDePalabras;
}Nodo;

int letraAnum(char letra);
int operacionHash(char *palabra,int tamHash);
int operacionHash2(char *palabra,int tamHash);
void iniciarTabla(Nodo *tablaHash[],int tamTabla);
int cantidadDePalabrasArchivo(char *nombreArchivo);
Nodo *crearNodo(Nodo *tablaHash[],char *palabra,int posicion);
void insertarPalabra(Nodo *tablaHash[],char *palabra,int tamTabla);
int leerArchivo(Nodo* tablaHash[],char *nombre, int tamTabla);
int creaTablaHash(char *nombreArchivo,int porcentajeDeUso);

int operacionHash(char *palabra,int tamHash){
    if(palabra == NULL){
        return -1;
    }
    unsigned int radix = 0;
    int cont=0;
    while((palabra[cont]!='\0')&&(cont<6)){(
        radix = radix + letraAnum(palabra[cont]*pow(27,cont)));
        cont++;
    }
    radix = radix%tamHash;
    return (radix);
}

int letraAnum(char letra){
    if(letra == 'ñ'){
        return 14;
    }
    if(letra == 'o'){
        letra - 'a';
    }
    letra = (letra - 'a') + 1;
    return letra;
}

int operacionHash2(char *palabra,int tamHash){
    if(palabra == NULL){
        return -1;
    }
    unsigned int radix = 0;
    int cont=0;
    while((palabra[cont]!='\0')&&(cont<6)){(
        radix = radix + letraAnum(palabra[cont]*pow(27,cont)));
        cont++;
    }
    radix = 1+(radix%tamHash-1);
    return (radix);
}

void iniciarTabla(Nodo *tablaHash[],int tamTabla){
    for(int cont=0; cont<tamTabla; cont++){
        tablaHash[cont]->palabra = NULL;
    }
}

int cantidadDePalabrasArchivo(char *nombreArchivo){
    strcat(nombreArchivo,".txt");
    FILE *archivo = fopen(nombreArchivo,"r");
    int contador=0;
    char string[30];
    fgets(string,30,archivo);
    while(!feof(archivo)){
        for(int i=0;i<strlen(string);i++){
            if(string[i] == '\n'){
                contador++;
            }
            contador++;
        }
    }
    contador = contador+1;

    fclose(archivo);
    return contador;
}

Nodo *crearNodo(Nodo *tablaHash[],char *palabra,int posicion){
    int largo = strlen(palabra);
    tablaHash[posicion]->palabra = (char*)malloc(sizeof(char)*largo+1);
    strcpy(tablaHash[posicion]->palabra,palabra);

    return (tablaHash);
}

void insertarPalabra(Nodo *tablaHash[],char *palabra,int tamTabla){
    int resultado = operacionHash(palabra,tamTabla);
    int resultado2 = operacionHash2(palabra,tamTabla);

    if(tablaHash[resultado]->palabra == NULL){
        crearNodo(tablaHash,palabra,resultado);   
    }else{
        crearNodo(tablaHash,palabra,resultado2);
    }
}

int leerArchivo(Nodo* tablaHash[],char *nombre, int tamTabla){
   strcat(nombre,".txt"); //Agrega .txt despues del ultimo caracter del string
    char *palabraExtraida;
    int totalDePalabras = 0;
    FILE *archivo = fopen(nombre,"r");
    while(!feof(archivo)){ //Mientras no sea final de archivo
        palabraExtraida = (char *)malloc(sizeof(char)*30);
        fscanf(archivo,"%s",palabraExtraida);//Copia el string del archivo y la deja en el string palabraextraida
        insertarPalabra(tablaHash,palabraExtraida,tamTabla);//Ingresa la palabra al nuevo nodo
        totalDePalabras++;
        free(palabraExtraida);
    }
    fclose(archivo);
    tablaHash[0]->totalDePalabras = totalDePalabras; //Se guarda el total de palabras en la estructura, pero solo en la primera posicion
    return totalDePalabras;
}

int creaTablaHash(char *nombreArchivo,int porcentajeDeUso){
    int tamHash = cantidadDePalabrasArchivo(nombreArchivo);
    tamHash = tamHash*porcentajeDeUso;
    return tamHash;
}