//cspell:disable
#ifndef PACIENTES_H_INCLUDE
#define PACIENTES_H_INCLUDE

#include <stdlib.h>
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

void initPaciente(Paciente *p);
Paciente crearPaciente(const char *nombre, const char *apellido, long dni, int osocial);
int modificar_nombrePaciente(Paciente *p, const char *nombre);
int modificar_apellidoPaciente(Paciente *p, const char *apellido);
int modificar_dniPaciente(Paciente *p, long dni);
int modificar_osocialPaciente(Paciente *p, int osocial);
char *obtener_nombrePaciente(Paciente p);
char *obtener_apellidoPaciente(Paciente p);
long obtener_dniPaciente(Paciente p);
int obtener_osocialPaciente(Paciente p);

void initPaciente(Paciente *p) {
    strcpy(p->nombre, "Sin Nombre");
    strcpy(p->apellido, "Sin Apellido");
    p->dni = 0;
    p->osocial = 0;
}

Paciente crearPaciente(const char *nombre, const char *apellido, long dni, int osocial) {
    Paciente p;
    initPaciente(&p);
    modificar_nombrePaciente(&p, nombre);
    modificar_apellidoPaciente(&p, apellido);
    modificar_dniPaciente(&p, dni);
    modificar_osocialPaciente(&p, osocial);
    return p;
}

int modificar_nombrePaciente(Paciente *p, const char *nombre) {
    strcpy(p->nombre, nombre);
    return 1;
}

int modificar_apellidoPaciente(Paciente *p, const char *apellido) {
    strcpy(p->apellido, apellido);
    return 1;
}

int modificar_dniPaciente(Paciente *p, long dni) {
    p->dni = dni;
    return 1;
}

int modificar_osocialPaciente(Paciente *p, int osocial) {
    p->osocial = osocial;
    return 1;
}

char *obtener_nombrePaciente(Paciente p) {
    char *nombre = (char *)malloc(strlen(p.nombre) + 1);
    if (nombre != NULL) strcpy(nombre, p.nombre);
    return nombre;
}

char *obtener_apellidoPaciente(Paciente p) {
    char *apellido = (char *)malloc(strlen(p.apellido) + 1);
    if (apellido != NULL) strcpy(apellido, p.apellido);
    return apellido;
}

long obtener_dniPaciente(Paciente p) { return p.dni; }
int obtener_osocialPaciente(Paciente p) { return p.osocial; }

#endif // PACIENTES_H_INCLUDE