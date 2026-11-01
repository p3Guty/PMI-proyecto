//cspell:disable
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fecha.h"
#include "listaE_pacientes.h"
#include "listaVO_turno.h"
#include "turno.h"

#define TAM_PAGINA 10

int llenaragenda(Fecha agenda[TAGENDA]);

int compararFechaLista(Fecha a, Fecha b) {
    if (a.anio != b.anio) return a.anio < b.anio ? -1 : 1;
    if (a.mes != b.mes) return a.mes < b.mes ? -1 : 1;
    if (a.dia != b.dia) return a.dia < b.dia ? -1 : 1;
    if (a.hora != b.hora) return a.hora < b.hora ? -1 : 1;
    if (a.minuto != b.minuto) return a.minuto < b.minuto ? -1 : 1;
    return 0;
}


void limpiarEntrada(void) {
    int c;
    while ((c = getchar()) != '\n' && c != -1) {
    }
}

int leerEntero(const char *mensaje, int *valor) {
    printf("%s", mensaje);
    if (scanf("%d", valor) != 1) {
        limpiarEntrada();
        printf("Entrada invalida.\n");
        return 0;
    }
    limpiarEntrada();
    return 1;
}

int leerDNI(const char *mensaje, long *dni) {
    printf("%s", mensaje);
    if (scanf("%ld", dni) != 1 || *dni <= 0) {
        limpiarEntrada();
        printf("DNI invalido.\n");
        return 0;
    }
    limpiarEntrada();
    return 1;
}

int leerMonto(float *monto) {
    printf("Monto pagado: ");
    if (scanf("%f", monto) != 1 || *monto < 0.0f) {
        limpiarEntrada();
        printf("Monto invalido.\n");
        return 0;
    }
    limpiarEntrada();
    return 1;
}

int leerTexto(const char *mensaje, char texto[MAX_CADENA]) {
    printf("%s", mensaje);
    if (scanf(" %49[^\n]", texto) != 1 || strchr(texto, '|') != NULL) {
        limpiarEntrada();
        printf("Texto invalido.\n");
        return 0;
    }
    limpiarEntrada();
    return 1;
}

int buscarPaciente(ListaE_Paciente *pacientes, long dni) {
    Paciente paciente;
    resetListaE(pacientes);
    while (!isOosListaE(*pacientes)) {
        if (!copyListaE(*pacientes, &paciente)) {
            return 0;
        }
        if (paciente.dni == dni) {
            return 1;
        }
        forwardsListaE(pacientes);
    }
    return 0;
}

int buscarTurno(ListaVO_Turno *turnos, int id) {
    Turno turno;
    resetListaVO(turnos);
    while (!isOosListaVO(*turnos)) {
        turno = copyListaVO(*turnos);
        if (turno.id_turno == id) {
            return 1;
        }
        forwardsListaVO(turnos);
    }
    return 0;
}

int mutualValida(const char *mutual) {
    return strcmp(mutual, "OSDE") == 0 ||
           strcmp(mutual, "ANSES") == 0 ||
           strcmp(mutual, "Galeno") == 0 ||
           strcmp(mutual, "PAMI") == 0;
}

int mismaFecha(Fecha a, Fecha b) {
    return a.dia == b.dia && a.mes == b.mes && a.anio == b.anio &&
           a.hora == b.hora && a.minuto == b.minuto;
}

int tieneTurnos(ListaVO_Turno turnos, long dni) {
    Turno turno;
    resetListaVO(&turnos);
    while (!isOosListaVO(turnos)) {
        turno = copyListaVO(turnos);
        if (turno.dni_paciente == dni) {
            return 1;
        }
        forwardsListaVO(&turnos);
    }
    return 0;
}

void mostrarPaciente(Paciente paciente) {
    printf("DNI: %ld | Nombre: %s | Apellido: %s | Obra social: %s\n",
           paciente.dni, paciente.nombre, paciente.apellido,
           paciente.osocial ? "Si" : "No");
}

