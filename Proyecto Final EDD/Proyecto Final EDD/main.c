//
//  main.c
//  Proyecto Final EDD
//
//  Created by Víctor David Rivera Ramírez on 23/04/15.
//  Copyright (c) 2015 Víctor David Rivera Ramírez. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#define SIZE 30

int tabla_hash[SIZE] = {0};


int hash(int clave){
    //esta parte es modular
    
    
    return clave % SIZE;
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
            return 1;
        }else{
            printf("Espacio agotado\n");
            return 0;
        }
    }else{
        tabla_hash[indice] = clave;
        return 1;
    }
}


int buscar (int clave){
    int indice;
    
    indice = hash(clave);
    
    if (tabla_hash[indice] == clave) {
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
    printf ("\n*        1. Ventas                           *");
    printf ("\n*        2. Entrada de Productos             *");
    printf ("\n*        3. Buscar Precio                    *");
    printf ("\n*        4. Salir                            *");
    printf ("\n**********************************************");
    printf ("\n");
    printf ("\nElige la opcion numero: ");
    scanf ("%i",&opcion);\
    return opcion;
}

int main() {
    int op, id;
    /*
    do{
        printf("Que desea hacer: \n1)Agregar un producto nuevo\n2)Buscar precio de un producto\n3)Eliminar un producto existente\n4)Salir\n");
        scanf("%d", &op);
        
        switch (op) {
            case 1:
                printf("Introduce el codigo del producto a insertar\n");
                scanf("%d", &id);
                insertar(id);
                break;
                
            case 2:
                printf("Introduce el codigo del producto para buscar\n");
                scanf("%d", &id);
                buscar(id);
                break;
                
            case 3:
                printf("Introduce el codigo del producto para eliminar\n");
                scanf("%d", &id);
                eliminar(id);
                break;
                
            default:
                break;
        }
        
    }while (op != 4);
     
     */
    
    do{
        op=menu_Ppal();
        switch (op) {
            case 1:
                //Ventas
                op=menu_Ventas();
                switch (op) {
                    case 1:
                        //Venta de productos
                        printf("Introduce el codigo del producto a vender\n");
                        scanf("%d", &id);
                        // aqui va la funcion de venta(id);
                        break;
                        
                    case 2:
                        //Entrada de productos
                        printf("Introduce el codigo del producto que entra\n");
                        scanf("%d", &id);
                        //aqui va a funcion de entrada(id);
                        break;
                        
                    case 3:
                        //Busqueda de precios
                        printf("Introduce el codigo del producto para buscar\n");
                        scanf("%d", &id);
                        buscar(id);//aqui va la funcion de buscar(id);
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case 2:
                //Registro
                printf("Introduce el codigo del producto para buscar\n");
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
                break;
        }
        
        
    }while (op!=4);
    
    
    
    printf("Fin del programa\n");
    return 0;
}