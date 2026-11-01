#ifndef LISTAVO_TURNO_H_INCLUDED
#define LISTAVO_TURNO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "turno.h"

struct nodo {
    Turno vipd;
    struct nodo *next;
};
typedef struct nodo Nodo;

typedef struct {
    Nodo *acc;
    Nodo *cur;
    Nodo *aux;
} ListaVO_Turno;


void initListaVO(ListaVO_Turno *l);
int isEmptyListaVO(ListaVO_Turno l);
int isFullListaVO(ListaVO_Turno l);
void resetListaVO(ListaVO_Turno *l);
void forwardsListaVO(ListaVO_Turno *l);
int isOosListaVO(ListaVO_Turno l);
Turno copyListaVO(ListaVO_Turno l);
int insertListaVO(ListaVO_Turno *l, Turno elem);
int suppressListaVO(ListaVO_Turno *l);

void initListaVO(ListaVO_Turno *l) {
    l->acc = NULL;
    l->cur = NULL;
    l->aux = NULL;
}

int isEmptyListaVO(ListaVO_Turno l) {
    if (l.acc == NULL) {
        return 1;
    } else {
        return 0;
    }
}

int isFullListaVO(ListaVO_Turno l) {
    Nodo *nodo_aux = (Nodo *) malloc( sizeof(Nodo) );
    if( nodo_aux == NULL ) return 1;
    else{
        free( nodo_aux );
        return 0;
    }
}

void resetListaVO(ListaVO_Turno *l) {
    l->cur = l->acc;
    l->aux = NULL;
}

void forwardsListaVO(ListaVO_Turno *l) {
    l->aux = l->cur;
    l->cur = l->cur->next;
}

int isOosListaVO(ListaVO_Turno l) {
    if (l.cur == NULL) {
        return 1;
    } else {
        return 0;
    }
}

Turno copyListaVO(ListaVO_Turno l) {
    return l.cur->vipd;
}

int insertListaVO ( ListaVO_Turno *l, Turno t ){
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
    return 1;
}

int suppressListaVO(ListaVO_Turno *l) {
    if ( l->acc == l->cur ){
        l->acc = l->acc->next;
        free( l->cur );
        l->cur = l->acc;
        l->aux = NULL;
    } else {
        l->aux->next = l->cur->next;
        free( l->cur );
        l->cur = l->aux->next;
    }
    return 1;
}

#endif // LISTAVO_TURNO_H_INCLUDED