void mostrarTurno(Turno turno) {
    char *estado[] = {
        "Invalido", "Solicitado", "Confirmado", "Atendido", "Cancelado"
    };
    printf("ID: %d | DNI: %ld | %02d/%02d/%04d %02d:%02d"
           " | %s | $%.2f | %s\n",
           turno.id_turno, turno.dni_paciente,
           turno.fecha.dia, turno.fecha.mes, turno.fecha.anio,
           turno.fecha.hora, turno.fecha.minuto,
           turno.estado >= 1 && turno.estado <= 4 ?
               estado[turno.estado] : estado[0],
           turno.monto, turno.mutual);
}

/* Consignas a y n: alta de pacientes. */
int altaPaciente(ListaE_Paciente *pacientes, long dni) {
    Paciente paciente;
    int obraSocial;
    if (isFullListaE(*pacientes)) {
        printf("No hay espacio para mas pacientes.\n");
        return 0;
    }
    if (dni == 0 && !leerDNI("DNI: ", &dni)) {
        return 0;
    }
    if (buscarPaciente(pacientes, dni)) {
        printf("Ese DNI ya esta registrado.\n");
        return 0;
    }
    initPaciente(&paciente);
    if (!leerTexto("Nombre: ", paciente.nombre) ||
        !leerTexto("Apellido: ", paciente.apellido) ||
        !leerEntero("Tiene obra social? (1=si, 0=no): ", &obraSocial) ||
    (obraSocial != 0 && obraSocial != 1) ||
        !modificar_dniPaciente(&paciente, dni) ||
        !modificar_osocialPaciente(&paciente, obraSocial) ||
        !insertListaE(pacientes, paciente)) {
        printf("No se pudo registrar el paciente.\n");
        return 0;
    }
    printf("Paciente registrado.\n");
    return 1;
}

/* Consignas a y f: modifica los campos de un paciente. */
void modificarPaciente(ListaE_Paciente *pacientes, ListaVO_Turno turnos) {
    long dni;
    long nuevoDni;
    int campo;
    int obraSocial;
    int posicion;
    char texto[MAX_CADENA];
    Paciente paciente;
    if (!leerDNI("DNI del paciente: ", &dni) ||
        !buscarPaciente(pacientes, dni) ||
        !copyListaE(*pacientes, &paciente)) {
        printf("Paciente no encontrado.\n");
        return;
    }
    posicion = pacientes->cur;
    printf("1. Nombre  2. Apellido  3. DNI  4. Obra social\n");
    if (!leerEntero("Campo a modificar: ", &campo)) {
        return;
    }
    if (campo == 1 || campo == 2) {
        if (!leerTexto("Nuevo texto: ", texto)) {
            return;
        }
        if (campo == 1) {
            modificar_nombrePaciente(&paciente, texto);
        } else {
            modificar_apellidoPaciente(&paciente, texto);
        }
    } else if (campo == 3 || campo == 4) {
        if (tieneTurnos(turnos, dni)) {
            printf("No se puede cambiar el DNI u obra social: tiene turnos.\n");
            return;
        }
        if (campo == 3) {
            if (!leerDNI("Nuevo DNI: ", &nuevoDni) ||
                (nuevoDni != dni && buscarPaciente(pacientes, nuevoDni)) ||
                !modificar_dniPaciente(&paciente, nuevoDni)) {
                printf("DNI invalido o repetido.\n");
                return;
            }
        } else if (!leerEntero("Tiene obra social? (1=si, 0=no): ",
                               &obraSocial) ||
                   (obraSocial != 0 && obraSocial != 1) ||
                   !modificar_osocialPaciente(&paciente, obraSocial)) {
            printf("Obra social invalida.\n");
            return;
        }
    } else {
        printf("Opcion invalida.\n");
        return;
    }
    pacientes->elementos[posicion] = paciente;
    printf("Paciente modificado.\n");
}

