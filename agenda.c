#include <stdio.h>
#include <stdlib.h>
#include "fecha.h"

#define Tagenda 390//es el tamanio de la agenda, la cantidad de turnos de nov y dic.//

/* Consigna o: carga automatica de fechas validas en la agenda. */
//---------------Para la agenda-------------//

int llenaragenda(Fecha ag[Tagenda]){
    //indice de la agenda                            (este tambien es el id_turno !!)
    //mes a aplicar a los espacios//
    //dia a aplicar a los espacios//
    /// es necesario para saltear los fines de semana D:///
    // hora a aplicar a los espacios//
    // minutos a aplicaar a los espacios//
    // modificacion a las variables d(dia) y n(mes) las casillas de diciembre //
    // llego a diciembre, feliz navidad eeee//
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
    for (turnoDia = 0; turnoDia < Tagenda; turnoDia++) {
        inicio(&ag[turnoDia]);
    }

    for (mes = 11; mes <= 12 && cantidad < Tagenda; mes++) {
        diasMes = mes == 11 ? 30 : 31;
        for (dia = 1; dia <= diasMes && cantidad < Tagenda; dia++) {
            int feriado = (mes == 11 && dia == 23) ||
                          (mes == 12 && (dia == 9 || dia == 25));
            if (diaSemana >= 1 && diaSemana <= 5 && !feriado) {
                //for para las horas, minutos y dias //
                for (turnoDia = 0; turnoDia < 10 && cantidad < Tagenda;
                     turnoDia++) {
                    int hora = 8 + turnoDia / 2;
                    int minuto = (turnoDia % 2) * 30;
                    if (!set_fecha(&ag[cantidad], dia, mes, hora, minuto, 'L')) {
                        return 0;
                    }
                    cantidad++;
                }
            }
            // para hacer que no entren los sabados ni domingos)
            // para hacer que no entren los unicos feriados (23/11, 9/12, 25/12)//
            diaSemana = (diaSemana + 1) % 7;
        }
    }
    return cantidad;
}