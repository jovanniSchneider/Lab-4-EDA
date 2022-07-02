#include <stdio.h>
#include "functions.h"
int main() {
    TDAlista * lista = crearListaVacia();
    TDAarbolAVL * cotasInf = crearAVLVacio();
    TDAarbolAVL * cotasSup = crearAVLVacio();
    leerArchivo("entrada1.in",lista);
    llenarArboles(lista,cotasInf,cotasSup);
    if (!esListaVacia(lista))
    {
        nodo* auxiliar=lista->inicio;
        while (auxiliar!=NULL)
        {
            auxiliar=auxiliar->siguiente;
        }
    }
    TDAlista * salida = crearListaVacia();
    encontrarHorarios(cotasInf,cotasSup,salida);
    escribirArchivo("jeje.out",salida);
    liberarLista(lista);
    return 0;
}