/* Consigna a: asigna una fecha libre de la agenda. */
void solicitarTurno(ListaE_Paciente *pacientes, ListaVO_Turno *turnos, Fecha agenda[]) {
    long dni;
    int id;
    Fecha fecha;
    Paciente paciente;
    Turno turno;
    if (!leerDNI("DNI del paciente: ", &dni)) {
        return;
    }
    if (!buscarPaciente(pacientes, dni)) {
        printf("Paciente nuevo. Cargue sus datos.\n");
        if (!altaPaciente(pacientes, dni)) {
            return;
        }
    }
    if (!leerEntero("ID de la fecha disponible (0-389): ", &id) ||
        id < 0 || id >= TAGENDA || agenda[id].disponible != 'L') {
        printf("ID invalido o fecha ocupada.\n");
        return;
    }
    if (buscarTurno(turnos, id) || !buscarPaciente(pacientes, dni) ||
        !copyListaE(*pacientes, &paciente)) {
        printf("No se pudo encontrar el paciente o la fecha.\n");
        return;
    }
    fecha = agenda[id];
    set_disponible(&fecha, 'O');
    turno = crearTurno(id, dni, 0.0f, "Sin Mutual", fecha,
                       ESTADO_SOLICITADO);
    if (turno.id_turno != id || !insertListaVO(turnos, turno)) {
        printf("No se pudo asignar el turno.\n");
        return;
    }
    agenda[id] = fecha;
    printf("Turno solicitado.\n");
    mostrarTurno(turno);
}

/* Consignas b y d: busca fechas libres u ocupadas. */
void buscarFechas(Fecha agenda[], int ocupadas) {
    int dia = 0;
    int mes;
    int i;
    int cantidad = 0;
    if (!leerEntero("Mes (11 o 12): ", &mes) || (mes != 11 && mes != 12)) {
        printf("Mes invalido.\n");
        return;
    }
    if (!ocupadas &&
        (!leerEntero("Dia: ", &dia) || dia < 1 ||
         dia > (mes == 11 ? 30 : 31))) {
        printf("Dia invalido.\n");
        return;
    }
    for (i = 0; i < TAGENDA; i++) {
        if (agenda[i].mes == mes &&
            (ocupadas || agenda[i].dia == dia) &&
            agenda[i].disponible == (ocupadas ? 'O' : 'L')) {
            printf("ID %d | %02d/%02d/%04d %02d:%02d\n", i,
                   agenda[i].dia, agenda[i].mes, agenda[i].anio,
                   agenda[i].hora, agenda[i].minuto);
            cantidad++;
        }
    }
    if (cantidad == 0) {
        printf("No hay fechas para mostrar.\n");
    }
}

/* Consigna c: lista los turnos de un paciente. */
void mostrarTurnosPaciente(ListaVO_Turno turnos, long dni) {
    int cantidad = 0;
    resetListaVO(&turnos);
    while (!isOosListaVO(turnos)) {
        Turno turno = copyListaVO(turnos);
        if (turno.dni_paciente == dni) {
            mostrarTurno(turno);
            cantidad++;
        }
        forwardsListaVO(&turnos);
    }
    if (cantidad == 0) {
        printf("El paciente no tiene turnos.\n");
    }
}

/* Consignas e y f: busca un turno por su ID y lo muestra. */
void buscarYMostrarTurno(ListaVO_Turno *turnos) {
    int id;
    if (!leerEntero("ID del turno: ", &id) ||
        id < 0 || id >= TAGENDA || !buscarTurno(turnos, id)) {
        printf("Turno no encontrado.\n");
        return;
    }
    if (turnos->cur == NULL) {
        printf("Error: cursor de turnos fuera de estructura.\n");
        return;
    }
    mostrarTurno(copyListaVO(*turnos));
}

