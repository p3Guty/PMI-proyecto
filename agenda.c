#include <stdio.h>
#include <stdlib.h>

/* El tipo y las declaraciones evitan incluir fecha.h y duplicar sus funciones. */
typedef struct fecha {
    int dia;
    int mes;
    int anio;
    int hora;
    int minuto;
    char disponible;
} Fecha;

#define TAGENDA 390

void inicio(Fecha *p);
int set_fecha(Fecha *p, int d, int m, int h, int minuto, char dispo);

int llenaragenda(Fecha ag[TAGENDA]){
    int mes;
    int dia;
    int diaSemana = 0;
    int cantidad = 0;
    int diasMes;
    int turnoDia;

    if (ag == NULL) {
        return 0;
    }

    // inicio de la agenda //
    for (turnoDia = 0; turnoDia < TAGENDA; turnoDia++) {
        inicio(&ag[turnoDia]);
    }

    for (mes = 11; mes <= 12 && cantidad < TAGENDA; mes++) {
        diasMes = mes == 11 ? 30 : 31;
        for (dia = 1; dia <= diasMes && cantidad < TAGENDA; dia++) {
            int feriado = (mes == 11 && dia == 23) ||
                          (mes == 12 && (dia == 9 || dia == 25));
            if (diaSemana >= 1 && diaSemana <= 5 && !feriado) {
                //for para las horas, minutos y dias //
                for (turnoDia = 0; turnoDia < 10 && cantidad < TAGENDA;
                     turnoDia++) {
                    int hora = 8 + turnoDia / 2;
                    int minuto = (turnoDia % 2) * 30;
                    if (!set_fecha(&ag[cantidad], dia, mes, hora, minuto, 'L')) {
                        return 0;
                    }
                    cantidad++;
                }
            }
            diaSemana = (diaSemana + 1) % 7;
        }
    }
    return cantidad;
}
