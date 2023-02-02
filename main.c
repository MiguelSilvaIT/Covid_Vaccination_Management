#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "funcoesLeitura.h"
#include "funcoesMembros.h"
#include "funcoesTestes.h"
#include "funcoesFicheiros.h"

int menu();



int main()
{
    int opcao;
    tipoMembro vetorMembros[MAX_MEMBROS];

    int qntMembros = 0;
    int qntTestes = 0;
    int qntTestesRealizados = 0;
    int positivos = 0;
    int nEstudantes = 0;
    int nDocentes = 0;
    int nTecnicos = 0;
    int inconclusivos = 0;
    int qntConfinados = 0;
    int qntMembrosVacinados = 0;

    tipoTeste *vetorTestes = NULL;
    tipoConf *vetorConfinamentos = NULL;

    do
    {

        opcao = menu(qntMembros, qntTestesRealizados, qntTestes, qntMembrosVacinados);


        switch(opcao)
        {
        case 1:

            acrescentaMembro(vetorMembros, &qntMembros, &nEstudantes, &nDocentes, &nTecnicos);

            break;

        case 2:

            mostraDados(vetorMembros, qntMembros);

            break;

        case 3:

            registaEstadoVacinacao(vetorMembros, qntMembros, &qntMembrosVacinados);

            break;

        case 4:

            atualizaEstadoVacinacao(vetorMembros, qntMembros);

            break;

        case 5:

            vetorConfinamentos = registaEstadoConfinamento(vetorConfinamentos, qntMembros, &qntConfinados, vetorMembros);


            break;

        case 6:

            vetorConfinamentos = atualizaEstadoConfinamento(vetorConfinamentos, qntMembros, &qntConfinados, vetorMembros);

            break;

        case 7:

            vetorTestes = acrescentaTeste(vetorTestes, &qntTestes, qntMembros);

            break;

        case 8:

            mostraDadosTestes(vetorTestes, qntTestes);

            break;

        case 9:

            alteraDataTeste(vetorTestes, qntTestes, vetorMembros, qntMembros);

            break;

        case 10:

            registarResultadoTeste(vetorTestes, qntTestes, vetorMembros, qntMembros, &positivos, &inconclusivos, &qntTestesRealizados);

            break;

        case 11:

            gravaFicheiroBinario(vetorTestes, qntTestes);
            gravaMembrosFicheiroBinario(vetorMembros,  qntMembros, nEstudantes,  nTecnicos,  nDocentes);

            break;

        case 12:

            vetorTestes = leFicheiroBinario(vetorTestes, &qntTestes);
            leMembrosFicheiroBinario(vetorMembros, &qntMembros, &nEstudantes, &nTecnicos, &nDocentes);

            break;

        case 13:

            mostraInfoTestes(vetorMembros, vetorTestes, qntTestes, qntMembros,  positivos);

            break;


        case 14:

            estatisticas(nEstudantes, nDocentes, nTecnicos, vetorTestes, qntTestes, inconclusivos, vetorMembros, qntMembros);

            break;

        case 15:

            mostraDadosConf(vetorConfinamentos, qntConfinados, vetorMembros, qntMembros);

            break;


        }
    }
    while(opcao != 0);

    free(vetorConfinamentos);
    free(vetorTestes);
    return 0;
}

int menu(int qntMembros, int qntTestesRealizados, int qntTestesAgendados, int qntMembrosVacinados)
{
    int opcao;

    do
    {
        printf("\n\n\t\t\t\tMENU\n\n");
        printf("Quantidade de membros: %d\t\t\t Testes Agendados: %d\n", qntMembros, qntTestesAgendados);
        printf("Testes Realizados: %d\t\t\t\t Membros Vacinados: %d\n", qntTestesRealizados, qntMembrosVacinados);
        printf("\n\n1 - Inserir Membros\n");
        printf("2 - Listar Membros \n");
        printf("3 - Registar estado vacc.\n");
        printf("4 -  Atualizar estado vacc.\n");
        printf("5 - Registar confinamento \n");
        printf("6 - Atualizar confinamento \n");
        printf("7 - Agendar Teste \n");
        printf("8 - Listar dados dos testes \n");
        printf("9 - Alterar data de teste \n");
        printf("10 - Registar resultado de teste \n");
        printf("11 - Gravar testes agendados \n");
        printf("12 - Ler testes agendados \n");
        printf("13 - Info teste \n");
        printf("14 - Estatisticas \n");
        printf("15 - Mostrar casos confinamento \n");
        printf("0- FIM \n");

        opcao = lerInteiro("\tOpcao--> ", 0, 15);
        //limpaBufferStdin();
    }
    while (opcao < 0 || opcao > 15);
    return opcao;
}
