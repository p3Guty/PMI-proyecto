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

/* -------------------------------------------------------------------------
 * ESTRUCTURA DEL TDA LISTA VINCULADA ORDENADA
 * acc: Puntero de Acceso al primer nodo de la lista.
 * cur: Cursor activo de trabajo.
 * aux: Puntero auxiliar al nodo inmediatamente anterior a cur.
 * ------------------------------------------------------------------------- */
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
int copyListaVO(ListaVO_Turno l, Turno *destino);
int insertListaVO(ListaVO_Turno *l, Turno elem);
int suppressListaVO(ListaVO_Turno *l);

int buscarTurnoPorId(ListaVO_Turno *l, int id_buscado);
int cancelarTurnoEnLista(ListaVO_Turno *l, int id_buscado);
int confirmarTurnoEnLista(ListaVO_Turno *l, int id_buscado);

int contarTurnosAtendidosRecursivaNodo(Nodo *n, int dia, int mes);
int contarTurnosAtendidosRecursiva(ListaVO_Turno l, int dia, int mes);
int contarTurnosAsignadosMesRecursivaNodo(Nodo *n, int mes_buscado);
int contarTurnosAsignadosMesRecursiva(ListaVO_Turno l, int mes_buscado);
float calcularMontoMes(ListaVO_Turno l, int mes);

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
    return 0;
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
    if (l->cur != NULL) {
        l->aux = l->cur;
        l->cur = l->cur->next;
    }
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
int copyListaVO(ListaVO_Turno l, Turno *destino) {
    if (isOosListaVO(l) == 1) {
        return 0;
    }
    *destino = l.cur->vipd;
    return 1;
}

/*
 * Funcion: insertListaVO
 * Propósito: Inserta un nuevo Turno manteniendo la lista vinculada
 *            estrictamente ordenada por fecha de menor a mayor.
 * Retorno: 1 si pudo asignar memoria e insertar, 0 si fallo malloc.
 */
int insertListaVO(ListaVO_Turno *l, Turno elem) {
    Nodo *nuevo;
    Nodo *ant;
    Nodo *act;

    /* Peticion de espacio en la memoria dinamica heap */
    nuevo = (Nodo *)malloc(sizeof(Nodo));
    if (nuevo == NULL) {
        return 0; /* Fallo por falta de memoria RAM */
    }
    nuevo->vipd = elem;

    ant = NULL;
    act = l->acc;

    /* Bucle de busqueda de la posicion cronologica correcta de menor a mayor */
    while (act != NULL && compararFechasTurno(obtener_fechaTurno(act->vipd), obtener_fechaTurno(elem)) < 0) {
        ant = act;
        act = act->next;
    }

    /* Caso 1: Insercion al principio de la lista */
    if (ant == NULL) {
        nuevo->next = l->acc;
        l->acc = nuevo;
        l->cur = nuevo;
        l->aux = NULL;
    }
    /* Caso 2: Insercion entre dos nodos o al final */
    else {
        nuevo->next = act;
        ant->next = nuevo;
        l->cur = nuevo;
        l->aux = ant;
    }

    return 1;
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
}

/*
 * Funcion: buscarTurnoPorId
 * Propósito: Recorre la lista buscando la coincidencia del id_turno.
 * Retorno: 1 si lo encuentra (cur queda parado en la coincidencia), 0 si no existe.
 */
int buscarTurnoPorId(ListaVO_Turno *l, int id_buscado) {
    Turno temp;
    resetListaVO(l);

    while (isOosListaVO(*l) == 0) {
        copyListaVO(*l, &temp);
        if (obtener_idTurno(temp) == id_buscado) {
            return 1; /* Coincidencia hallada */
        }
        forwardsListaVO(l);
    }
    return 0; /* No encontrado */
}

/*
 * Funcion: cancelarTurnoEnLista
 * Propósito: Modifica el estado del turno encontrado a ESTADO_CANCELADO (4).
 */
int cancelarTurnoEnLista(ListaVO_Turno *l, int id_buscado) {
    Turno temp;

    if (buscarTurnoPorId(l, id_buscado) == 1) {
        copyListaVO(*l, &temp);
        modificar_estadoTurno(&temp, ESTADO_CANCELADO);
        l->cur->vipd = temp;
        return 1;
    }
    return 0;
}

