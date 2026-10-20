#ifndef TURNO_H_INCLUDED
#define TURNO_H_INCLUDED

/* Inclusion de la libreria auxiliar de Fecha */
#include "pacientes.h"
#include "fecha.h"
#include "agenda.h"

/* Inclusión de librerias estandar para manejo de cadenas y memoria */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Capacidad maxima para el nombre de la obra social / mutual */
#define MAX_MUTUAL 50

/* Codigos numericos para representar los 4 estados posibles de un turno */
#define ESTADO_SOLICITADO 1  /* Turno reservado por el paciente */
#define ESTADO_CONFIRMADO 2  /* Paciente presente en el consultorio */
#define ESTADO_ATENDIDO   3  /* Paciente atendido por el medico */
#define ESTADO_CANCELADO  4  /* Turno anulado */

/* -------------------------------------------------------------------------
 * ESTRUCTURA DE DATOS: Turno
 * Agrupa todos los campos requeridos por la consigna del PMI 2026.
 * ------------------------------------------------------------------------- */
typedef struct {
    int id_turno;            /* Codigo unico coincidente con el indice de la agenda */
    long dni_paciente;       /* DNI del paciente asignado al turno */
    float monto;             /* Dinero abonado si no posee obra social */
    char mutual[MAX_MUTUAL]; /* Nombre de la mutual u obra social */
    Fecha fecha;             /* Estructura de tipo Fecha (dia, mes, anio, hora, min) */
    int estado;              /* Estado actual (1=Solicitado, 2=Confirmado, 3=Atendido, 4=Cancelado) */
} Turno;

/* PROTOTIPOS DE LAS FUNCIONES PRIMITIVAS DEL TDA TURNO */
void initTurno(Turno *t);
Turno crearTurno(int id, long dni, float monto, const char *mutual, Fecha f, int estado);

void modificar_idTurno(Turno *t, int id);
void modificar_dniPaciente(Turno *t, long dni);
void modificar_monto(Turno *t, float monto);
void modificar_mutual(Turno *t, const char *mutual);
void modificar_fechaTurno(Turno *t, Fecha f);
void modificar_estadoTurno(Turno *t, int estado);

int obtener_idTurno(Turno t);
long obtener_dniPaciente(Turno t);
float obtener_monto(Turno t);
void obtener_mutual(Turno t, char *destino);
Fecha obtener_fechaTurno(Turno t);
int obtener_estadoTurno(Turno t);

int compararFechasTurno(Fecha f1, Fecha f2);

/* =========================================================================
 * IMPLEMENTACION DE LAS FUNCIONES PRIMITIVAS
 * ========================================================================= */

/*
 * Funcion: initTurno
 * Propósito: Limpia la memoria asignando valores neutros e iniciales por defecto.
 * Parametros: t (puntero al Turno a inicializar)
 */
void initTurno(Turno *t) {
    t->id_turno = -1;
    t->dni_paciente = 0;
    t->monto = 0.0f;
    strcpy(t->mutual, "Sin Mutual");
    t->estado = ESTADO_SOLICITADO;
}

/*
 * Funcion: crearTurno
 * Propósito: Construye y retorna un objeto Turno validando los rangos permitidos.
 * Parametros: id, dni, monto, mutual, f (fecha), estado.
 * Retorno: Estructura Turno cargada.
 */
Turno crearTurno(int id, long dni, float monto, const char *mutual, Fecha f, int estado) {
    Turno t;
    t.id_turno = id;
    t.dni_paciente = dni;

    /* Validacion de monto no negativo */
    if (monto >= 0.0f) {
        t.monto = monto;
    } else {
        t.monto = 0.0f;
    }

    /* Validacion de cadena de mutual */
    if (mutual != NULL) {
        strcpy(t.mutual, mutual);
    } else {
        strcpy(t.mutual, "Sin Mutual");
    }

    t.fecha = f;

    /* Validacion de estado entre 1 y 4 */
    if (estado >= 1 && estado <= 4) {
        t.estado = estado;
    } else {
        t.estado = ESTADO_SOLICITADO;
    }

    return t;
}

/* MODIFICADORES (SETTERS) */

void modificar_idTurno(Turno *t, int id) {
    t->id_turno = id;
}

void modificar_dniPaciente(Turno *t, long dni) {
    if (dni > 0) {
        t->dni_paciente = dni;
    }
}

void modificar_monto(Turno *t, float monto) {
    if (monto >= 0.0f) {
        t->monto = monto;
    }
}

void modificar_mutual(Turno *t, const char *mutual) {
    if (mutual != NULL) {
        strcpy(t->mutual, mutual);
    }
}

void modificar_fechaTurno(Turno *t, Fecha f) {
    t->fecha = f;
}

void modificar_estadoTurno(Turno *t, int estado) {
    if (estado >= 1 && estado <= 4) {
        t->estado = estado;
    }
}

/* CONSULTORES (GETTERS) */

int obtener_idTurno(Turno t) {
    return t.id_turno;
}

long obtener_dniPaciente(Turno t) {
    return t.dni_paciente;
}

float obtener_monto(Turno t) {
    return t.monto;
}

void obtener_mutual(Turno t, char *destino) {
    if (destino != NULL) {
        strcpy(destino, t.mutual);
    }
}

Fecha obtener_fechaTurno(Turno t) {
    return t.fecha;
}

int obtener_estadoTurno(Turno t) {
    return t.estado;
}

/*
 * Funcion: compararFechasTurno
 * Propósito: Compara dos variables de tipo Fecha en orden cronologico.
 * Retorno:
 *   -1 si f1 es estrictamente anterior en el tiempo a f2.
 *    1 si f1 es estrictamente posterior en el tiempo a f2.
 *    0 si ambas fechas corresponden exactamente al mismo instante.
 */
int compararFechasTurno(Fecha f1, Fecha f2) {
    if (f1.anio != f2.anio) {
        if (f1.anio < f2.anio) {
            return -1;
        } else {
            return 1;
        }
    }
    if (f1.mes != f2.mes) {
        if (f1.mes < f2.mes) {
            return -1;
        } else {
            return 1;
        }
    }
    if (f1.dia != f2.dia) {
        if (f1.dia < f2.dia) {
            return -1;
        } else {
            return 1;
        }
    }
    if (f1.hora != f2.hora) {
        if (f1.hora < f2.hora) {
            return -1;
        } else {
            return 1;
        }
    }
    if (f1.minuto != f2.minuto) {
        if (f1.minuto < f2.minuto) {
            return -1;
        } else {
            return 1;
        }
    }
    return 0;
}

#endif // TURNO_H_INCLUDED