/* Consigna g: confirma el turno y carga mutual o monto. */
void confirmarTurno(ListaE_Paciente *pacientes,
                           ListaVO_Turno *turnos) {
    int id;
    int opcion;
    long dni;
    float monto;
    char *mutuales[] = {"OSDE", "ANSES", "Galeno", "PAMI"};
    Paciente paciente;
    Turno turno;
    if (!leerEntero("ID del turno: ", &id) ||
        !buscarTurno(turnos, id) || turnos->cur == NULL ||
        turnos->cur->vipd.estado != ESTADO_SOLICITADO) {
        printf("No se encontro un turno solicitado.\n");
        return;
    }
    turno = copyListaVO(*turnos);
    dni = turno.dni_paciente;
    if (!buscarPaciente(pacientes, dni) ||
        !copyListaE(*pacientes, &paciente)) {
        printf("Paciente del turno no encontrado.\n");
        return;
    }
    if (paciente.osocial) {
        printf("1. OSDE  2. ANSES  3. Galeno  4. PAMI\n");
        if (!leerEntero("Mutual: ", &opcion) || opcion < 1 || opcion > 4) {
            printf("Mutual invalida.\n");
            return;
        }
        modificar_mutual(&turno, mutuales[opcion - 1]);
    } else if (!leerMonto(&monto)) {
        printf("Monto invalido.\n");
        return;
    } else {
        modificar_monto(&turno, monto);
    }
    modificar_estadoTurno(&turno, ESTADO_CONFIRMADO);
    turnos->cur->vipd = turno;
    printf("Turno confirmado.\n");
}

/* Consignas h y j: guarda el turno cancelado y libera su fecha. */
int cancelarTurno(ListaVO_Turno *turnos, Fecha agenda[], int id) {
    FILE *archivo;
    Turno turno;
    if (!buscarTurno(turnos, id) || turnos->cur == NULL) {
        printf("Turno no encontrado.\n");
        return 0;
    }
    turno = copyListaVO(*turnos);
    if (turno.estado == ESTADO_ATENDIDO) {
        printf("Un turno atendido no se puede cancelar.\n");
        return 0;
    }
    archivo = fopen("turno_cancelado.txt", "a");
    if (archivo == NULL) {
        printf("No se pudo abrir turno_cancelado.txt.\n");
        return 0;
    }
    if (fprintf(archivo, "%d|%ld|%.2f|%s|%02d|%02d|%04d|%02d|%02d|4\n",
                turno.id_turno, turno.dni_paciente, turno.monto,
                turno.mutual, turno.fecha.dia, turno.fecha.mes,
                turno.fecha.anio, turno.fecha.hora, turno.fecha.minuto) < 0) {
        fclose(archivo);
        printf("No se pudo guardar la cancelacion.\n");
        return 0;
    }
    if (fclose(archivo) != 0) {
        printf("No se pudo cerrar turno_cancelado.txt.\n");
        return 0;
    }
    set_disponible(&agenda[id], 'L');
    if (!suppressListaVO(turnos)) {
        printf("No se pudo eliminar el turno.\n");
        return 0;
    }
    printf("Turno cancelado y guardado.\n");
    return 1;
}

/* Consigna h: cancela el turno elegido. */
void menuCancelarTurno(ListaVO_Turno *turnos, Fecha agenda[]) {
    int id;
    if (leerEntero("ID del turno: ", &id) && id >= 0 && id < TAGENDA) {
        cancelarTurno(turnos, agenda, id);
    } else {
        printf("ID invalido.\n");
    }
}

