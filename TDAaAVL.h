#include <stdio.h>
#include <stdlib.h>

/*--------------- estructura de datos -----------------*/

typedef struct nodoAVL
{
  int dato;
  struct nodoAVL* padre;
  struct nodoAVL* hijoIzquierdo;
  struct nodoAVL* hijoDerecho;
}nodoAVL;

typedef struct 
{
  nodoAVL* inicio;
}TDAarbolAVL;

/*--------------- operaciones de creación -----------------*/

TDAarbolAVL* crearAVLVacio()
{
  TDAarbolAVL* arbol=(TDAarbolAVL*)malloc(sizeof(TDAarbolAVL));
  arbol->inicio=NULL;
  return arbol;
}

int esAVLvacio(TDAarbolAVL* arbol)
{
  if (arbol->inicio == NULL)
    return 1;
  else
    return 0;
}

/*--------------- operaciones de posicion -----------------*/

//devuelve NULO si el árbol está vacío
nodoAVL* raizAVL(TDAarbolAVL* arbol)
{
  if (arbol!=NULL)
    return arbol->inicio;
  return NULL;
}

nodoAVL* padreNodoAVL(TDAarbolAVL* arbol, nodoAVL* nodo)
{
  if (nodo!=NULL)
    return nodo->padre;
}

nodoAVL* hijoIzqNodoAVL(TDAarbolAVL* arbol, nodoAVL* nodo)
{
  if (nodo!=NULL)
    return nodo->hijoIzquierdo;
}

nodoAVL* hijoDerNodoAVL(TDAarbolAVL* arbol, nodoAVL* nodo)
{
  if (nodo!=NULL)
    return nodo->hijoDerecho;
}

int buscarMenorAVL(TDAarbolAVL* arbol, nodoAVL* nodo)
{
  nodoAVL* aux;
  if (!esAVLvacio(arbol))
  {
    aux=nodo;
    while (aux!=NULL)
    {
      if (aux->hijoIzquierdo!=NULL)
      {
        aux=aux->hijoIzquierdo;
      }
      else //es el aux es nodo que contiene dato
      {
        return aux->dato;
      }
    }
  }
  return -1;
}

int esHojaAVL(TDAarbolAVL* arbol, nodoAVL* nodo)
{
  if (!esAVLvacio(arbol))
  {
    if ((nodo->hijoIzquierdo==NULL)&&(nodo->hijoDerecho==NULL))
      return 1;
  }
  return 0;
}

/*--------------- operaciones de recorrido -----------------*/

void recorridoInorden(nodoAVL* nodo)
{
  if (nodo!=NULL)
  {
    //hijo izquierdo
    recorridoInorden(nodo->hijoIzquierdo);
    // raiz
    printf("%d ",nodo->dato);
    // hijo derecho
    recorridoInorden(nodo->hijoDerecho);
  }
}

void recorridoInordenAVL(TDAarbolAVL* arbol){
  if (!esAVLvacio(arbol))
  {
    printf("INORDEN: ");
    recorridoInorden(arbol->inicio);
    printf("\n");
  }
  else
    printf("El árbol AVL está vacío\n");
}

//imprimirNodo, función que imprime un nodo
//DOM: TDAnodoAVL
//REC: void
void imprimirNodo(nodoAVL* nodo){
  if (nodo->padre == NULL){printf("nodo padre: es la raiz\n");}
  else{printf("nodo padre: %d\n",nodo->padre->dato);}
	printf("nodo: %d\n",nodo->dato);
	if (nodo->hijoIzquierdo == NULL){printf("hijo izq: %s\n",nodo->hijoIzquierdo);}
	else{printf("hijo izq: %d\n",nodo->hijoIzquierdo->dato);}
	if (nodo->hijoDerecho == NULL){printf("hijo der: %s\n",nodo->hijoDerecho);}
	else{printf("hijo der: %d\n",nodo->hijoDerecho->dato);}
}

/*------------------ operaciones de balance --------------------*/

