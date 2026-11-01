//cspell:disable

#ifndef LISTAE_PACIENTES_H_INCLUDE
#define LISTAE_PACIENTES_H_INCLUDE

#include <stdio.h>
#include <stdlib.h>
#include "pacientes.h"

#define MAX_PACIENTES 200

/* -------------------------------------------------------------------------
 * ESTRUCTURA DE LA LISTA ESTATICA DESORDENADA DE PACIENTES
 * ------------------------------------------------------------------------- */
typedef struct {
    Paciente elementos[MAX_PACIENTES];
    int cant; /* Cantidad de pacientes guardados actualmente */
    int cur;  /* Indice del cursor activo (-1 si isOos) */
} ListaE_Paciente;

/* PROTOTIPOS DE LAS PRIMITIVAS */
void initListaE(ListaE_Paciente *l);
int isEmptyListaE(ListaE_Paciente l);
int isFullListaE(ListaE_Paciente l);
void resetListaE(ListaE_Paciente *l);
void forwardsListaE(ListaE_Paciente *l);
int isOosListaE(ListaE_Paciente l);
int copyListaE(ListaE_Paciente l, Paciente *destino);
void insertListaE(ListaE_Paciente *l, Paciente elem);
void suppressListaE(ListaE_Paciente *l);

/* =========================================================================
 * IMPLEMENTACION DE LAS FUNCIONES PRIMITIVAS DE LA LISTA
 * ========================================================================= */

void initListaE(ListaE_Paciente *l) {
    l->cant = 0;
    l->cur = -1;
}

int isEmptyListaE(ListaE_Paciente l) {
    if (l.cant == 0) {
        return 1;
    } else {
        return 0;
    }
}

int isFullListaE(ListaE_Paciente l) {
    if (l.cant == MAX_PACIENTES) {
        return 1;
    } else {
        return 0;
    }
}

void resetListaE(ListaE_Paciente *l) {
    if (l->cant > 0) {
        l->cur = 0;
    } else {
        l->cur = -1;
    }
}

void forwardsListaE(ListaE_Paciente *l) {
    l->cur++;
}

int isOosListaE(ListaE_Paciente l) {
    if (l.cur < 0 || l.cur >= l.cant) {
        return 1;
    } else {
        return 0;
    }
}

int copyListaE(ListaE_Paciente l, Paciente *destino) {
    if (destino == NULL || l.cur < 0 || l.cur >= l.cant) {
        return 0;
    }
    *destino = l.elementos[l.cur];
    return 1;
}

void insertListaE(ListaE_Paciente *l, Paciente elem) {
    int i;
    /* Desplazamiento a la derecha */
    if( isEmptyListaE( *l ) ) l->cur++;
    else {
        for (i = l->cant; i > l->cur ; i--) {
            l->elementos[i] = l->elementos[i - 1];
        }
    }
    l->elementos[ l->cur++] = elem;
    l->cant++;
}

void suppressListaE(ListaE_Paciente *l) {
    int i;
    //esto esta bien 
    for (i = l->cur; i < l->cant - 1; i++) {
        l->elementos[i] = l->elementos[i + 1];
    }
    l->cant--;
}

#endif // LISTAE_PACIENTES_H_INCLUDE