/* Consigna i: atiende o cancela el primer turno confirmado del dia. */
void proximoPaciente(ListaVO_Turno *turnos, Fecha agenda[]) {
    int dia;
    int mes;
    int presente;
    Turno turno;
    if (!leerEntero("Mes (11 o 12): ", &mes) ||
        (mes != 11 && mes != 12) ||
        !leerEntero("Dia: ", &dia) || dia < 1 ||
        dia > (mes == 11 ? 30 : 31)) {
        printf("Fecha invalida.\n");
        return;
    }
    resetListaVO(turnos);
    while (!isOosListaVO(*turnos)) {
        turno = copyListaVO(*turnos);
        if (turno.fecha.mes == mes && turno.fecha.dia == dia &&
            turno.estado == ESTADO_CONFIRMADO) {
            mostrarTurno(turno);
            if (!leerEntero("Esta presente? (1=si, 0=no): ", &presente) ||
                (presente != 0 && presente != 1)) {
                printf("Respuesta invalida.\n");
                return;
            }
            if (presente) {
                modificar_estadoTurno(&turno, ESTADO_ATENDIDO);
                turnos->cur->vipd = turno;
                printf("Turno atendido.\n");
            } else {
                cancelarTurno(turnos, agenda, turno.id_turno);
            }
            return;
        }
        forwardsListaVO(turnos);
    }
    printf("No hay turnos confirmados ese dia.\n");
}

/* Consignas f y k: muestra todos los turnos en paginas de diez. */
void mostrarTodosTurnos(ListaVO_Turno turnos) {
    int pagina = 0;
    int cantidad = 0;
    resetListaVO(&turnos);
    while (!isOosListaVO(turnos)) {
        int i;
        printf("\nPagina %d\n", ++pagina);
        for (i = 0; i < TAM_PAGINA && !isOosListaVO(turnos); i++) {
            mostrarTurno(copyListaVO(turnos));
            forwardsListaVO(&turnos);
            cantidad++;
        }
        if (!isOosListaVO(turnos)) {
            printf("Presione Enter para continuar.");
            limpiarEntrada();
        }
    }
    if (cantidad == 0) {
        printf("No hay turnos.\n");
    }
}

/* Consigna l: cuenta e imprime recursivamente los turnos asignados. */
int mostrarAsignados(Nodo *nodo, int mes) {
    int cantidad;
    if (nodo == NULL) {
        return 0;
    }
    cantidad = mostrarAsignados(nodo->next, mes);
    if (nodo->vipd.fecha.mes == mes &&
        (nodo->vipd.estado == ESTADO_SOLICITADO ||
         nodo->vipd.estado == ESTADO_CONFIRMADO)) {
        mostrarTurno(nodo->vipd);
        cantidad++;
    }
    return cantidad;
}

void menuAsignados(ListaVO_Turno turnos) {
    int mes;
    if (!leerEntero("Mes (11 o 12): ", &mes) ||
        (mes != 11 && mes != 12)) {
        printf("Mes invalido.\n");
        return;
    }
    printf("Turnos asignados:\n");
    printf("Total: %d\n", mostrarAsignados(turnos.acc, mes));
}

/* Consigna m: cuenta recursivamente los turnos atendidos de un dia. */
int contarAtendidos(Nodo *nodo, int dia, int mes) {
    if (nodo == NULL) {
        return 0;
    }
    return contarAtendidos(nodo->next, dia, mes) +
           (nodo->vipd.fecha.dia == dia && nodo->vipd.fecha.mes == mes &&
            nodo->vipd.estado == ESTADO_ATENDIDO);
}

void menuAtendidos(ListaVO_Turno turnos) {
    int dia;
    int mes;
    if (!leerEntero("Mes (11 o 12): ", &mes) || (mes != 11 && mes != 12) || !leerEntero("Dia: ", &dia) || dia < 1 || dia > (mes == 11 ? 30 : 31)) {
        printf("Fecha invalida.\n");
        return;
    }
    printf("Turnos atendidos: %d\n",
           contarAtendidos(turnos.acc, dia, mes));
}

/* Consigna n: elimina pacientes que no tengan turnos. */
void eliminarPaciente(ListaE_Paciente *pacientes, ListaVO_Turno turnos) {
    long dni;
    if (!leerDNI("DNI del paciente: ", &dni) ||
        !buscarPaciente(pacientes, dni)) {
        printf("Paciente no encontrado.\n");
        return;
    }
    if (tieneTurnos(turnos, dni)) {
        printf("El paciente tiene turnos y no se puede eliminar.\n");
        return;
    }
    if (!suppressListaE(pacientes)) {
        printf("No se pudo eliminar el paciente.\n");
        return;
    }
    printf("Paciente eliminado.\n");
}

