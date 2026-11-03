#include <stdio.h>
#include <stdlib.h>

/* El tipo y las declaraciones evitan incluir fecha.h*/
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
    int i; //indice de la agenda                            (este tambien es el id_turno !!)
    i = 0; // inicio de la agenda //
    FILE *fa;
fa= fopen("llenaragenda.txt", "r+");
if(fa == NULL){
    printf("Error. No se pudo abrir el archivo 'llenaragenda.txt'.\n\n");
    return 0; // fallo
}
else{
    int d, m, h, min, a;
    char dispo;

    while(i < TAGENDA && fscanf(fa, "Dia: %02d.\n Mes: %02d.\n Anio: %d.\n Horario: %02d:%02d.\n Disponibilidad: '%c'\n\n", &d, &m, &a, &h, &min, &dispo)== 6){
        set_fecha(&ag[i], d, m, h, min, dispo);
        i++;
    }
    printf("Agenda iniciada con exito.");
    fclose(fa);
}
}