/***------------- actividad 1 -------------***/
//largoArbol, función que recorre el arbol hacia abajo, desde un nodo, para conseguir la altura del nodo
//DOM: TDAarbolAVL X TDAnodoAVL
//REC: int
int largoArbol(TDAarbolAVL* arbol, nodoAVL* nodo){
  if (nodo == NULL) {
    return 0;
  }
  else {
    //Caso hoja, no posee hijos
    if (esHojaAVL(arbol,nodo)) {
      return 1;
    }
    //Caso ambos hijos
    else if (nodo->hijoIzquierdo != NULL && nodo->hijoDerecho != NULL){
      if (largoArbol(arbol,nodo->hijoIzquierdo) > largoArbol(arbol,nodo->hijoDerecho)){
        return (largoArbol(arbol,nodo->hijoIzquierdo) +1);
      }
      else{
        return (largoArbol(arbol,nodo->hijoDerecho) +1);
      }
    }
    //Caso un hijo hacia la izquierda
    else if (nodo->hijoIzquierdo != NULL){
      return (largoArbol(arbol,nodo->hijoIzquierdo)+1);
    }
    //Caso un hijo hacia la derecha
    else if (nodo->hijoDerecho != NULL){
      return (largoArbol(arbol,nodo->hijoDerecho)+1);
    }
    
    return (largoArbol(arbol,nodo->hijoIzquierdo)+largoArbol(arbol,nodo->hijoDerecho)+1);
  }
}

//esBalanceadoNodoAVL, función que retorna 1 si el arbol está balanceado, sino 0
//DOM: TDAarbolAVL X TDAnodoAVL
//REC: int (boolean)
int esBalanceadoNodoAVL(TDAarbolAVL* arbol, nodoAVL* nodo){
  if (!esAVLvacio(arbol)){
    int contador = 0;

    //Obtiene la altura del hijo izquierdo
    int ladoIzq = largoArbol(arbol, nodo->hijoIzquierdo);
     
    //Obtiene la altura del hijo derecho
    int ladoDer = largoArbol(arbol, nodo->hijoDerecho);   
    
    printf("Para el nodo %d:\nh ladoDer = %d\nh ladoIzq = %d\n", nodo->dato, ladoDer, ladoIzq);
    if (ladoIzq < ladoDer){
      while(ladoIzq < ladoDer){
        ladoIzq = ladoIzq + 1;
        contador = contador + 1;
      }
    }
    else if (ladoDer < ladoIzq) {
      while (ladoDer < ladoIzq){
        ladoDer = ladoDer + 1;
        contador = contador + 1;
      }
    }
    if (contador == 0){
        return 1;
      }
    else {
      return 0;
    }
  }
  else {printf("El arbol esta vacio\n");}
}