/* Consignas p y q: busca un paciente o muestra la lista completa. */
void consultarPaciente(ListaE_Paciente pacientes, int todos) {
    long dni;
    int pagina = 0;
    int cantidad = 0;
    Paciente paciente;
    if (!todos) {
        if (!leerDNI("DNI del paciente: ", &dni) || !buscarPaciente(&pacientes, dni) || !copyListaE(pacientes, &paciente)) {
            printf("Paciente no encontrado.\n");
            return;
        }
        mostrarPaciente(paciente);
        return;
    }
    resetListaE(&pacientes);
    while (!isOosListaE(pacientes)) {
        int i;
        printf("\nPagina %d\n", ++pagina);
        for (i = 0; i < TAM_PAGINA && !isOosListaE(pacientes); i++) {
            if (!copyListaE(pacientes, &paciente)) {
                printf("Error: cursor de pacientes fuera de estructura.\n");
                return;
            }
            mostrarPaciente(paciente);
            forwardsListaE(&pacientes);
            cantidad++;
        }
        if (!isOosListaE(pacientes)) {
            printf("Presione Enter para continuar.");
            limpiarEntrada();
        }
    }
    if (cantidad == 0) {
        printf("No hay pacientes.\n");
    }
}

/* Consigna r: suma los montos de los turnos atendidos del mes. */
void calcularRecaudacion(ListaVO_Turno turnos) {
    int mes;
    float total = 0.0f;
    if (!leerEntero("Mes (11 o 12): ", &mes) ||
        (mes != 11 && mes != 12)) {
        printf("Mes invalido.\n");
        return;
    }
    resetListaVO(&turnos);
    while (!isOosListaVO(turnos)) {
        Turno turno = copyListaVO(turnos);
        if (turno.fecha.mes == mes && turno.estado == ESTADO_ATENDIDO) {
            total += turno.monto;
        }
        forwardsListaVO(&turnos);
    }
    printf("Recaudacion: $%.2f\n", total);
}

/* Consigna f: cambia el DNI de un turno solicitado. */
void modificarDniTurno(ListaE_Paciente *pacientes, ListaVO_Turno *turnos) {
    int id;
    long dni;
    Turno turno;
    if (!leerEntero("ID del turno: ", &id) || !buscarTurno(turnos, id) || turnos->cur == NULL || turnos->cur->vipd.estado != ESTADO_SOLICITADO) {
        printf("No se encontro un turno solicitado.\n");
        return;
    }
    if (!leerDNI("Nuevo DNI: ", &dni) ||
        !buscarPaciente(pacientes, dni)) {
        printf("El paciente no esta registrado.\n");
        return;
    }
    turno = copyListaVO(*turnos);
    modificar_dniPacienteTurno(&turno, dni);
    turnos->cur->vipd = turno;
    printf("DNI del turno modificado.\n");
}

