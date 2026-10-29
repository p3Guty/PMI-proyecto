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
Paciente copyListaE(ListaE_Paciente l);
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
    //if (l->cur >= 0 && l->cur < l->cant) {  //control que hay que hacer en el main
        l->cur++;
    //}
}

int isOosListaE(ListaE_Paciente l) {
    if (l.cur < 0 || l.cur >= l.cant) {
        return 1;
    } else {
        return 0;
    }
}

Paciente copyListaE(ListaE_Paciente l) {
    /*if (isOosListaE(l) == 1) {
        return 0;
    }*/                     //poner en el main.c
    //*destino = l.elementos[l.cur];
    //return 1;
    return l.elementos[l.cur];
}

void insertListaE(ListaE_Paciente *l, Paciente elem) {
    int i;
    int pos_insert; //no hace falta esto 

    /* if (isFullListaE(*l) == 1) {
        return 0;  Fallo: Lista llena 
    }
                                
    if (isOosListaE(*l) == 1) {
        pos_insert = l->cant;
    } else {
        pos_insert = l->cur;
    }
    */

    /* Desplazamiento a la derecha */ //forma correcta por el profe
    if( isEmptyListaE( *l ) ) l->cur++;
    else {
        for (i = l->cant; i > l->cur ; i--) {
            l->elementos[i] = l->elementos[i - 1];
        }
    }
    l->elementos[ l->cur++] = elem;
    l->cant++;
    //l->cur = pos_insert;
}

void suppressListaE(ListaE_Paciente *l) {
    int i;
    //int pos_suppress;

    /*if (isOosListaE(*l) == 1 || isEmptyListaE(*l) == 1) {
        return 0;
    }*/                             //forma incorrecta

    //pos_suppress = l->cur;

    /* Desplazamiento a la izquierda */  //esto esta bien 
    for (i = l->cur; i < l->cant - 1; i++) {
        l->elementos[i] = l->elementos[i + 1];
    }

    l->cant--;
    /*
    if (l->cant == 0) {
        l->cur = -1;
    } else if (l->cur >= l->cant) {             //demas todo esto
        l->cur = l->cant - 1;
    }*/

}

#endif // LISTAE_PACIENTES_H_INCLUDE