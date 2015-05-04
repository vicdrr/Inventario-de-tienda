//
//  main.c
//  Prueba
//
//  Created by Víctor David Rivera Ramírez on 04/05/15.
//  Copyright (c) 2015 Víctor David Rivera Ramírez. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct nodo{
    int codigo;
    int stock;
    char * nombre;
    struct nodo * izq;
    struct nodo * der;
    struct nodo * sig;
}nodoArbol;

nodoArbol arreglo[10];

nodoArbol * buscar(int bcodigo);
nodoArbol * eliminar(int ecodigo);
nodoArbol * raiz=NULL;
nodoArbol * nuevo=NULL;
nodoArbol datos();
void recorrido(nodoArbol *actual);
//void ordenamiento(nodoArbol *actual);
void insertar(nodoArbol producto);

int main(){
    int opcion, bcodigo, ecodigo;
    nodoArbol producto;
    nodoArbol* busqueda;
    nodoArbol * eliminacion;
    
    
    do{
        printf ("\n");
        printf ("**********************************************\n");
        printf ("*               Abarrotera                   *");
        printf ("\n*   Bienvenido al sistema de venta           *");
        printf ("\n*        de la abarrotera, que desea hacer:  *");
        printf ("\n*                                            *");
        printf ("\n*        1. Introducir Producto nuevo        *");
        printf ("\n*        2. Busqueda de Productos            *");
        printf ("\n*        3. Eliminar productos del catalogo  *");
        printf ("\n*        4. Salir                            *");
        printf ("\n**********************************************");
        printf ("\n");
        printf("\n\nIntroducir opcion\t");
        scanf("%d", & opcion);
        
        if(opcion==1){
            producto = datos();
            insertar(producto);
        }
        
        if(opcion==2){
            printf("Introducir valor a buscar");
            scanf("%d", & bcodigo);
            busqueda= buscar(bcodigo);
            printf("%d, %d, %s\n", busqueda->codigo, busqueda->stock, busqueda->nombre);
        }
        if(opcion==3){
            printf("Introducir codigo de producto que se desea eliminar");
            scanf("%d", & ecodigo);
            eliminacion = eliminar(ecodigo);
            if(eliminacion == NULL)
                printf("No existe el codigo ingresado");
            else{
                printf("\nEl porducto a eliminar es:");
                printf("%d", eliminacion->codigo);
                printf("%s", eliminacion->nombre);
                printf("%d", eliminacion->stock);
                
                if(eliminacion == raiz) raiz = NULL;
                free(eliminacion);
                
            }
            
        }
    }while(opcion !=4);
    return 0;
}

nodoArbol datos(){
    nodoArbol producto;
    producto.nombre=(char *)malloc(sizeof(50));
    
    fflush(stdin);
    printf("\n\nIntroducir nombre de producto\t");
    //gets(producto.nombre);
    scanf("%s", &producto.nombre);
    printf("\nIntroducir stock\t");
    scanf("%d", & producto.stock);
    printf("\nIntroducir numero de codigo\t");
    scanf("%d", & producto.codigo);
    
    return producto;
    
}

void insertar(nodoArbol producto){
    if(raiz==NULL){
        raiz=(nodoArbol *)malloc(sizeof(nodoArbol));
        raiz->codigo=producto.codigo;
        raiz->stock=producto.stock;
        raiz->nombre=producto.nombre;
        raiz->izq=NULL;
        raiz->der=NULL;
        return;
    }
    
    nodoArbol * anterior;
    nodoArbol * recorre = raiz;
    
    while(recorre != NULL && recorre->codigo != producto.codigo){
        anterior = recorre;
        if(producto.codigo < recorre->codigo)
            recorre = recorre->izq;
        else
            recorre = recorre->der;
    }
    
    if(recorre != NULL){
        printf("El codigo insertado ya existe");
        return;
    }
    
    nodoArbol * nuevo = (nodoArbol *)malloc(sizeof(nodoArbol));
    nuevo->codigo = producto.codigo;
    nuevo->stock = producto.stock;
    nuevo ->nombre= producto.nombre;
    nuevo->izq = NULL;
    nuevo->der = NULL;
    
    if(producto.codigo < anterior->codigo)
        anterior->izq = nuevo;
    else
        anterior->der = nuevo;
}

nodoArbol * buscar(int bcodigo){
    
    nodoArbol * recorre = raiz;
    
    while(recorre != NULL && recorre->codigo != bcodigo){
        if(bcodigo < recorre->codigo)
            recorre = recorre->izq;
        else
            recorre = recorre->der;
        
    }
    
    return recorre;
}

nodoArbol * eliminar(int ecodigo){
    
    nodoArbol * padre = NULL;
    nodoArbol * actual = raiz;
    
    while(actual && actual->codigo != ecodigo){
        padre = actual;
        if(ecodigo < actual->codigo)
            actual = actual->izq;
        else
            actual = actual->der;
    }
    if(actual==NULL)    return NULL;
    
    //***********************************************/
    //*******Analisis de casos para eliminacion******/
    //***********************************************/
    
    
    //***********************************************/
    //******Caso 1: nodo hoja************************/
    //***********************************************/
    
    
    
    if(actual->izq == NULL && actual->der == NULL){
        if(raiz == actual) return raiz;
        if(ecodigo < padre->codigo)
            padre->izq = NULL;
        else
            padre->der = NULL;
        return actual;
    }
    
    //***********************************************/
    //*********Caso 2: nodo con un hijo**************/
    //***********************************************/
    
    if(actual->izq == NULL || actual->der == NULL){
        if(raiz == actual){
            if(raiz->izq == NULL)
                raiz = raiz->der;
            else
                raiz = raiz->izq;
            return actual;
        }
        
        if(ecodigo < padre->codigo)
            if(actual->izq == NULL)
                padre->izq = actual->der;
            else
                padre->izq = actual->izq;
            else
                if(actual->izq == NULL)
                    padre->der = actual->der;
                else
                    padre->der = actual->izq;
        return actual;
    }
    
    //***********************************************/
    //******Caso 3: nodo con dos hijos***************/
    //***********************************************/
    
    nodoArbol * sucesor = actual->der;
    nodoArbol * padreSucesor = NULL;
    
    while(sucesor->izq != NULL){
        padreSucesor = sucesor;
        sucesor = sucesor->izq;
    }
    
    nodoArbol * retorno = (nodoArbol *)malloc(sizeof(nodoArbol));
    retorno->codigo = actual->codigo;
    
    actual->codigo = sucesor->codigo;
    if(padreSucesor == NULL)
        actual->der = sucesor->der;
    else
        padreSucesor->izq = sucesor->der;
    free(sucesor);
    return retorno;
    
    
}