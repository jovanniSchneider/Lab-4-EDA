#include "TDAlista.h"
#include <stdio.h>
#include <stdlib.h>
#include "TDAaAVL.h"
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

//Entrada: lista enlazada con los datos de los intervalos de tiempo y 2 arboles, donde se encuentran las cotas
// inferiores y superiores respectivamente
//Salida: no entrega, ya que se utiliza paso por referencia
//Funcion: Guarda los datos de la lista enlazada en 1 arbol de cotas iferiores y en otro de cotas superiores (ambos AVL)
void llenarArboles(TDAlista * lista, TDAarbolAVL * cotasInf, TDAarbolAVL * cotasSup){
    if (!esListaVacia(lista))
    {
        nodo* auxiliar=lista->inicio;
        while (auxiliar!=NULL)
        {
            if(buscarNodoAVL(cotasInf,auxiliar->dato[0])== NULL)
                insertarNodoAVL(cotasInf,auxiliar->dato[0]);
            if(buscarNodoAVL(cotasSup,auxiliar->dato[1])== NULL)
                insertarNodoAVL(cotasSup,auxiliar->dato[1]);
            auxiliar=auxiliar->siguiente;
        }
    }
    else
        printf("La lista esta vacia\n");
}

//Entrada: 2 arboles con las cotas superiores e inferiores de los rangos horarios respectivamente y la lista
// de salida vacia
//Salida: No entrega, ya que utiliza paso por referencia
//Funcion: Genera los rangos horarios donde siempre habrá al menos una persona trabajando en atender el chat
void encontrarHorarios(TDAarbolAVL* cotasInf, TDAarbolAVL * cotasSup, TDAlista * salida){
    int preRango[2];
    preRango[0] = buscarMenorAVL(cotasInf,cotasInf->inicio);
    int flag = 1;
    int l1;
    int l2;
    while (flag == 1){
        preRango[1] = buscarMayorQue(cotasSup->inicio,preRango[0],-1);
        if (l1 == -1){
            int l2Aux = l2;
            do {
                l2 = l2Aux;
                l2Aux = buscarMayorQue(cotasSup->inicio,l2,-1);
            }while(l2 > preRango[1]);
            preRango[1] = l2;
            //insertarNodoFinal(salida,preRango);
            flag = 0;
            break;
        }
        l1 = buscarMayorQue(cotasInf->inicio,preRango[1],-1);
        while (buscarNodoAVL(cotasSup,l1)!=NULL) {
            l1 = buscarMayorQue(cotasInf->inicio, l1, -1);
        }
        l2 = buscarMayorQue(cotasSup->inicio,preRango[1],-1);
        while (l2 < l1){
            preRango[1] = l2;
            l2 = buscarMayorQue(cotasSup->inicio,l2,-1);
        }
        if (l1 == -1){
            while (l2 != -1){
                preRango[1] = l2;
                l2 = buscarMayorQue(cotasSup->inicio,l2,-1);
            }
        }
        insertarNodoFinal(salida,preRango);
        if (l1 != -1)
            preRango[0] = l1;
    }
}

void escribirArchivo(char * nombre, TDAlista * lista){
    FILE * archivo = fopen(nombre,"w");
    nodo * aux = lista->inicio;
    while (aux != NULL){
        fprintf(archivo,"%d %d\n",aux->dato[0],aux->dato[1]);
        aux = aux->siguiente;
    }
}