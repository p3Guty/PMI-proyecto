/* =========================================================================
 * ARCHIVO DE APLICACION / CLIENTE: usopaciente.c
 * CONSIGNAS DESARROLLADAS:
 *   - Consigna n   : Cargar un paciente por teclado.
 *   - Consigna enye: Eliminar un paciente por teclado (validando que no posea turnos).
 * ========================================================================= */

#include <stdio.h>
#include <stdlib.h>
#include "listaE_Paciente.h"

/* -------------------------------------------------------------------------
 * CONSIGNA N: Cargar un paciente por teclado e insertarlo en la lista.
 * ------------------------------------------------------------------------- */
void consigna_n_cargarPaciente(ListaEPaciente *lista_p) {
    char nom[MAX_CADENA];
    char ape[MAX_CADENA];
    long dni;
    int osocial;
    Paciente p_nuevo;

    printf("\n=========================================\n");
    printf("     CONSIGNA N: CARGAR NUEVO PACIENTE   \n");
    printf("=========================================\n");

    if (isFullListaE(*lista_p) == 1) {
        printf("ERROR: La lista de pacientes esta llena. No se pueden agregar mas registros.\n");
        return;
    }

    printf("Ingrese el DNI del paciente: ");
    scanf("%ld", &dni);

    /* Validacion de DNI unico */
    if (existePaciente(*lista_p, dni) == 1) {
        printf("ERROR: Ya existe un paciente registrado con el DNI %ld.\n", dni);
        return;
    }

    printf("Ingrese el nombre del paciente (sin espacios): ");
    scanf("%s", nom);

    printf("Ingrese el apellido del paciente (sin espacios): ");
    scanf("%s", ape);

    do {
        printf("¿Posee obra social? (1 = SI / 0 = NO): ");
        scanf("%d", &osocial);
        if (osocial != 0 && osocial != 1) {
            printf("Error: Ingrese 1 para SI o 0 para NO.\n");
        }
    } while (osocial != 0 && osocial != 1);

    /* Creamos e insertamos el paciente usando las primitivas */
    p_nuevo = crearPaciente(nom, ape, dni, osocial);

    if (insertListaE(lista_p, p_nuevo) == 1) {
        printf("EXITO: Paciente %s %s (DNI: %ld) registrado correctamente.\n", nom, ape, dni);
    } else {
        printf("ERROR: No se pudo registrar el paciente.\n");
    }
}

/* -------------------------------------------------------------------------
 * CONSIGNA ENYE: Eliminar un paciente por teclado (solo si no posee turnos).
 * Parametros:
 *   - lista_p: puntero a la lista estatica de pacientes.
 *   - tiene_turnos: valor de control (1 si el paciente tiene turnos activos en
 *                   la lista de turnos de Persona 3, 0 si esta libre de turnos).
 * ------------------------------------------------------------------------- */
void consigna_enye_eliminarPaciente(ListaEPaciente *lista_p, int tiene_turnos) {
    long dni;
    Paciente p_temp;
    char nom[MAX_CADENA];
    char ape[MAX_CADENA];

    printf("\n=========================================\n");
    printf("   CONSIGNA ENYE: ELIMINAR UN PACIENTE  \n");
    printf("=========================================\n");

    if (isEmptyListaE(*lista_p) == 1) {
        printf("ERROR: La lista de pacientes esta vacia. No hay datos para eliminar.\n");
        return;
    }

    printf("Ingrese el DNI del paciente que desea eliminar: ");
    scanf("%ld", &dni);

    /* Búsqueda del paciente en la lista estatica */
    if (buscarPacientePorDni(lista_p, dni) == 0) {
        printf("RESULTADO: No se encontro ningun paciente con el DNI %ld.\n", dni);
        return;
    }

    /* Copiamos los datos del paciente hallado */
    copyListaE(*lista_p, &p_temp);
    obtener_nombrePaciente(p_temp, nom);
    obtener_apellidoPaciente(p_temp, ape);

    /* RESTRICCION DEL PMI 2026: No se puede eliminar si posee turnos */
    if (tiene_turnos == 1) {
        printf("RECHAZADO: El paciente %s %s (DNI: %ld) posee turnos asignados.\n", nom, ape, dni);
        printf("No se puede eliminar un paciente con turnos registrados en el sistema.\n");
        return;
    }

    /* Si no posee turnos, procedemos a la eliminacion mediante la primitiva */
    if (suppressListaE(lista_p) == 1) {
        printf("EXITO: El paciente %s %s (DNI: %ld) ha sido eliminado correctamente de la lista.\n", nom, ape, dni);
    } else {
        printf("ERROR: No se pudo eliminar el paciente.\n");
    }
}

/* Ejemplo de menu principal de prueba */
int main(void) {
    ListaEPaciente lista_pacientes;
    int opcion = 0;
    int simulacion_turnos = 0; /* Variable de simulacion: 0=Sin turnos, 1=Con turnos */

    initListaE(&lista_pacientes);

    printf("=== PRUEBA DE CONSIGNAS N Y ENYE (PERSONA 1) ===\n");

    do {
        printf("\n--- MENU DE PACIENTES ---\n");
        printf("<1> Cargar paciente (Consigna n)\n");
        printf("<2> Eliminar paciente (Consigna enye)\n");
        printf("<3> Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                consigna_n_cargarPaciente(&lista_pacientes);
                break;

            case 2:
                /*
                 * En la integracion final, aqui se consulta a la lista de turnos (Persona 3).
                 * Para esta prueba, preguntamos al usuario si simulamos que tiene turnos.
                 */
                printf("Simulacion de control: ¿El paciente a eliminar tiene turnos registrados? (1 = SI, 0 = NO): ");
                scanf("%d", &simulacion_turnos);
                consigna_enye_eliminarPaciente(&lista_pacientes, simulacion_turnos);
                break;

            case 3:
                printf("\nSaliendo del programa de prueba de Persona 1. Fin de ejecucion.\n");
                break;

            default:
                printf("\nOpcion invalida. Intente nuevamente.\n");
        }
    } while (opcion != 3);

    return 0;
}
