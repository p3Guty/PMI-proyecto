#include <stdio.h>
#include <stdlib.h>
#include "fecha.h"
#include "turno.h"
#include "listaVO_turno.h"
#define Tagenda 390 //es el tamanio de la agenda, la cantidad de turnos de nov y dic.

/*---------------Para la agenda-------------*/

void llenaragenda(Fecha ag[]){
    int i; //indice de la agenda                            (este tambien es el id_turno !!)
    int n = 11; //mes a aplicar a los espacios
    int d = 2; //dia a aplicar a los espacios
    int diadelasemana = 1;   /// es necesario para saltear los fines de semana D:
    int h = 8; // hora a aplicar a los espacios
    int m = 00; // minutos a aplicaar a los espacios

    // inicio de la agenda //
    for(i = 0; i < Tagenda; i++){
        inicio(&ag[i]);
    }
    for(i = 0; i < Tagenda; i++){
        set_fecha(&ag[i], d, n, h, m, 'L');

        // modificacion a las variables d(dia) y n(mes) las casillas de diciembre //
        if (d > 30 && n == 11) {
                d = 1;
                n = 12;    // llego a diciembre, feliz navidad eeee//

            //for para las horas, minutos y dias //
            m += 30;
            if(m == 60){
                m = 00;
                h++;
            }
            if(h == 13){
                h = 8;
                d++;
                diadelasemana++;
                // para hacer que no entren los sabados ni domingos)
                if(diadelasemana > 5){
                    diadelasemana = 1;
                    d= d+2;}
            }

            // para hacer que no entren los unicos feriados (23/11, 9/12, 25/12)//
            if(d == 23 && n == 11 || d == 9 && n == 12 || d == 25 && n == 12){
                diadelasemana++;
                d++;
            }
        }
    }
}