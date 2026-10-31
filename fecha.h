#ifndef FECHA_H_INCLUDED
#define FECHA_H_INCLUDED

#define anioo 2026

typedef struct fecha{
    int dia;
    int mes;
    int anio;
    int hora;
    int minuto;
    char disponible;
} Fecha;

void inicio(Fecha *p){
    (*p).anio = anioo;
    (*p).disponible = 'L';
    (*p).mes = 1;
    (*p).hora = 0;
    (*p).minuto = 0;
    (*p).dia = 1;
}

/*
int set_dia( Fecha *p, int d ){
    p->dia = d;
}
*/

int set_dia(Fecha *p, int d){
    int diasdelmes;     //corregir controles y agregarlos en el main
    diasdelmes=30;
    if((*p).mes == 1 || (*p).mes == 3 || (*p).mes == 5 || (*p).mes == 7 || (*p).mes == 8 || (*p).mes == 10 || (*p).mes == 12){
            diasdelmes=31;}
    else{
          if((*p).mes == 2){
                    diasdelmes=28;}
    }
    if(d>=1 && d<=diasdelmes){
            (*p).dia=d;
            return 1;
    }
    else{
    return 0;
}
}

int get_dia(Fecha p){
    return p.dia;
}

int set_mes(Fecha *p, int m){
    if(m<=12 && m>=1){
        (*p).mes= m;
        return 1;
    }
    else{
        return 0;
    }
}

int get_mes(Fecha p){
    return p.mes;
}

int set_hora(Fecha *p, int h){
    if(h>=0 && h<=23){
    (*p).hora=h;
    return 1;
    }
    else{
        return 0;
    }
    }

int get_hora(Fecha p){
    return p.hora;
}

int set_minuto(Fecha *p, int m){
    if(m == 0 || m == 30){
    (*p).minuto=m;
    return 1;
    }
    else{
        return 0;
    }
}

int get_minuto(Fecha p){
    return p.minuto;
}

int set_disponible(Fecha *p, char d){       //varios setter por corregir los controles y agregarlos en el main.c
    if(d == 'L' || d == 'O'){
            (*p).disponible= d;
            return 1;
    }
    else{
        return 0;
    }
}

int get_anio(Fecha p){
    return p.anio;
}

char get_disponible(Fecha p){
    return p.disponible;
}

int set_fecha(Fecha *p, int d, int m, int h, int minuto, char dispo){
    if(set_mes(p, m) == 0){
        return 0;
    }
    if(set_dia(p, d) == 0){
        return 0;
    }
    if(set_hora(p, h) == 0){
        return 0;
    }
    if(set_minuto(p, minuto)== 0){
        return 0;
    }
    if(set_disponible(p, dispo)== 0){
        return 0;
    }
    (*p).anio=anioo;
    return 1;
}

Fecha get_fecha (Fecha p){
    return p;
}


#endif // FECHA_H_INCLUDED
