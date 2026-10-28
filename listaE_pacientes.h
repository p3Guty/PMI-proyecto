/* =========================================================================
 * ARCHIVO: listaE_Paciente.h
 * COMPONENTE: TDA Lista Estatica Desordenada de Pacientes (Persona 1 - PMI 2026)
 * DESCRIPCION: Implementa el almacenamiento estatico de pacientes mediante
 *              cursor e incluye la busqueda por DNI.
 * ========================================================================= */

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
int insertListaE(ListaE_Paciente *l, Paciente elem);
int suppressListaE(ListaE_Paciente *l);

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
    if (l->cur >= 0 && l->cur < l->cant) {
        l->cur++;
    }
}

int isOosListaE(ListaE_Paciente l) {
    if (l.cur < 0 || l.cur >= l.cant) {
        return 1;
    } else {
        return 0;
    }
}

int copyListaE(ListaE_Paciente l, Paciente *destino) {
    if (isOosListaE(l) == 1) {
        return 0;
    }
    *destino = l.elementos[l.cur];
    return 1;
}

int insertListaE(ListaE_Paciente *l, Paciente elem) {
    int i;
    int pos_insert;

    if (isFullListaE(*l) == 1) {
        return 0; /* Fallo: Lista llena */
    }

    if (isOosListaE(*l) == 1) {
        pos_insert = l->cant;
    } else {
        pos_insert = l->cur;
    }

    /* Desplazamiento a la derecha */
    for (i = l->cant; i > pos_insert; i--) {
        l->elementos[i] = l->elementos[i - 1];
    }

    l->elementos[pos_insert] = elem;
    l->cant++;
    l->cur = pos_insert;
    return 1;
}

int suppressListaE(ListaE_Paciente *l) {
    int i;
    int pos_suppress;

    if (isOosListaE(*l) == 1 || isEmptyListaE(*l) == 1) {
        return 0;
    }

    pos_suppress = l->cur;

    /* Desplazamiento a la izquierda */
    for (i = pos_suppress; i < l->cant - 1; i++) {
        l->elementos[i] = l->elementos[i + 1];
    }

    l->cant--;

    if (l->cant == 0) {
        l->cur = -1;
    } else if (l->cur >= l->cant) {
        l->cur = l->cant - 1;
    }

    return 1;
}

#endif // LISTAE_PACIENTES_H_INCLUDE