/* Consigna s: guarda pacientes, turnos y agenda en archivos de texto. */
int backup(ListaVO_Turno turnos, ListaE_Paciente pacientes, Fecha agenda[]) {
    FILE *ft = fopen("turno.txt", "w");
    FILE *fp;
    FILE *fa;
    int correcto = 1;
    int i;
    if (ft == NULL) {
        printf("No se pudo abrir turno.txt.\n");
        return 0;
    }
    fp = fopen("paciente.txt", "w");
    fa = fopen("agenda.txt", "w");
    if (fp == NULL || fa == NULL) {
        printf("No se pudieron abrir los archivos de backup.\n");
        fclose(ft);
        if (fp != NULL) fclose(fp);
        if (fa != NULL) fclose(fa);
        return 0;
    }
    resetListaVO(&turnos);
    while (!isOosListaVO(turnos)) {
        Turno t = copyListaVO(turnos);
        if (fprintf(ft, "%d|%ld|%.2f|%s|%d|%d|%d|%d|%d|%d|%c\n",
                    t.id_turno, t.dni_paciente, t.monto, t.mutual,
                    t.fecha.dia, t.fecha.mes, t.fecha.anio,
                    t.fecha.hora, t.fecha.minuto, t.estado,
                    t.fecha.disponible) < 0) {
            correcto = 0;
        }
        forwardsListaVO(&turnos);
    }
    resetListaE(&pacientes);
    while (!isOosListaE(pacientes)) {
        Paciente p;
        if (!copyListaE(pacientes, &p) ||
            fprintf(fp, "%ld|%d|%s|%s\n", p.dni, p.osocial,
                    p.nombre, p.apellido) < 0) {
            correcto = 0;
        }
        forwardsListaE(&pacientes);
    }
    for (i = 0; i < TAGENDA; i++) {
        if (fprintf(fa, "%d|%d|%d|%d|%d|%c\n",
                    agenda[i].dia, agenda[i].mes, agenda[i].anio,
                    agenda[i].hora, agenda[i].minuto,
                    agenda[i].disponible) < 0) {
            correcto = 0;
        }
    }
    if (fclose(ft) != 0) correcto = 0;
    if (fclose(fp) != 0) correcto = 0;
    if (fclose(fa) != 0) correcto = 0;
    printf(correcto ? "Backup realizado.\n" : "Error al guardar backup.\n");
    return correcto;
}

/* Consigna t: carga los tres archivos de backup. */
int cargarBackup(ListaVO_Turno *turnos, ListaE_Paciente *pacientes,
                        Fecha agenda[]) {
    FILE *ft = fopen("turno.txt", "r");
    FILE *fp = fopen("paciente.txt", "r");
    FILE *fa = fopen("agenda.txt", "r");
    ListaVO_Turno nuevosTurnos;
    ListaE_Paciente nuevosPacientes;
    Fecha nuevaAgenda[TAGENDA];
    int i, n, correcto = 1;

    if (ft == NULL || fp == NULL || fa == NULL) {
        printf("Faltan archivos de backup.\n");
        if (ft != NULL) fclose(ft);
        if (fp != NULL) fclose(fp);
        if (fa != NULL) fclose(fa);
        return 0;
    }
    initListaVO(&nuevosTurnos);
    initListaE(&nuevosPacientes);

    while (correcto) {
        Paciente p;
        n = fscanf(fp, "%ld|%d|%49[^|]|%49[^\n]\n",
                   &p.dni, &p.osocial, p.nombre, p.apellido);
        if (n == EOF) break;
        if (n != 4 || !insertListaE(&nuevosPacientes, p)) {
            correcto = 0;
            break;
        }
    }
    if (ferror(fp)) correcto = 0;

    for (i = 0; correcto && i < TAGENDA; i++) {
        int dia, mes, anio, hora, minuto;
        char disponible;
        if (fscanf(fa, "%d|%d|%d|%d|%d|%c\n",
                   &dia, &mes, &anio, &hora, &minuto, &disponible) != 6) {
            correcto = 0;
            break;
        }
        set_fecha(&nuevaAgenda[i], dia, mes, hora, minuto, disponible);
        nuevaAgenda[i].anio = anio;
    }
    if (ferror(fa)) correcto = 0;

    while (correcto) {
        int id, dia, mes, anio, hora, minuto, estado;
        long dni;
        float monto;
        char mutual[MAX_MUTUAL], disponible;
        Fecha fecha;
        Turno turno;
        n = fscanf(ft, "%d|%ld|%f|%49[^|]|%d|%d|%d|%d|%d|%d|%c\n",
                   &id, &dni, &monto, mutual, &dia, &mes, &anio,
                   &hora, &minuto, &estado, &disponible);
        if (n == EOF) break;
        if (n != 11 || id < 0 || id >= TAGENDA) {
            correcto = 0;
            break;
        }
        set_fecha(&fecha, dia, mes, hora, minuto, disponible);
        fecha.anio = anio;
        turno = crearTurno(id, dni, monto, mutual, fecha, estado);
        if (!insertListaVO(&nuevosTurnos, turno)) correcto = 0;
    }
    if (ferror(ft)) correcto = 0;

    fclose(ft);
    fclose(fp);
    fclose(fa);
    if (!correcto) {
        liberarListaVO(&nuevosTurnos);
        printf("Error al leer el backup.\n");
        return 0;
    }
    liberarListaVO(turnos);
    *turnos = nuevosTurnos;
    *pacientes = nuevosPacientes;
    for (i = 0; i < TAGENDA; i++) agenda[i] = nuevaAgenda[i];
    printf("Backup cargado.\n");
    return 1;
}

