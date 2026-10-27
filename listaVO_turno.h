#ifndef LISTAVO_TURNO_H_INCLUDED
#define LISTAVO_TURNO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "turno.h"

/* --------------------------------------------------------------------------
 * ESTRUCTURA DE NODO AUTORREFERENCIADO
 * VIPD (Variable de Informacion Propiamente Dicha): Guarda el Turno.
 * next: Puntero al siguiente nodo en la memoria RAM (o NULL si es el ultimo).
 * -------------------------------------------------------------------------- */
struct nodo {
    Turno vipd;
    struct nodo *next;
};
typedef struct nodo Nodo;

/* --------------------------------------------------------------------------
 * ESTRUCTURA DEL TDA LISTA VINCULADA ORDENADA
 * acc: Puntero de Acceso al primer nodo de la lista.
 * cur: Cursor activo de trabajo.
 * aux: Puntero auxiliar al nodo inmediatamente anterior a cur.
 * -------------------------------------------------------------------------- */
typedef struct {
    Nodo *acc;
    Nodo *cur;
    Nodo *aux;
} ListaVO_Turno;

/* PROTOTIPOS DE PRIMITIVAS Y FUNCIONES DE NEGOCIO */
void initListaVO(ListaVO_Turno *l);
int isEmptyListaVO(ListaVO_Turno l);
int isFullListaVO(ListaVO_Turno l);
void resetListaVO(ListaVO_Turno *l);
void forwardsListaVO(ListaVO_Turno *l);
int isOosListaVO(ListaVO_Turno l);
int copyListaVO(ListaVO_Turno l,);
int insertListaVO(ListaVO_Turno *l, Turno elem);
int suppressListaVO(ListaVO_Turno *l);

/* =========================================================================
 * IMPLEMENTACION DE LAS FUNCIONES PRIMITIVAS
 * ========================================================================= */

/*
 * Funcion: initListaVO
 * Propósito: Inicializa la lista vinculada dejando todos los punteros en NULL.
 */
void initListaVO(ListaVO_Turno *l) {
    l->acc = NULL;
    l->cur = NULL;
    l->aux = NULL;
}

/*
 * Funcion: isEmptyListaVO
 * Propósito: Comprueba si la lista esta vacia.
 * Retorno: 1 si acc es NULL (vacia), 0 si contiene nodos.
 */
int isEmptyListaVO(ListaVO_Turno l) {
    if (l.acc == NULL) {
        return 1;
    } else {
        return 0;
    }
}

/*
 * Funcion: isFullListaVO
 * Propósito: Comprueba si la lista esta llena.
 * Retorno: En memoria dinamica siempre retorna 0 (solo se llena si falta RAM).
 */
int isFullListaVO(ListaVO_Turno l) {
    Nodo *nodo_aux = (Nodo *) malloc( sizeof(Nodo) );
    if( nodo_aux == NULL ) return 1;
    else{
        free( nodo_aux );
        return 0;
    }
}

/*
 * Funcion: resetListaVO
 * Propósito: Posiciona el cursor en el primer nodo de la lista.
 */
void resetListaVO(ListaVO_Turno *l) {
    l->cur = l->acc;
    l->aux = NULL;
}

/*
 * Funcion: forwardsListaVO
 * Propósito: Avanza el cursor un nodo hacia adelante en la secuencia.
 */
void forwardsListaVO(ListaVO_Turno *l) {
    l->aux = l->cur;
    l->cur = l->cur->next;
}

/*
 * Funcion: isOosListaVO (Is Out of Structure)
 * Propósito: Determina si el cursor sobrepaso el final de la lista.
 * Retorno: 1 si cur es NULL (fuera de estructura), 0 en caso contrario.
 */
int isOosListaVO(ListaVO_Turno l) {
    if (l.cur == NULL) {
        return 1;
    } else {
        return 0;
    }
}

/*
 * Funcion: copyListaVO
 * Propósito: Copia el Turno actual sobre la variable *destino sin desapilar.
 * Retorno: 1 si tuvo exito, 0 si la lista estaba vacia o cur fuera de estructura.
 */
int copyListaVO(ListaVO_Turno l,) {
    return l->cur->vipd;
}

/*
 * Funcion: insertListaVO
 * Propósito: Inserta un nuevo Turno manteniendo la lista vinculada
 *            estrictamente ordenada por fecha de menor a mayor.
 * Retorno: 1 si pudo asignar memoria e insertar, 0 si fallo malloc.
 */

void insertListaVO ( ListaVO_Turno *l, Turno t ){
    Nodo *nuevo = (Nodo*) malloc(sizeof(Nodo));

    if( l->cur == l->acc ){
        l->acc = nuevo;
        nuevo->next = l->cur;
        l->cur = nuevo;
        l->aux = nuevo; 
    } else {
        l->aux->next = nuevo;
        nuevo->next = l->cur;
        l->cur = nuevo;
    }
    l->cur->vipd = t;
}

/*
 * Funcion: suppressListaVO
 * Propósito: Elimina el nodo apuntado por cur y entrega la memoria con free.
 * Retorno: 1 si elimino con exito, 0 si no habia elemento que suprimir.
 */
int suppressListaVO(ListaVO_Turno *l) {
    Nodo *elim;

    if (isOosListaVO(*l) == 1 || isEmptyListaVO(*l) == 1) {
        return 0;
    }

    elim = l->cur;

    /* Caso 1: Eliminacion del primer nodo */
    if (l->aux == NULL) {
        l->acc = l->cur->next;
        l->cur = l->acc;
    }
    /* Caso 2: Eliminacion en el medio o al final */
    else {
        l->aux->next = l->cur->next;
        l->cur = l->cur->next;
    }

    free(elim); /* Liberacion de memoria devuelta al sistema operativo */
    return 1;
}   //corregir lo mismo que insert

#endif // LISTAVO_TURNO_H_INCLUDED