/***------------- actividad 2 -------------***/
void movimientosBalanceAVL(TDAarbolAVL* arbol, nodoAVL* z){
  //Defino estas variables para "limpiar" el código
  nodoAVL* hijoIzq = z->hijoIzquierdo;
  nodoAVL* hijoDer = z->hijoDerecho;
  //Se aplicará una serie de movimientos dependendiendo del desbalance que posea
  //Caso "L"
  if (largoArbol(arbol,hijoIzq) > largoArbol(arbol,hijoDer)){
    //Caso a: "LL"
    if (largoArbol(arbol,hijoIzq->hijoIzquierdo) > largoArbol(arbol,hijoIzq->hijoDerecho)){
      printf("Se le aplica un movimiento LL a %d\n",z->dato);
      //Definimos "x" e "y" + los nodos a intercambiar
      nodoAVL* y = z->hijoIzquierdo;
      nodoAVL* x = y->hijoIzquierdo;
      nodoAVL* t2 = y->hijoDerecho;
      //En caso de que Z no tenga padre:
      if (z->padre == NULL){
        arbol->inicio = y;
        y->padre = NULL;
      }
      else{//Sino, vemos cuál de los dos hijos es:
        if (z->padre->hijoIzquierdo == z){//caso izq
          z->padre->hijoIzquierdo = y;
          y->padre = z->padre;
        }
        else if (z->padre->hijoDerecho == z){//caso der
          z->padre->hijoDerecho = y;
          y->padre = z->padre;
        }
      }
      y->hijoDerecho = z;
      if (z != NULL){z->padre = y;}
      z->hijoIzquierdo = t2;
      if (t2 != NULL){t2->padre = z;}
    }
    //Caso c: "LR"
    else if (largoArbol(arbol,hijoIzq->hijoIzquierdo) < largoArbol(arbol,hijoIzq->hijoDerecho)
    || ((largoArbol(arbol,hijoIzq->hijoIzquierdo) == largoArbol(arbol,hijoIzq->hijoDerecho)) 
    && hijoIzq->hijoIzquierdo != NULL && hijoIzq->hijoDerecho != NULL)){
      printf("Se le aplica un movimiento LR a %d\n",z->dato);
      //Definimos "x" e "y" + los nodos a intercambiar
      nodoAVL* y = z->hijoIzquierdo;
      nodoAVL* x = y->hijoDerecho;
      nodoAVL* t1 = x->hijoIzquierdo;
      nodoAVL* t2 = x->hijoDerecho;
      //En caso de que Z no tenga padre:
      if (z->padre == NULL){
        arbol->inicio = x;
        x->padre = NULL;
      }
      else{//Sino, vemos cuál de los dos hijos es:
        if (z->padre->hijoIzquierdo == z){//caso izq
          z->padre->hijoIzquierdo = x;
          x->padre = z->padre;
        }
        else if (z->padre->hijoDerecho == z){//caso der
          z->padre->hijoDerecho = x;
          x->padre = z->padre;
        }
      }
      x->hijoIzquierdo = y;
      if (y != NULL){y->padre = x;}
      x->hijoDerecho = z;
      if (z != NULL){z->padre = x;}
      y->hijoDerecho = t1;
      if (t1 != NULL){t1->padre = y;}
      z->hijoIzquierdo = t2;
      if (t2 != NULL){t2->padre = z;}
    }
  }
  //Caso "R"
  else if(largoArbol(arbol,hijoIzq) < largoArbol(arbol,hijoDer)){
    //Caso b: "RR"
    if (largoArbol(arbol,hijoDer->hijoIzquierdo) < largoArbol(arbol,hijoDer->hijoDerecho)){
      printf("Se le aplica un movimiento RR a %d\n",z->dato);
      //Definimos "x" e "y" + los nodos a intercambiar
      nodoAVL* y = z->hijoDerecho;
      nodoAVL* x = y->hijoDerecho;
      nodoAVL* t1 = y->hijoIzquierdo;
      //En caso de que Z no tenga padre:
      if (z->padre == NULL){
        arbol->inicio = y;
        y->padre = NULL;
      }
      else{//Sino, vemos cuál de los dos hijos es:
        if (z->padre->hijoIzquierdo == z){//caso izq
          z->padre->hijoIzquierdo = y;
          y->padre = z->padre;
        }
        else if (z->padre->hijoDerecho == z){//caso der
          z->padre->hijoDerecho = y;
          y->padre = z->padre;
        }
      }
      y->hijoIzquierdo = z;
      if (z != NULL){z->padre = y;}
      z->hijoDerecho = t1;
      if (t1 != NULL){t1->padre = z;}
    }
    //Caso d: "RL"
    else if (largoArbol(arbol,hijoDer->hijoIzquierdo) > largoArbol(arbol,hijoDer->hijoDerecho)
    || ((largoArbol(arbol,hijoDer->hijoIzquierdo) == largoArbol(arbol,hijoDer->hijoDerecho)) 
    && hijoDer->hijoIzquierdo != NULL && hijoDer->hijoDerecho != NULL)){
      printf("Se le aplica un movimiento RL a %d\n",z->dato);
      //Definimos "x" e "y" + los nodos a intercambiar
      nodoAVL* y = z->hijoDerecho;
      nodoAVL* x = y->hijoIzquierdo;
      nodoAVL* t1 = x->hijoIzquierdo;
      nodoAVL* t2 = x->hijoDerecho;
      //En caso de que Z no tenga padre:
      if (z->padre == NULL){
        arbol->inicio = x;
        x->padre = NULL;
      }
      else{//Sino, vemos cuál de los dos hijos es:
        if (z->padre->hijoIzquierdo == z){//caso izq
          z->padre->hijoIzquierdo = x;
          x->padre = z->padre;
        }
        else if (z->padre->hijoDerecho == z){//caso der
          z->padre->hijoDerecho = x;
          x->padre = z->padre;
        }
      }
      x->hijoIzquierdo = z;
      if (z != NULL){z->padre = x;}
      x->hijoDerecho = y;
      if (y != NULL){y->padre = x;}
      z->hijoDerecho = t1;
      if (t1 != NULL){t1->padre = z;}
      y->hijoIzquierdo = t2;
      if (t2 != NULL){t2->padre = y;}
    }
  }
}

void recuperarBalanceAVL(TDAarbolAVL* arbol, nodoAVL* z){
  while (z != NULL) {
    nodoAVL* zHI = z->hijoIzquierdo;
    nodoAVL* zHD = z->hijoDerecho;
    imprimirNodo(z);printf("\n");
    movimientosBalanceAVL(arbol,z);
    //Para evitar los ciclos infinitos
    if (z->padre == zHI || z->padre == zHD){
      z = z->padre->padre;
    }
    else {z = z->padre;}
  }
}

/*--------------- operaciones de búsqueda -----------------*/

nodoAVL* buscarNodoRecursivoAVL(nodoAVL* nodo, int dato)
{
  if (nodo!=NULL)
  {
    if (nodo->dato==dato)
      return nodo;
    else
    {
      if (dato < nodo->dato)
        return buscarNodoRecursivoAVL(nodo->hijoIzquierdo,dato);
      else
        return buscarNodoRecursivoAVL(nodo->hijoDerecho,dato);
    }
  } else
      return NULL;
}

