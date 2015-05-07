//
//  main.c
//  Proyecto Final EDD
//
//  Created by Víctor David Rivera Ramírez on 23/04/15.
//  Copyright (c) 2015 Víctor David Rivera Ramírez. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 30

int tabla_hash[SIZE] = {0};

typedef struct abarrotera{
    char nombre[20];
    int stock;
    int codigo;
    float precio;
    
    //struct abarrotera *siguiente;
    //struct abarrotera *anterior;
    
}INVENTARIO;

INVENTARIO Abarrotera[30];

int hash(int clave){
    //esta parte es modular
    
    return clave % SIZE;
}

void registroProducto(int id){
    //Aqui se le da nombre y stock al codigo
    
    printf("\nNombre del producto: ");
    fflush(stdin);
    //gets(Abarrotera[id].nombre);
    scanf("%s", &Abarrotera[id].nombre);
    
    printf("\nStock del producto: ");
    fflush(stdin);
    scanf("%d", &Abarrotera[id].stock);
    
    printf("\nPrecio del producto: $");
    fflush(stdin);
    scanf("%f", &Abarrotera[id].precio);
    printf("\n");
    Abarrotera[id].codigo = id;
    
}

void buscaProducto(int id){
    //al buscar esta te da nombre, codigo y stock del producto
    
    printf("\nPrecio del producto:\t %.2f", Abarrotera[id].precio);
    printf("\nNombre del producto:\t %s", Abarrotera[id].nombre);
    printf("\nStock  del producto:\t %d", Abarrotera[id].stock);
    printf("\nCodigo del producto:\t %d\n", Abarrotera[id].codigo);
}

void sumaStock(int id){
    //incrementa stock de ventas
    int suma;
    
    printf("\nCantidad del producto que llego: ");
    scanf("%d", &suma);
    Abarrotera[id].stock = (Abarrotera[id].stock)+suma;
    printf("\nTiene un total de %d en stock", Abarrotera[id].stock);
}

void restaStock(int id){
    //disminuye stock de ventas
    int resta;
    float precio;
    
    printf("\nCantidad del producto que se vende: ");
    scanf("%d", &resta);
    if (resta<Abarrotera[id].stock) {
        Abarrotera[id].stock = (Abarrotera[id].stock)-resta;
        precio = resta*Abarrotera[id].precio;
        printf("\nSeria un total de: %d %s\nPor el precio de: $%f", resta, Abarrotera[id].nombre, precio);
    }else{
        printf("\nNo tiene suficiente producto en Stock\n");
    }
}

int entradasProducto(int clave){
    //Aqui se incrementa el stock del producto
    
    int indice;
    indice = buscar(clave);
    
    if (indice == -1) {
        printf("Debe registrar primero el producto\n");
        return 0;
    }else{
        sumaStock(indice);
        return 1;
    }

}

int salidasProducto(int clave){
    //Aqui se incrementa el stock del producto
    
    int indice;
    indice = buscar(clave);
    
    if (indice == -1) {
        printf("No existe el producto\n");
        return 0;
    }else{
        restaStock(indice);
        return 1;
    }
}

int insertar (int clave){
    //aqui se inserta
    int indice;
    indice = hash(clave);
    
    if (tabla_hash[indice] != 0) {
        int inicio = indice + 1;
        printf("Hubo Colision\n");
        while (tabla_hash[inicio % SIZE] != 0 && inicio % SIZE != indice) {
            printf("Hubo Colision\n");
            inicio++;
        }
        if (tabla_hash[inicio % SIZE] == 0) {
            tabla_hash[indice] = clave;
            registroProducto(indice);
            return 1;
        }else{
            printf("Espacio agotado\n");
            return 0;
        }
    }else{
        tabla_hash[indice] = clave;
        registroProducto(indice);
        return 1;
    }
    
    
    
}

int buscar (int clave){
    int indice;
    
    indice = hash(clave);
    
    if (tabla_hash[indice] == clave) {
        buscaProducto(indice);
        return indice;
    }else{
        int inicio = indice + 1;
        printf("Hubo Colision\n");
        while (tabla_hash[inicio % SIZE] != clave && inicio % SIZE != indice) {
            printf("Hubo Colision\n");
            inicio++;
        }
        if (tabla_hash[inicio % SIZE] == clave) {
            tabla_hash[indice] = clave;
            buscaProducto(indice);
            return inicio % SIZE;
        }else{
            
            return -1;
        }
    }
    
}

int eliminar (int clave){
    int indice;
    indice = buscar(clave);
    
    if (indice == -1) {
        printf("No existe\n");
        return 0;
    }else{
        tabla_hash[indice] = 0;
        return 1;
    }
}

int menu_Ppal (){
    
    int opcion;
    printf ("\n");
    printf ("**********************************************\n");
    printf ("*               Abarrotera                   *");
    printf ("\n*   Bienvenido al sistema de venta           *");
    printf ("\n*        de la abarrotera, que desea hacer:  *");
    printf ("\n*                                            *");
    printf ("\n*        1. Ventas                           *");
    printf ("\n*        2. Registro de Productos            *");
    printf ("\n*        3. Eliminar productos del catalogo  *");
    printf ("\n*        4. Salir                            *");
    printf ("\n**********************************************");
    printf ("\n");
    printf ("\nElige la opcion numero: ");
    scanf ("%i",&opcion);\
    return opcion;
}

int menu_Ventas (){
    int opcion;
    printf ("\n");
    printf ("**********************************************\n");
    printf ("*               Ventas                       *");
    printf ("\n*                                            *");
    printf ("\n*        6. Vender producto                  *");
    printf ("\n*        7. Entrada de Productos             *");
    printf ("\n*        8. Buscar Precio                    *");
    printf ("\n*        0. Salir                            *");
    printf ("\n**********************************************");
    printf ("\n");
    printf ("\nElige la opcion numero: ");
    scanf ("%i",&opcion);\
    return opcion;
}

int main() {
    int op, id, op_2;
    
    do{
        op=menu_Ppal();
        switch (op) {
            case 1:
                //Ventas
                do{
                    op_2=menu_Ventas();
                    switch (op_2) {
                        case 6:
                            //Venta de productos
                            printf("Introduce el codigo del producto a vender\n");
                            scanf("%d", &id);
                            salidasProducto(id);
                            break;
                            
                        case 7:
                            //Entrada de productos
                            printf("Introduce el codigo del producto que entra\n");
                            scanf("%d", &id);
                            entradasProducto(id);
                            break;
                            
                        case 8:
                            //Busqueda de precios
                            printf("Introduce el codigo del producto para buscar\n");
                            scanf("%d", &id);
                            buscar(id);
                            break;
                            
                        default:
                            printf ("**********************************************\n");
                            printf ("*        Opcion Invalida Favor de            *");
                            printf ("\n*        selecionar una opcion valida        *");
                            printf ("\n**********************************************");
                            printf ("\n");
                            break;
                    }
                }while (op_2!=0);
                break;
                
            case 2:
                //Registro
                printf("Introduce el codigo del producto para regisrar\n");
                scanf("%d", &id);
                insertar(id);
                break;
                
            case 3:
                //Eliminar
                printf("Introduce el codigo del producto para eliminar\n");
                scanf("%d", &id);
                eliminar(id);
                break;
                
            default:
                printf ("**********************************************\n");
                printf ("*        Opcion Invalida Favor de            *");
                printf ("\n*        selecionar una opcion valida        *");
                printf ("\n**********************************************");
                printf ("\n");
                break;
        }
        
        
    }while (op!=4);
    
    
    printf("Fin del programa\n");
    return 0;
}