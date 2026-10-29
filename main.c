#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "listaE_pacientes.h"
#include "fecha.h"
#include "turno.h"
#include "listaVO_turno.h"
#include "agenda.h"
#include "pacientes.h"

void cargarPacienteMenu(ListaE_Paciente *listaP) {
    long int dniIngresado;
    char nombreIngresado[15];
    char apellidoIngresado[15];
    int osocialIngresada;
    int existe = 0;
    Paciente pCopia;
    Paciente nuevoPaciente;

    printf("\n=== [OPCION n] CARGAR NUEVO PACIENTE ===\n");

    if (isFullListaE(*listaP)) {
        printf("Error: La lista de pacientes esta llena. No se pueden agregar mas registros.\n");
        return;
    }

    printf("Ingrese el DNI del paciente: ");
    scanf("%ld", &dniIngresado);

    resetListaE(listaP);
    while (!isOosListaE(*listaP) && !existe) {
        copyListaE(*listaP, &pCopia);
        if (obtener_dniPaciente(pCopia) == dniIngresado) {
            existe = 1;
        } else {
            forwardsListaE(listaP);
        }
    }
    if (existe) {
        printf("Error: Ya existe un paciente con el DNI %ld.\n", dniIngresado);
        return;
    }

    printf("Ingrese Nombre: ");
    scanf(" %14[^\n]", nombreIngresado);
    printf("Ingrese Apellido: ");
    scanf(" %14[^\n]", apellidoIngresado);

    do {
        printf("Tiene obra social? (1 = Si / 0 = No): ");
        scanf("%d", &osocialIngresada);
        if (osocialIngresada != 0 && osocialIngresada != 1) {
            printf("Valor Invalido. Ingrese 1 para 'Si' o 0 para 'No'.\n");
        }
    } while (osocialIngresada != 0 && osocialIngresada != 1);

    setDni(&nuevoPaciente, dniIngresado);
    setNombre(&nuevoPaciente, nombreIngresado);
    setApellido(&nuevoPaciente, apellidoIngresado);
    setOsocial(&nuevoPaciente, osocialIngresada);

    insertListaE(listaP, nuevoPaciente);
    printf("Exito! El paciente con DNI %ld ha sido registrado correctamente.\n", dniIngresado);
}

void eliminarPacienteMenu(ListaE_Paciente *listaP, ListaVO_Turno listaT) {
    long int dniIngresado;
    int encontrado = 0;
    Paciente pCopia;

    printf("\n=== [OPCION n] ELIMINAR PACIENTE ===\n");

    if (isEmptyListaE(*listaP)) {
        printf("Aviso: No hay pacientes registrados en el sistema.\n");
        return;
    }

    printf("Ingrese el DNI del paciente a eliminar: ");
    scanf("%ld", &dniIngresado);

    resetListaE(listaP);
    while (!isOosListaE(*listaP) && !encontrado) {
        copyListaE(*listaP, &pCopia);
        if (obtener_dniPaciente(pCopia) == dniIngresado) {
            encontrado = 1;
        } else {
            forwardsListaE(listaP);
        }
    }

    if (!encontrado) {
        printf("Aviso: No se encontro ningun paciente registrado con el DNI %ld.\n", dniIngresado);
        return;
    }

  /* 4\. Verificación de turnos asignados (Consulta a Persona 3) */

  /* La función tieneTurnosDni la define Persona 3 en su TDA de Turnos */
  if (tieneTurnosDni(listaT, dniIngresado)) {
    printf("Error: El paciente con DNI %ld posee turnos asignados. Debe cancelar sus turnos antes de eliminarlo.\n", dniIngresado);
    return;
  }

    suppressListaE(listaP);
    printf("Exito! El paciente con el DNI %ld ha sido eliminado del sistema.\n", dniIngresado);
}
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

/*------------------------------------------------------------------------------
 * Funcion: buscarPacientePorDni CONSIGNA P.
 * Propósito: Recorre la lista buscando un paciente por su DNI.
 * Retorno: 1 si lo encuentra (cur queda parado en el elemento), 0 si no existe.
 -------------------------------------------------------------------------------*/