nodoAVL* buscarNodoAVL(TDAarbolAVL* arbol, int dato)
{
  nodoAVL* aux;
  if (!esAVLvacio(arbol))
  {
    aux=arbol->inicio;
    return buscarNodoRecursivoAVL(aux,dato);
  }
  else
    return NULL;
}

/*--------------- operaciones de actualización -----------------*/

void insertarRaizAVL(TDAarbolAVL* arbol, int dato)
{
  nodoAVL* raiz=(nodoAVL*)malloc(sizeof(nodoAVL));
  raiz->dato=dato;
  raiz->hijoIzquierdo=NULL;
  raiz->hijoDerecho=NULL;
  raiz->padre=NULL;
  arbol->inicio=raiz;
}

void insertarNodoRecursivoAVL(TDAarbolAVL* arbol, nodoAVL* nodo, int dato)
{
  nodoAVL* nuevo;

  nuevo=(nodoAVL*)malloc(sizeof(nodoAVL));
  nuevo->dato=dato;
  nuevo->hijoIzquierdo=NULL;
  nuevo->hijoDerecho=NULL;

 if (dato <= nodo->dato)  //vamos por la izquierda
  {
    if (nodo->hijoIzquierdo==NULL) // no hay un hijo a la izquierda
    {
      nodo->hijoIzquierdo=nuevo;
      nuevo->padre=nodo;
    }
    else  //si ya hay un hijo a la izquierda
    {
      insertarNodoRecursivoAVL(arbol,nodo->hijoIzquierdo,dato);
    }
  }
  else //vamos por la derecha
  {
    if (nodo->hijoDerecho==NULL) // no hay un hijo a la izquierda
    {
      nodo->hijoDerecho=nuevo;
      nuevo->padre=nodo;
    }
    else  //si ya hay un hijo a la izquierda
    {
      insertarNodoRecursivoAVL(arbol,nodo->hijoDerecho,dato);
    }
  }
  /*** recuperarBalanceAVL(arbol,nodo); ***/
}

void insertarNodoAVL(TDAarbolAVL* arbol, int dato)
{
  if (!esAVLvacio(arbol))
  {
    insertarNodoRecursivoAVL(arbol,arbol->inicio,dato);
  }
  else
    insertarRaizAVL(arbol,dato);
}


/*** -------- actividad 3 ---------- ***/
void eliminarNodoAVL(TDAarbolAVL* arbol, int dato);

/*** -------- funciones extra -------- ***/

//nodoMenorAlturaAVL, función que busca el nodo con menor altura dentro del arbol
//DOM: TDAarbolAVL
//REC: TDAnodoAVL
nodoAVL* nodoMenorAlturaAVL(TDAarbolAVL* arbol){
  nodoAVL* aux;
  if (!esAVLvacio(arbol)){
    aux = arbol->inicio;
    //Va viendo la altura de cada lado y se va por el lado más alto, hasta llegar a una hoja
    while (!esHojaAVL(arbol,aux)){
      if (largoArbol(arbol,aux->hijoIzquierdo) > largoArbol(arbol,aux->hijoDerecho)){
        aux = aux->hijoIzquierdo;
      }
      else if (largoArbol(arbol,aux->hijoIzquierdo) < largoArbol(arbol,aux->hijoDerecho)){
        aux = aux->hijoDerecho;
      }
    }
  }
  else{printf("El arbol esta vacio");}
  
  return aux;
}

int buscarMayor(nodoAVL * nodo){
    if (nodo == NULL){
        return -1;
    } else if (nodo->hijoDerecho == NULL){
        return nodo->dato;
    }else
        buscarMayor(nodo->hijoDerecho);
}

int buscarMayorQue(nodoAVL * nodo, int dato,int mayor){
    if(nodo == NULL){
        return mayor;
    }
    if (nodo->dato > dato){
            mayor = nodo->dato;
            buscarMayorQue(nodo->hijoIzquierdo,dato,mayor);
    }else
        buscarMayorQue(nodo->hijoDerecho,dato,mayor);
}

int buscarMenorQue(nodoAVL * nodo,int dato,int menor){
    if (nodo == NULL)
        return menor;
    if (nodo->dato < dato){
        menor = nodo->dato;
        buscarMenorQue(nodo->hijoDerecho,dato,menor);
    }else
        buscarMenorQue(nodo->hijoIzquierdo,dato,menor);
}
