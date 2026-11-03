#ifndef TURNO_H_INCLUDED
#define TURNO_H_INCLUDED

/* Inclusion de la libreria auxiliar de Fecha */
#include "pacientes.h"
#include "fecha.h"

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

/* ---------------------------------------------------------------------
 * ESTRUCTURA DE DATOS: Turno
 * Agrupa todos los campos requeridos por la consigna del PMI 2026.
 * --------------------------------------------------------------------- */
typedef struct {
    int id_turno;            /* Codigo unico coincidente con el indice de la agenda */
    long dni_paciente;       /* DNI del paciente asignado al turno */
    float monto;             /* Dinero abonado si no posee obra social */
    char mutual[MAX_MUTUAL]; /* Nombre de la mutual u obra social */
    Fecha fecha;             /* Estructura de tipo Fecha (dia, mes, anio, hora, min) */
    int estado;              /* Estado actual (1=Solicitado, 2=Confirmado, 3=Atendido, 4=Cancelado) */
} Turno;


void initTurno(Turno *t) {
    t->id_turno = -1;
    t->dni_paciente = 0;
    t->monto = 0.0f;
    strcpy(t->mutual, "Sin Mutual");
    t->estado = ESTADO_SOLICITADO;
    inicio( &t->fecha );
}

Turno crearTurno(int id, long dni, float monto, const char *mutual, Fecha f, int estado) {
    Turno t;
    t.id_turno = id;
    t.dni_paciente = dni;
    t.monto = monto;
    strcpy(t.mutual, mutual);
    t.fecha = f;
    t.estado = estado;
    return t;
}

void modificar_idTurno(Turno *t, int id) {
    t->id_turno = id;
}

void modificar_dniPacienteTurno(Turno *t, long dni) {
    t->dni_paciente = dni;
}

void modificar_monto(Turno *t, float monto) {
t->monto = monto;
}


void modificar_mutual(Turno *t, const char *mutual) {
    strcpy(t->mutual, mutual);
}

void modificar_fechaTurno(Turno *t, Fecha f) {
    t->fecha = f;
}

void modificar_estadoTurno(Turno *t, int estado) {
    t->estado = estado;
}

/* CONSULTORES (GETTERS) */

int obtener_idTurno(Turno t) {
    return t.id_turno;
}

long obtener_dniPacienteTurno(Turno t) {
    return t.dni_paciente;
}

float obtener_monto(Turno t) {
    return t.monto;
}

int obtener_mutual(Turno t, char *destino) {
    strcpy(destino, t.mutual);
    return 1;
}

Fecha obtener_fechaTurno(Turno t) {
    return t.fecha;
}

int obtener_estadoTurno(Turno t) {
    return t.estado;
}

#endif // TURNO_H_INCLUDED
