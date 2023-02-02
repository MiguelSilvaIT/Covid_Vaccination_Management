#ifndef FUNCOESTESTES_H_INCLUDED
#define FUNCOESTESTES_H_INCLUDED

#include "funcoesLeitura.h"
#include "funcoesMembros.h"



typedef struct
{
    char designacaoTeste[50];
    int tipoTeste;
    tipoData dataRealizacao;
    int numUtente;
    int resultado;
    int horaColheita;
    int duracao;

} tipoTeste;

tipoTeste* acrescentaTeste(tipoTeste *vTestes, int *qntTestes, int nMembros);
tipoTeste lerDadosTeste(tipoTeste *vTestes);
void mostraDadosTestes(tipoTeste *vTestes, int qntTestes);
void alteraDataTeste(tipoTeste *vTestes, int nTestes, tipoMembro vMembros[], int qntMembros);
int procuraTestes(tipoTeste *vTestes, int qntTestes, char desigTeste[50]);
void registarResultadoTeste(tipoTeste *vTestes, int nTestes, tipoMembro vMembros[], int qntMembros, int *positivos, int *inconclusivos, int *qntTestesRealizados);
void LogResultados(tipoTeste teste, tipoMembro membro);
void mostraDadosTesteIndividual(tipoTeste *vTestes, int qntTestes, int posicao, tipoMembro vMembro[MAX_MEMBROS], int nMembros);
void mostraInfoTestes(tipoMembro vMembro[], tipoTeste *vTeste, int nTestes, int nMembros, int positivos);
void estatisticas(int nEstudantes, int nDocentes, int nTecnicos, tipoTeste  *vTestes, int nTestes, int invalidos, tipoMembro vMembro[MAX_MEMBROS], int nMembros);
void membrosMenoresTestes(tipoMembro vMembro[MAX_MEMBROS], int nMembros, int nTestes);
void mostraDataTesteMaisRecente(tipoTeste *vTestes, int nTestes, tipoMembro vMembro[MAX_MEMBROS], int nMembros);
int procuraQntTestesPCR(int dia, int mes, int ano, tipoTeste *vTestes,int qntTestes, int *qntPCR);



#endif
