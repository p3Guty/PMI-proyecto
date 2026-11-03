#ifndef LISTAVO_TURNO_H_INCLUDED
#define LISTAVO_TURNO_H_INCLUDED

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

int isOosListaVO(ListaVO_Turno l);

void initListaVO(ListaVO_Turno *l) {
    l->acc = NULL;
    l->cur = NULL;
    l->aux = NULL;
}

int isEmptyListaVO(ListaVO_Turno l) {
    return l.acc == NULL;
}

int isFullListaVO(ListaVO_Turno l) {
    Nodo *nodo_aux;
    (void)l;
    nodo_aux = (Nodo *)malloc(sizeof(Nodo));
    if (nodo_aux == NULL) {
        return 1;
    }
    free(nodo_aux);
    return 0;
}

void resetListaVO(ListaVO_Turno *l) {
    l->cur = l->acc;
    l->aux = NULL;
}


void forwardsListaVO(ListaVO_Turno *l) {
    if (isOosListaVO(*l)) {
        return;
    }
    l->aux = l->cur;
    l->cur = l->cur->next;
}

int isOosListaVO(ListaVO_Turno l) {
    return l.cur == NULL;
}

Turno copyListaVO(ListaVO_Turno l) {
    return l.cur->vipd;
}

int insertListaVO(ListaVO_Turno *l, Turno t) {

    if (isFullListaVO(*l) == 1) {
        return;
    }

    Nodo *nuevoNodo = (Nodo*)malloc(sizeof(Nodo));
    if (nuevoNodo == NULL) {
        exit(1);
    }
    nuevoNodo->vipd = t;

    if (l->cur == l->acc ) {
        l->acc = nuevoNodo;
        nuevoNodo->next = l->cur;
        l->cur = l->acc;
        l->aux = l->acc;
    }else {
        l->aux->next = nuevoNodo;
        nuevoNodo->next = l->cur;
        l->cur = nuevoNodo;
    }
}


int suppressListaVO(ListaVO_Turno *l) {
    Nodo *eliminado;
    eliminado = l->cur;
    if (l->aux == NULL) {
        l->acc = eliminado->next;
    } else {
        l->aux->next = eliminado->next;
    }
    l->cur = eliminado->next;
    free(eliminado);
    return 1;
}

void liberarListaVO(ListaVO_Turno *l) {
    Nodo *actual;
    Nodo *siguiente;
    actual = l->acc;
    while (actual != NULL) {
        siguiente = actual->next;
        free(actual);
        actual = siguiente;
    }
    initListaVO(l);
}

#endif // LISTAVO_TURNO_H_INCLUDED
