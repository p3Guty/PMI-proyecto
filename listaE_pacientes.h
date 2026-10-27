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
} ListaEPaciente;

/* PROTOTIPOS DE LAS PRIMITIVAS */
void initListaE(ListaEPaciente *l);
int isEmptyListaE(ListaEPaciente l);
int isFullListaE(ListaEPaciente l);
void resetListaE(ListaEPaciente *l);
void forwardsListaE(ListaEPaciente *l);
int isOosListaE(ListaEPaciente l);
int copyListaE(ListaEPaciente l, Paciente *destino);
int insertListaE(ListaEPaciente *l, Paciente elem);
int suppressListaE(ListaEPaciente *l);

int buscarPacientePorDni(ListaEPaciente *l, long dni_buscado);
int existePaciente(ListaEPaciente l, long dni_buscado);

/* =========================================================================
 * IMPLEMENTACION DE LAS FUNCIONES PRIMITIVAS DE LA LISTA
 * ========================================================================= */

void initListaE(ListaEPaciente *l) {
    l->cant = 0;
    l->cur = -1;
}

int isEmptyListaE(ListaEPaciente l) {
    if (l.cant == 0) {
        return 1;
    } else {
        return 0;
    }
}

int isFullListaE(ListaEPaciente l) {
    if (l.cant == MAX_PACIENTES) {
        return 1;
    } else {
        return 0;
    }
}

void resetListaE(ListaEPaciente *l) {
    if (l->cant > 0) {
        l->cur = 0;
    } else {
        l->cur = -1;
    }
}

void forwardsListaE(ListaEPaciente *l) {
    if (l->cur >= 0 && l->cur < l->cant) {
        l->cur++;
    }
}

int isOosListaE(ListaEPaciente l) {
    if (l->cur < 0 || l->cur >= l->cant) {
        return 1;
    } else {
        return 0;
    }
}

int copyListaE(ListaEPaciente l, Paciente *destino) {
    if (isOosListaE(l) == 1) {
        return 0;
    }
    *destino = l.elementos[l.cur];
    return 1;
}

int insertListaE(ListaEPaciente *l, Paciente elem) {
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

int suppressListaE(ListaEPaciente *l) {
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

/*
 * Funcion: buscarPacientePorDni
 * Propósito: Recorre la lista buscando un paciente por su DNI.
 * Retorno: 1 si lo encuentra (cur queda parado en el elemento), 0 si no existe.
 */
int buscarPacientePorDni(ListaEPaciente *l, long dni_buscado) {
    Paciente temp;
    resetListaE(l);

    while (isOosListaE(*l) == 0) {
        copyListaE(*l, &temp);
        if (obtener_dniPaciente(temp) == dni_buscado) {
            return 1; /* Paciente hallado */
        }
        forwardsListaE(l);
    }
    return 0; /* No encontrado */
}

/* Funcion de consulta para saber si un DNI ya esta registrado */
int existePaciente(ListaEPaciente l, long dni_buscado) {
    return buscarPacientePorDni(&l, dni_buscado);
}

#endif // LISTAE_PACIENTES_H_INCLUDE