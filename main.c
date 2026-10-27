#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "listaE_Paciente.h"
#include "listaE_pancientes.h"
#include "fecha.h"
#include "turno.h"
#include "listaVO_turno.h"


//FUNCIONES DE TURNO Y LISTAVOTURNO

/* -------------------------------------------------------------------------
 * 1. Busqueda de Turno por ID
 * Recorre la lista buscando la coincidencia. Deja el cursor parado en el nodo.
 * ------------------------------------------------------------------------- */
int buscarTurnoPorId(ListaVO_Turno *l, int id_buscado) {
    Turno temp;

    resetListaVO(l);
    while (isOosListaVO(*l) == 0) {
        copyListaVO(*l, &temp);
        if (obtener_idTurno(temp) == id_buscado) {
            return 1; /* Coincidencia hallada: cur posicionado */
        }
        forwardsListaVO(l);
    }
    return 0; /* No encontrado */
}

/* -------------------------------------------------------------------------
 * 2. Cancelar Turno en Lista
 * Busca el id, valida el estado actual e informa el resultado al usuario.
 * ------------------------------------------------------------------------- */
int cancelarTurnoEnLista(ListaVO_Turno *l, int id_buscado) {
    Turno temp;

    if (buscarTurnoPorId(l, id_buscado) == 1) {
        copyListaVO(*l, &temp);

        /* Validacion previa de estado */
        if (obtener_estadoTurno(temp) == ESTADO_CANCELADO) {
            printf("\n[AVISO] El turno ID %d ya se encuentra CANCELADO previamente.\n", id_buscado);
            return 0;
        }

        /* Modificacion y guardado directo sobre el nodo activo */
        modificar_estadoTurno(&temp, ESTADO_CANCELADO);
        l->cur->vipd = temp;

        printf("\n[EXITO] El turno ID %d ha sido CANCELADO correctamente.\n", id_buscado);
        return 1;
    }

    printf("\n[ERROR] No se encontro ningun turno registrado con el ID %d.\n", id_buscado);
    return 0;
}

/* -------------------------------------------------------------------------
 * 3. Confirmar Turno en Lista
 * Busca el id, valida reglas de negocio e informa el resultado al usuario.
 * ------------------------------------------------------------------------- */
int confirmarTurnoEnLista(ListaVO_Turno *l, int id_buscado) {
    Turno temp;

    if (buscarTurnoPorId(l, id_buscado) == 1) {
        copyListaVO(*l, &temp);

        if (obtener_estadoTurno(temp) == ESTADO_CONFIRMADO) {
            printf("\n[AVISO] El turno ID %d ya habia sido CONFIRMADO previamente.\n", id_buscado);
            return 0;
        }

        if (obtener_estadoTurno(temp) == ESTADO_CANCELADO) {
            printf("\n[ERROR] No se puede confirmar el turno ID %d porque se encuentra CANCELADO.\n", id_buscado);
            return 0;
        }

        modificar_estadoTurno(&temp, ESTADO_CONFIRMADO);
        l->cur->vipd = temp;

        printf("\n[EXITO] El turno ID %d ha sido CONFIRMADO correctamente.\n", id_buscado);
        return 1;
    }

    printf("\n[ERROR] No se encontro ningun turno registrado con el ID %d.\n", id_buscado);
    return 0;
}

/* -------------------------------------------------------------------------
 * 4. Conteo Recursivo de Turnos Atendidos por Dia y Mes (Consigna m)
 * ------------------------------------------------------------------------- */
int contarTurnosAtendidosRecursivaNodo(Nodo *n, int dia, int mes) {
    Turno t;
    Fecha f;
    int est;
    int suma;

    if (n == NULL) {
        return 0;
    }

    t = n->vipd;
    f = obtener_fechaTurno(t);
    est = obtener_estadoTurno(t);
    suma = 0;

    if (f.dia == dia && f.mes == mes && est == ESTADO_ATENDIDO) {
        suma = 1;
    }

    return suma + contarTurnosAtendidosRecursivaNodo(n->next, dia, mes);
}

int contarTurnosAtendidosRecursiva(ListaVO_Turno l, int dia, int mes) {
    int total;

    total = contarTurnosAtendidosRecursivaNodo(l.acc, dia, mes);

    printf("\n===========================================================\n");
    printf(" REPORTE RECURSIVO: TURNOS ATENDIDOS POR DIA Y MES          \n");
    printf("===========================================================\n");
    printf(" Fecha consultada : %02d/%02d\n", dia, mes);
    printf(" Total atendidos  : %d paciente(s)\n", total);
    printf("===========================================================\n");

    return total;
}

/* -------------------------------------------------------------------------
 * 5. Conteo Recursivo de Turnos Asignados en un Mes (Consigna l)
 * (Cuenta turnos en estado SOLICITADO o CONFIRMADO)
 * ------------------------------------------------------------------------- */
int contarTurnosAsignadosMesRecursivaNodo(Nodo *n, int mes_buscado) {
    Turno t;
    Fecha f;
    int est;
    int suma;

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

    return suma + contarTurnosAsignadosMesRecursivaNodo(n->next, mes_buscado);
}

int contarTurnosAsignadosMesRecursiva(ListaVO_Turno l, int mes_buscado) {
    int total;

    total = contarTurnosAsignadosMesRecursivaNodo(l.acc, mes_buscado);

    printf("\n===========================================================\n");
    printf(" REPORTE RECURSIVO: TURNOS ASIGNADOS EN EL MES              \n");
    printf("===========================================================\n");
    printf(" Mes consultado   : %02d\n", mes_buscado);
    printf(" Total asignados  : %d turno(s) (Solicitados / Confirmados)\n", total);
    printf("===========================================================\n");

    return total;
}

/* -------------------------------------------------------------------------
 * 6. Calculo del Monto Recaudado en un Mes (Consigna r)
 * Acumula el dinero cobrado por turnos en estado ATENDIDO.
 * ------------------------------------------------------------------------- */
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

    printf("\n===========================================================\n");
    printf(" REPORTE DE RECAUDACION: TOTAL COBRADO EN EL MES           \n");
    printf("===========================================================\n");
    printf(" Mes consultado   : %02d\n", mes);
    printf(" Recaudacion total: $%.2f\n", total);
    printf("===========================================================\n");

    return total;
}

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