void mostrarMenu(void) {
    printf("\n=== TURNOS MEDICOS ===\n"
           " 1. Solicitar turno\n"
           " 2. Buscar fechas libres\n"
           " 3. Turnos de un paciente\n"
           " 4. Buscar fechas ocupadas\n"
           " 5. Buscar turno por ID\n"
           " 6. Confirmar turno\n"
           " 7. Cancelar turno\n"
           " 8. Proximo paciente\n"
           " 9. Mostrar todos los turnos\n"
           "10. Turnos asignados por mes\n"
           "11. Contar turnos atendidos por dia\n"
           "12. Cargar paciente\n"
           "13. Eliminar paciente\n"
           "14. Mostrar paciente\n"
           "15. Mostrar todos los pacientes\n"
           "16. Recaudacion mensual\n"
           "17. Guardar backup\n"
           "18. Cargar backup\n"
           "19. Modificar DNI de turno\n"
           "20. Modificar paciente\n"
           " 0. Salir\n");
}

/* Consignas f y o: inicia las listas y carga la agenda. */
int main(void) {
    ListaE_Paciente pacientes;
    ListaVO_Turno turnos;
    Fecha agenda[TAGENDA]; //cosita que pide el profe para que este bien que es solo esto en el main y lo demas es simplemente llenarla con las fechas libres
    int opcion;

    initListaE(&pacientes);
    initListaVO(&turnos);
    if (llenaragenda(agenda) != TAGENDA) {
        printf("No se pudo crear la agenda.\n");
        return EXIT_FAILURE;
    }
    do {
        mostrarMenu();
        if (!leerEntero("Opcion: ", &opcion)) {
            opcion = -1;
        }
        switch (opcion) {
            case 1: solicitarTurno(&pacientes, &turnos, agenda); break;
            case 2: buscarFechas(agenda, 0); break;
            case 3: {
                long dni;
                if (leerDNI("DNI: ", &dni)) {
                    mostrarTurnosPaciente(turnos, dni);
                }
                break;
            }
            case 4: buscarFechas(agenda, 1); break;
            case 5: buscarYMostrarTurno(&turnos); break;
            case 6: confirmarTurno(&pacientes, &turnos); break;
            case 7: menuCancelarTurno(&turnos, agenda); break;
            case 8: proximoPaciente(&turnos, agenda); break;
            case 9: mostrarTodosTurnos(turnos); break;
            case 10: menuAsignados(turnos); break;
            case 11: menuAtendidos(turnos); break;
            case 12: altaPaciente(&pacientes, 0); break;
            case 13: eliminarPaciente(&pacientes, turnos); break;
            case 14: consultarPaciente(pacientes, 0); break;
            case 15: consultarPaciente(pacientes, 1); break;
            case 16: calcularRecaudacion(turnos); break;
            case 17: backup(turnos, pacientes, agenda); break;
            case 18: cargarBackup(&turnos, &pacientes, agenda); break;
            case 19: modificarDniTurno(&pacientes, &turnos); break;
            case 20: modificarPaciente(&pacientes, turnos); break;
            case 0: break;
            default: printf("Opcion invalida.\n"); break;
        }
    } while (opcion != 0);

    liberarListaVO(&turnos);
    return 0;
}
