/* =========================================================================
 * ARCHIVO: paciente.h
 * COMPONENTE: TDA Paciente (Persona 1 - PMI 2026)
 * DESCRIPCION: Define la estructura interna de un Paciente y sus operaciones
 *              primitivas de lectura y modificacion sin entrada/salida.
 * ========================================================================= */

#ifndef PACIENTES_H_INCLUDE
#define PACIENTES_H_INCLUDE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CADENA 50

/* -------------------------------------------------------------------------
 * ESTRUCTURA DE DATOS: Paciente
 * ------------------------------------------------------------------------- */
typedef struct {
    char nombre[MAX_CADENA];   /* Nombre del paciente */
    char apellido[MAX_CADENA]; /* Apellido del paciente */
    long dni;                  /* DNI unico del paciente */
    int osocial;               /* 1 si posee obra social, 0 si no posee */
} Paciente;

/* PROTOTIPOS DE LAS FUNCIONES PRIMITIVAS */
void initPaciente(Paciente *p);
Paciente crearPaciente(const char *nombre, const char *apellido, long dni, int osocial);

void modificar_nombrePaciente(Paciente *p, const char *nuevo_nombre);
void modificar_apellidoPaciente(Paciente *p, const char *nuevo_apellido);
void modificar_dniPaciente(Paciente *p, long nuevo_dni);
void modificar_osocialPaciente(Paciente *p, int nueva_osocial);

char* obtener_nombrePaciente(Paciente p);
char* obtener_apellidoPaciente(Paciente p);
long obtener_dniPaciente(Paciente p);
int obtener_osocialPaciente(Paciente p);

/* =========================================================================
 * IMPLEMENTACION DE LAS FUNCIONES PRIMITIVAS
 * ========================================================================= */

/* Inicializa la estructura con valores neutros por defecto */
void initPaciente(Paciente *p) {
    strcpy(p->nombre, "Sin Nombre");
    strcpy(p->apellido, "Sin Apellido");
    p->dni = 0;
    p->osocial = 0;
}

/* Construye y retorna una estructura Paciente validando los datos */
Paciente crearPaciente(const char *nombre, const char *apellido, long dni, int osocial) {
    Paciente p;

    if (nombre != NULL) {
        strcpy(p.nombre, nombre);
    } else {
        strcpy(p.nombre, "Sin Nombre");
    }

    if (apellido != NULL) {
        strcpy(p.apellido, apellido);
    } else {
        strcpy(p.apellido, "Sin Apellido");
    }

    if (dni > 0) {
        p.dni = dni;
    } else {
        p.dni = 0;
    }

    if (osocial == 1) {
        p.osocial = 1;
    } else {
        p.osocial = 0;
    }

    return p;
}

/* SETTERS (MODIFICADORES) */

void modificar_nombrePaciente(Paciente *p, const char *nuevo_nombre) {
    //if (nuevo_nombre != NULL) {
        strcpy(p->nombre, nuevo_nombre);
    //}
}

void modificar_apellidoPaciente(Paciente *p, const char *nuevo_apellido) {
    //if (nuevo_apellido != NULL) {
        strcpy(p->apellido, nuevo_apellido);
    //}
}

void modificar_dniPaciente(Paciente *p, long nuevo_dni) {
    //if (nuevo_dni > 0) {
        p->dni = nuevo_dni;
    //}
}

void modificar_osocialPaciente(Paciente *p, int nueva_osocial) {
    if (nueva_osocial == 1) {
        p->osocial = 1;
    } else {
        p->osocial = 0;
    }
}

/* GETTERS (CONSULTORES) */

char* obtener_nombrePaciente(Paciente p) {
    /*if (destino != NULL) {
        strcpy(destino, p.nombre);
    }*/

    char *nombre_a_retornar = (char *) malloc( strlen( p.nombre ) + 1 );
    if (nombre_a_retornar == NULL ) exit(1);
    strcpy( nombre_a_retornar, p.nombre );
    return nombre_a_retornar; 
}

char* obtener_apellidoPaciente(Paciente p) {
    /*if (destino != NULL) {
        strcpy(destino, p.apellido);
    }*/
   char *nombre_a_retornar = (char *) malloc( strlen( p.apellido ) + 1 );
    if (nombre_a_retornar == NULL ) exit(1);
    strcpy( nombre_a_retornar, p.apellido );
    return nombre_a_retornar; 
}

long obtener_dniPaciente(Paciente p) {
    return p.dni;
}

int obtener_osocialPaciente(Paciente p) {
    return p.osocial;
}

#endif // PACIENTES_H_INCLUDE