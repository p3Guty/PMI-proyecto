#include <stdio.h>
#include <stdlib.h>

#include "listaE_pacientes.h"
#include "fecha.h"
#include "turno.h"
#include "listaVO_turno.h"
#include "agenda.h"
#include "pacientes.h"

//funciones de turno y listaVOturno
void menu_cancelarTurno(ListaVO_Turno *l) {
    int id;
    printf("\n--- CANCELACION DE TURNO ---\n");
    printf("Ingrese el ID del turno a cancelar: ");
    scanf("%d", &id);
    cancelarTurnoEnLista(l, id);
}

void menu_confirmarTurno(ListaVO_Turno *l) {
    int id;
    printf("\n--- CONFIRMACION DE TURNO ---\n");
    printf("Ingrese el ID del turno a confirmar: ");
    scanf("%d", &id);
    confirmarTurnoEnLista(l, id);
}

void menu_consultarAtendidos(ListaVO_Turno l) {
    int dia, mes;
    printf("\n--- CONSULTA RECURSIVA DE TURNOS ATENDIDOS ---\n");
    printf("Ingrese el dia: ");
    scanf("%d", &dia);
    printf("Ingrese el mes: ");
    scanf("%d", &mes);
    contarTurnosAtendidosRecursiva(l, dia, mes);
}

void menu_consultarAsignadosMes(ListaVO_Turno l) {
    int mes;
    printf("\n--- CONSULTA RECURSIVA DE TURNOS ASIGNADOS DEL MES ---\n");
    printf("Ingrese el numero de mes (1-12): ");
    scanf("%d", &mes);
    contarTurnosAsignadosMesRecursiva(l, mes);
}

void menu_consultarMontoMes(ListaVO_Turno l) {
    int mes;
    printf("\n--- CONSULTA DE RECAUDACION MENSUAL ---\n");
    printf("Ingrese el numero de mes (1-12): ");
    scanf("%d", &mes);
    calcularMontoMes(l, mes);
}

void menu_compararFechasInteractivo(void) {
    Fecha f1;
    Fecha f2;
    int resultado;

    printf("\n===========================================================\n");
    printf("        COMPARACION CRONOLOGICA DE DOS FECHAS               \n");
    printf("===========================================================\n");

    /* 1. Ingreso de la Primera Fecha */
    printf("\n--- INGRESO DE LA PRIMERA FECHA (f1) ---\n");
    printf("Ingrese dia (1-31): ");
    scanf("%d", &f1.dia);
    printf("Ingrese mes (1-12): ");
    scanf("%d", &f1.mes);
    printf("Ingrese anio (4 digitos): ");
    scanf("%d", &f1.anio);
    printf("Ingrese hora (0-23): ");
    scanf("%d", &f1.hora);
    printf("Ingrese minutos (0 o 30): ");
    scanf("%d", &f1.minuto);

    /* 2. Ingreso de la Segunda Fecha */
    printf("\n--- INGRESO DE LA SEGUNDA FECHA (f2) ---\n");
    printf("Ingrese dia (1-31): ");
    scanf("%d", &f2.dia);
    printf("Ingrese mes (1-12): ");
    scanf("%d", &f2.mes);
    printf("Ingrese anio (4 digitos): ");
    scanf("%d", &f2.anio);
    printf("Ingrese hora (0-23): ");
    scanf("%d", &f2.hora);
    printf("Ingrese minutos (0 o 30): ");
    scanf("%d", &f2.minuto);

    /* 3. Ejecucion del algoritmo de comparacion */
    resultado = compararFechasTurno(f1, f2);

    /* 4. Muestra del resultado con formato legible en pantalla */
    printf("\n===========================================================\n");
    printf("                RESULTADO DE LA COMPARACION                 \n");
    printf("===========================================================\n");
    printf(" Fecha 1: %02d/%02d/%04d %02d:%02d hs\n", f1.dia, f1.mes, f1.anio, f1.hora, f1.minuto);
    printf(" Fecha 2: %02d/%02d/%04d %02d:%02d hs\n", f2.dia, f2.mes, f2.anio, f2.hora, f2.minuto);
    printf("-----------------------------------------------------------\n");

    if (resultado == -1) {
        printf(" CONCLUSION: La Fecha 1 es ANTERIOR en el tiempo a la Fecha 2.\n");
    } else if (resultado == 1) {
        printf(" CONCLUSION: La Fecha 1 es POSTERIOR en el tiempo a la Fecha 2.\n");
    } else {
        printf(" CONCLUSION: Ambas fechas corresponden EXACTAMENTE al mismo instante.\n");
    }

    printf("===========================================================\n");

    /* 
main(){
//--------------acá se define la agenda---------------//

Fecha agenda[Tagenda];
llenaragenda(&agenda);  // y listo ahr //


} */

}

