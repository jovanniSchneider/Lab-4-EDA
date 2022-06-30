#include "TDAlista.h"
#include <stdio.h>
#include <stdlib.h>

// Entrada: nombre del archivo ("string") y puntero a estructura del tipo lista enlazada
// Salida: no entrega, ya que se utiliza paso por referencia
// Funcion: Lee el archivo y si es que existe guarda sus datos en la lista enlazada.
void leerArchivo(char *nombreArchivo, TDAlista *lista)
{
    FILE *archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL)
    {
        printf("Hubo un problema al leer el archivo\n");
    }
    else
    {
        int *dato = (int *)malloc(sizeof(int) * 2);
        while (fscanf(archivo, "%d %d", &dato[0], &dato[1]) != EOF)
        {
            insertarNodoFinal(lista, dato);
        }
        fclose(archivo);
    }
}