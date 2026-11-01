#ifndef LISTAE_PACIENTES_H_INCLUDE
#define LISTAE_PACIENTES_H_INCLUDE

#include "pacientes.h"

#define MAX_PACIENTES 200

typedef struct {
    Paciente elementos[MAX_PACIENTES];
    int cant;
    int cur; 
} ListaE_Paciente;

int isOosListaE(ListaE_Paciente l);

void initListaE(ListaE_Paciente *l) {
    l->cant = 0;
    l->cur = -1;
}

int isEmptyListaE(ListaE_Paciente l) {
    return l.cant <= 0;
}

int isFullListaE(ListaE_Paciente l) {
    return l.cant >= MAX_PACIENTES;
}

void resetListaE(ListaE_Paciente *l) {
    l->cur = l->cant > 0 ? 0 : -1;
}

void forwardsListaE(ListaE_Paciente *l) {
    if (isOosListaE(*l)) {
        return;
    }
    l->cur++;

}

int isOosListaE(ListaE_Paciente l) {
    return l.cur < 0 || l.cur >= l.cant;
}

int copyListaE(ListaE_Paciente l, Paciente *destino) {;
    *destino = l.elementos[l.cur];
    return 1;
}

int insertListaE(ListaE_Paciente *l, Paciente elem) {
    l->elementos[l->cant] = elem;
    l->cant++;
    l->cur = l->cant - 1;
    return 1;
}

int suppressListaE(ListaE_Paciente *l) {
    int i;
    for (i = l->cur; i < l->cant - 1; i++) {
        l->elementos[i] = l->elementos[i + 1];
    }
    l->cant--;
    if (l->cur >= l->cant) l->cur = l->cant == 0 ? -1 : l->cant - 1;
    return 1;
}

#endif // LISTAE_PACIENTES_H_INCLUDE