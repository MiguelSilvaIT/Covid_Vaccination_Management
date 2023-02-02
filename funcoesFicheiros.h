#ifndef FUNCOESPARAFICHEIROS_H_INCLUDED
#define FUNCOESPARAFICHEIROS_H_INCLUDED


#include "funcoesMembros.h"
#include "funcoesTestes.h"

tipoTeste* gravaFicheiroBinario(tipoTeste *vTestes, int qntTestes);
tipoTeste* leFicheiroBinario(tipoTeste *vTestes, int *qntTestes);

void leMembrosFicheiroBinario(tipoMembro vMembros[MAX_MEMBROS], int *qntMembros, int *nEst, int *nTec, int *nFunc);
void gravaMembrosFicheiroBinario(tipoMembro vMembros[MAX_MEMBROS], int qntMembros, int nEst, int nTec, int nFunc);

#endif
