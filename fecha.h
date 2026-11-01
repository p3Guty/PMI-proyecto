#ifndef FECHA_H_INCLUDED
#define FECHA_H_INCLUDED

#define anioo 2026
#define TAGENDA 390

/* Consigna c: TDA Fecha y sus operaciones primitivas. */
typedef struct fecha{
    int dia;
    int mes;
    int anio;
    int hora;
    int minuto;
    char disponible;
} Fecha;


void inicio(Fecha *p){
    p->anio = anioo;
    p->disponible = 'L';
    p->mes = 1;
    p->hora = 0;
    p->minuto = 0;
    p->dia = 1;
}

int set_dia(Fecha *p, int d){
    p->dia = d;
    return 1;
}

int get_dia(Fecha p){
    return p.dia;
}

int set_mes(Fecha *p, int m){
    p->mes = m;
    return 1;
}

int get_mes(Fecha p){
    return p.mes;
}

int set_hora(Fecha *p, int h){
    p->hora = h;
    return 1;
}

int get_hora(Fecha p){
    return p.hora;
}

int set_minuto(Fecha *p, int m){
    p->minuto = m;
    return 1;
}

int get_minuto(Fecha p){
    return p.minuto;
}

int set_disponible(Fecha *p, char d){
    p->disponible = d;
    return 1;
}

int get_anio(Fecha p){
    return p.anio;
}

char get_disponible(Fecha p){
    return p.disponible;
}

int set_fecha(Fecha *p, int d, int m, int h, int minuto, char dispo){
    p->dia = d;
    p->mes = m;
    p->anio = anioo;
    p->hora = h;
    p->minuto = minuto;
    p->disponible = dispo;
    return 1;
}

Fecha get_fecha (Fecha p){
    return p;
}

#endif // FECHA_H_INCLUDED
