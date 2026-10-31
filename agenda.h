#ifndef AGENDA_H_INCLUDED
#define AGENDA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "fecha.h"
#include "turno.h"
#include "listaVO_turno.h"
#define Tagenda 390 //es el tamanio de la agenda, la cantidad de turnos de nov y dic.

void llenaragenda(Fecha ag[]){
    int i;
    int n = 11;
    int d = 2;
    int diadelasemana = 1;
    int h = 8;
    int m = 00;

    for(i = 0; i < Tagenda; i++){
        inicio(&ag[i]);
    }
    for(i = 0; i < Tagenda; i++){
        set_fecha(&ag[i], d, n, h, m, 'L');

        if (d > 30 && n == 11) {
            d = 1;
            n = 12;

            m += 30;
            if(m == 60){
                m = 00;
                h++;
            }
            if(h == 13){
                h = 8;
                d++;
                diadelasemana++;
                if(diadelasemana > 5){
                    diadelasemana = 1;
                    d= d+2;
                }
            }

            if(d == 23 && n == 11 || d == 9 && n == 12 || d == 25 && n == 12){
                diadelasemana++;
                d++;
            }
        }
    }
}

#endif // AGENDA_H_INCLUDED
