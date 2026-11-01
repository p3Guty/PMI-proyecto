/* =========================================================================
 * ARCHIVO: paciente.h
 * COMPONENTE: TDA Paciente (Persona 1 - PMI 2026)
 * DESCRIPCION: Define la estructura interna de un Paciente y sus operaciones
 *              primitivas de lectura y modificacion sin entrada/salida.
 * ========================================================================= */

#ifndef PACIENTES_H_INCLUDE
#define PACIENTES_H_INCLUDE

#include <string.h>

#define MAX_CADENA 50

/* Consigna a: TDA Paciente, sus campos y operaciones primitivas. */
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

int modificar_nombrePaciente(Paciente *p, const char *nuevo_nombre);
int modificar_apellidoPaciente(Paciente *p, const char *nuevo_apellido);
int modificar_dniPaciente(Paciente *p, long nuevo_dni);
int modificar_osocialPaciente(Paciente *p, int nueva_osocial);

char *obtener_nombrePaciente(Paciente p);
char *obtener_apellidoPaciente(Paciente p);
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
    initPaciente(&p);
    modificar_nombrePaciente(&p, nombre);
    modificar_apellidoPaciente(&p, apellido);
    modificar_dniPaciente(&p, dni);
    modificar_osocialPaciente(&p, osocial);

    return p;
}

/* SETTERS (MODIFICADORES) */

int modificar_nombrePaciente(Paciente *p, const char *nuevo_nombre) {
    strcpy(p->nombre, nuevo_nombre);
    return 1;
}

int modificar_apellidoPaciente(Paciente *p, const char *nuevo_apellido) {
    strcpy(p->apellido, nuevo_apellido);
    return 1;
}

int modificar_dniPaciente(Paciente *p, long nuevo_dni) {
    p->dni = nuevo_dni;
    return 1;
}

int modificar_osocialPaciente(Paciente *p, int nueva_osocial) {
    p->osocial = nueva_osocial;
    return 1;
}

/* GETTERS (CONSULTORES) */

char *obtener_nombrePaciente(Paciente p) {
    char *nombre_a_retornar = (char *) malloc( strlen( p.nombre ) + 1 );
    if (nombre_a_retornar == NULL ) exit(1);
    strcpy( nombre_a_retornar, p.nombre );
    return nombre_a_retornar; 
}

char *obtener_apellidoPaciente(Paciente p) {
    char *nombre_a_retornar = (char *) malloc( strlen( p.nombre ) + 1 );
    if (nombre_a_retornar == NULL ) exit(1);
    strcpy( nombre_a_retornar, p.nombre );
    return nombre_a_retornar; 
}

long obtener_dniPaciente(Paciente p) {
    return p.dni;
}

int obtener_osocialPaciente(Paciente p) {
    return p.osocial;
}

#endif // PACIENTES_H_INCLUDE