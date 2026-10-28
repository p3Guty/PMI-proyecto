#include <stdio.h>
#include <stdlib.h>
#include "fecha.h"
#include "turno.h"
#include "listaVO_turno.h"
#define Tagenda 390 //es el tamanio de la agenda, la cantidad de turnos de nov y dic.//

//---------------Para la agenda-------------//

void llenaragenda(Fecha ag[]){
    int i; //indice de la agenda                            (este tambien es el id_turno !!)
    int n=11; //mes a aplicar a los espacios//
    int d=2; //dia a aplicar a los espacios//
    int diadelasemana=1;   /// es necesario para saltear los fines de semana D:///
    int h=8; // hora a aplicar a los espacios//
    int m=00; // minutos a aplicaar a los espacios//

// inicio de la agenda //
for(i=0;i<Tagenda;i++){
    inicio(&ag[i]);
}
for(i=0; i<Tagenda;i++){
set_fecha(&ag[i], d, n, h, m, 'L');

// modificacion a las variables d(dia) y n(mes) las casillas de diciembre //
if (d>30 && n==11) {
     d = 1;
     n = 12;    // llego a diciembre, feliz navidad eeee//

//for para las horas, minutos y dias //
m+=30;
if(m==60){
    m=00;
    h++;
}
if(h==13){
    h=8;
    d++;
    diadelasemana++;
    // para hacer que no entren los sabados ni domingos)
    if(diadelasemana>5){
    diadelasemana=1;
    d= d+2;}
}

// para hacer que no entren los unicos feriados (23/11, 9/12, 25/12)//
if(d==23 && n==11 || d==9 && n==12 || d==25 && n==12){
    diadelasemana++;
    d++;
}
}
}

//                   consigna b                        //

void buscarfechalibre(Fecha agenda[]){
    printf("---A continuacion se solicitara una fecha para analizar si hay turnos disponibles.---\n");
int mesB, diaB;
printf("Ingrese el mes que desea inspeccionar (solo con ): ");
scanf("%d", mesB);

//              control antes de inspeccionar la lista              //
while(mesB != 11 && mesB != 12){
    printf("Error: no ingreso un MES valido. Intente nuevamente (solo con NOVIEMBRE o DICIEMBRE): ");
    scanf("%d", &mesB);
}
printf("Ingrese el dia que desea inspeccionar: ");
scanf("%d", &diaB);

//              control antes de inspeccionar la lista              //
if(mesB==11){
    while(diaB<1 || diaB>30){
        printf("Error: no ingreso un DIA valido. Intente nuevamente (NOVIEMBRE tiene 1-30 dias): ");
        scanf("%d", &diaB);
    }
}
else{
    while(diaB<1 || diab>31){
        printf("Error: no ingreso un DIA valido. Intente nuevamente (DICIEMBRE tiene 1-31 dias): ");
        scanf("%d", &diaB);
    }
}

int i, encontrados;
encontrados=0;
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
    printf("A continuacion ingrese un mes (11= noviembre o 12=diciembre) para buscar las fechas ocupadas del mismo: ");
    scanf("%d", &m);
    while(m != 11 && m!= 12){
        printf("Error. Intente nuevamente con 11= NOVIEMBRE o 12= DICIEMBRE: ");
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

void guardaryeliminarturnocancelado(ListaVO_turno *l, Turno t){
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
void backup(ListaVO_turno l1, ListaEPaciente l2, Fecha a[]){

//           Empezamos con turno.txt             //
    Turno t;
    FILE *ft;
    ft= fopen("turno.txt", "w");
    if(ft == NULL){
        printf("Error al crear o abrir el archivo 'turno.txt'.");
        return;
    }
    resetListaVO(l1);
    while(!isOosListaVO(l1)){
        copyListaVO(l1, &t);
        fprintf(ft, "Turno: %d.\n D.N.I. del paciente: %ld.\n Monto: %f.\n Mutual: %s.\n Fecha: %02d/%02d/%d | Hora: %02d:%02d Hs.\n Estado: %d\n %c\n\n", obtener_idTurno(t), obtener_dniPaciente(t), obtener_monto(t), t.mutual, get_dia(t.fecha), get_mes(t.fecha), get_anio(t.fecha), get_hora(t.fecha), get_minuto(t.fecha), obtener_estadoTurno(t), get_disponible(t.fecha));
        forwardsListaVO(l1);
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
    resetListaE(l2);
    while(!isOosListaE(l2)){
        copyListaE(l2, &p);
        fprintf(fp, "Nombre: %s.\n Apellido: %s.\n D.N.I: %ld.\n Obra social: %d.\n\n", p.nombre, p.apellido, obtener_dniPaciente(p), obtener_osocialPaciente(p));
        forwardsListaE(l2);
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



main(){
//--------------acá se define la agenda---------------//

Fecha agenda[Tagenda];
llenaragenda(&agenda);  // y listo ahr //


}