/*
 * Funcion: confirmarTurnoEnLista
 * Propósito: Modifica el estado del turno encontrado a ESTADO_CONFIRMADO (2).
 */
int confirmarTurnoEnLista(ListaVO_Turno *l, int id_buscado) {
    Turno temp;

    if (buscarTurnoPorId(l, id_buscado) == 1) {
        copyListaVO(*l, &temp);
        modificar_estadoTurno(&temp, ESTADO_CONFIRMADO);
        l->cur->vipd = temp;
        return 1;
    }
    return 0;
}

/* -------------------------------------------------------------------------
 * FUNCIONES RECURSIVAS EXIGIDAS POR EL PMI 2026
 * ------------------------------------------------------------------------- */

/*
 * Funcion: contarTurnosAtendidosRecursivaNodo (Consigna m)
 * Propósito: Contar los turnos atendidos para un dia y mes pasados por parametro.
 * Metodo: Recursion lineal pura sobre los nodos de la lista.
 */
int contarTurnosAtendidosRecursivaNodo(Nodo *n, int dia, int mes) {
    Turno t;
    Fecha f;
    int est;
    int suma;

    /* Caso Base: Alcanzo el final de la lista vinculada */
    if (n == NULL) {
        return 0;
    }

    t = n->vipd;
    f = obtener_fechaTurno(t);
    est = obtener_estadoTurno(t);
    suma = 0;

    /* Evaluacion del nodo corriente */
    if (f.dia == dia && f.mes == mes && est == ESTADO_ATENDIDO) {
        suma = 1;
    }

    /* Paso Recursivo: Suma resultado local + llamada con el siguiente nodo (n->next) */
    return suma + contarTurnosAtendidosRecursivaNodo(n->next, dia, mes);
}

/* Funcion envoltorio (wrapper) de la Consigna m */
int contarTurnosAtendidosRecursiva(ListaVO_Turno l, int dia, int mes) {
    return contarTurnosAtendidosRecursivaNodo(l.acc, dia, mes);
}

/*
 * Funcion: contarTurnosAsignadosMesRecursivaNodo (Consigna l)
 * Propósito: Contar los turnos asignados (solicitado o confirmado) de un mes.
 * Metodo: Recursion lineal pura sobre los nodos.
 */
int contarTurnosAsignadosMesRecursivaNodo(Nodo *n, int mes_buscado) {
    Turno t;
    Fecha f;
    int est;
    int suma;

    /* Caso Base */
    if (n == NULL) {
        return 0;
    }

    t = n->vipd;
    f = obtener_fechaTurno(t);
    est = obtener_estadoTurno(t);
    suma = 0;

    if (f.mes == mes_buscado) {
        if (est == ESTADO_SOLICITADO || est == ESTADO_CONFIRMADO) {
            suma = 1;
        }
    }

    /* Paso Recursivo */
    return suma + contarTurnosAsignadosMesRecursivaNodo(n->next, mes_buscado);
}

/* Funcion envoltorio (wrapper) de la Consigna l */
int contarTurnosAsignadosMesRecursiva(ListaVO_Turno l, int mes_buscado) {
    return contarTurnosAsignadosMesRecursivaNodo(l.acc, mes_buscado);
}

/*
 * Funcion: calcularMontoMes (Consigna r)
 * Propósito: Calcula el acumulado total de dinero por consultas atendidas en un mes.
 */
float calcularMontoMes(ListaVO_Turno l, int mes) {
    Turno t;
    Fecha f;
    float total;

    total = 0.0f;
    resetListaVO(&l);

    while (isOosListaVO(l) == 0) {
        copyListaVO(l, &t);
        f = obtener_fechaTurno(t);
        if (f.mes == mes && obtener_estadoTurno(t) == ESTADO_ATENDIDO) {
            total = total + obtener_monto(t);
        }
        forwardsListaVO(&l);
    }

    return total;


#endif // LISTAVO_TURNO_H_INCLUDED
