#ifndef FUNCOESMEMBROS_H_INCLUDED
#define FUNCOESMEMBROS_H_INCLUDED

#define MAX_MEMBROS 200

#include "funcoesLeitura.h"



typedef struct
{
    int numUtente;
    char nome[100];
    int tipoMembro;
    int anoNascimento;
    int estadoVacinacao;
    int estadoConfinamento;
    tipoData dataUltimaVacina;
    int testesRealizados;
    int duracaoConfinamento;
    tipoData dataConfinamento;

} tipoMembro;

typedef struct
{
    int numUtente;
    int estadoConfinamento;
    int duracaoConfinamento;
    tipoData dataConfinamento;

} tipoConf;


tipoMembro lerDadosMembro();
void acrescentaMembro(tipoMembro vMembros[], int *qntMembros, int *nEstudantes, int *nDocentes, int *nTecnicos);
int  procuraMembros(tipoMembro vMembros[MAX_MEMBROS], int qntMembros, int numUtente);
void mostraDados(tipoMembro vMembros[MAX_MEMBROS], int qntMembros);
void registaEstadoVacinacao(tipoMembro vMembros[MAX_MEMBROS], int qntMembros, int *qntMembrosVacc);
void atualizaEstadoVacinacao(tipoMembro vMembros[MAX_MEMBROS], int qntMembros);


tipoConf* registaEstadoConfinamento(tipoConf* pConfinados, int qntMembros, int *qntConfinados, tipoMembro vMembros[MAX_MEMBROS]);
tipoConf* atualizaEstadoConfinamento(tipoConf* pConfinados, int qntMembros, int *qntConfinados, tipoMembro vMembros[MAX_MEMBROS]);
void mostraDadosConf(tipoConf* pConf, int qntConf, tipoMembro vMembros[MAX_MEMBROS], int qntMembros);



#endif