int buscarPacientePorDni(ListaE_Paciente *l, long dni_buscado) {
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
int existePaciente(ListaE_Paciente l, long dni_buscado) {
    return buscarPacientePorDni(&l, dni_buscado);
}


 /*                      consignas de chel jijo                     */


void buscarfechalibre(Fecha agenda[]){
    printf("---A continuacion se solicitara una fecha para analizar si hay turnos disponibles.---\n");
    int mesB, diaB;
    printf("Ingrese el mes que desea inspeccionar (solo con ): ");
    scanf("%d", &mesB);

    //              control antes de inspeccionar la lista              //
    while(mesB != 11 && mesB != 12){
        printf("[ERROR] no ingreso un MES valido. Intente nuevamente (solo con NOVIEMBRE o DICIEMBRE): ");
        scanf("%d", &mesB);
    }
    printf("Ingrese el dia que desea inspeccionar: ");
    scanf("%d", &diaB);

    //              control antes de inspeccionar la lista              //
    if(mesB==11){
        while(diaB<1 || diaB>30){
            printf("[ERROR] no ingreso un DIA valido. Intente nuevamente (NOVIEMBRE tiene 1-30 dias): ");
            scanf("%d", &diaB);
        }
    }
    else{
        while(diaB<1 || diaB>31){
            printf("[ERROR] no ingreso un DIA valido. Intente nuevamente (DICIEMBRE tiene 1-31 dias): ");
            scanf("%d", &diaB);
        }
    }

    int i, encontrados;
    encontrados = 0;
    printf("Los turnos disponibles para esa fecha son: ");
    for(i=0; i<Tagenda; i++){
        if(get_mes(agenda[i]) == diaB && get_mes(agenda[i]) == mesB){
            if(get_disponible(agenda[i]) == 'L'){
                printf("ID del turno: %d\n", i+1);
                printf("Dia: %d\n", get_dia(agenda[i]));
                printf("Mes: %d\n", get_mes(agenda[i]));
                printf("Hora: %02d:%02d\n", get_hora(agenda[i]), get_minuto(agenda[i]));
                encontrados++;
            }
        }
    }
    if(encontrados==0){
        printf("No se han encontrado turnos libres para esa fecha.");
    }
}

//                        consigna d                       //

void buscarfechaocupada(Fecha p[]){
    int m;
    printf("A continuacion ingrese un mes (11 = noviembre o 12 = diciembre) para buscar las fechas ocupadas del mismo: ");
    scanf("%d", &m);
    while(m != 11 && m != 12){
        printf("Error. Intente nuevamente con 11 = NOVIEMBRE o 12 = DICIEMBRE: ");
        scanf("%d", &m);
    }
    int i, encontrados;
    encontrados=0;
    printf("Los turnos NO disponibles del mes son: ");
    for(i=0 ; i<Tagenda ; i++){
        if(m == get_mes(p[i])){
            if(get_disponible(p[i]) == 'O'){
                printf("ID del turno: %d", i+1);
                printf("Dia: %d", get_dia(p[i]));
                printf("Mes: %d", get_mes(p[i]));
                printf("Hora: %02d:%02d", get_hora(p[i]), get_minuto(p[i]));
                encontrados++;
            }
        }
    }
    if(encontrados==0){
        printf("No se han encontrado turnos ocupados para esa fecha.");
    }


}


//              consigna e ya esta hecha en el archivo de turno creo               //

//                                consigna j                                     //

void guardaryeliminarturnocancelado(ListaVO_Turno *l, Turno t){
    FILE *fp;
    fp= fopen("turno_cancelado.txt", "a");
    if(fp == NULL){
        printf("Error al crear o abrir el archivo 'turno_cancelado.txt.");
        return;
    }
    fprintf(fp, "Turno Cancelado - Fecha: %02d/%02d/%d | Hora: %02d:%02d Hs\\n", get_dia(t.fecha), get_mes(t.fecha), get_anio(t.fecha), get_hora(t.fecha), get_minuto(t.fecha));
    fclose(fp);
    suppressListaVO(l);
}




//                           consigna s                              //
void backup(ListaVO_Turno l1, ListaE_Paciente l2, Fecha a[]){

//           Empezamos con turno.txt             //
    Turno t;
    FILE *ft;
    ft= fopen("turno.txt", "w");
    if(ft == NULL){
        printf("Error al crear o abrir el archivo 'turno.txt'.");
        return;
    }
    resetListaVO(&l1);
    while(!isOosListaVO(l1)){
        copyListaVO(l1, &t);
        fprintf(ft, "Turno: %d.\n D.N.I. del paciente: %ld.\n Monto: %f.\n Mutual: %s.\n Fecha: %02d/%02d/%d | Hora: %02d:%02d Hs.\n Estado: %d\n %c\n\n", obtener_idTurno(t), obtener_dniPacienteTurno(t), obtener_monto(t), t.mutual, get_dia(t.fecha), get_mes(t.fecha), get_anio(t.fecha), get_hora(t.fecha), get_minuto(t.fecha), obtener_estadoTurno(t), get_disponible(t.fecha));
        forwardsListaVO(&l1);
    }
    fclose(ft);
    printf("Respaldo completado con exito en 'turno.txt'.\n");

//           2- pacientes.txt                        //
    Paciente p;
    FILE *fp;
    fp= fopen("paciente.txt", "w");
    if(fp == NULL){
        printf("Error al crear o abrir el archivo 'paciente.txt'.\n");
        return;
    }
    resetListaE(&l2);
    while(!isOosListaE(l2)){
        copyListaE(l2, &p);
        fprintf(fp, "Nombre: %s.\n Apellido: %s.\n D.N.I: %ld.\n Obra social: %d.\n\n", p.nombre, p.apellido, obtener_dniPaciente(p), obtener_osocialPaciente(p));
        forwardsListaE(&l2);
    }
    fclose(fp);
    printf("Respaldo completado con exito en 'paciente.txt'.\n\n");


//           Y agenda.txt                                  //
    FILE *fa;
    fa= fopen("agenda.txt", "w");
    if(fa == NULL){
        printf("Error al crear o abrir el archivo 'agenda.txt'.\n");
        return;
    }
    int i;
    for(i=0;i<Tagenda;i++){
        fprintf("Dia: %02d.\n Mes: %02d.\n Anio: %d.\n Horario: %02d:%02d.\n Disponibilidad: '%c'\n\n", get_dia(a[i]), get_mes(a[i]), get_anio(a[i]), get_hora(a[i]), get_minuto(a[i]), get_disponible(a[i]));
    }
    fclose(fa);
    printf("Respaldo completado con exito en 'agenda.txt'.\n\n");

}
