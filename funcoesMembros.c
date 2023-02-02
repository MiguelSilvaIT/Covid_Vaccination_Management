#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "funcoesMembros.h"


tipoMembro lerDadosMembro()
{
    tipoMembro dados;

    dados.numUtente = lerNumUtente("Numero de utente: ", 000000000,999999999);

    lerString("Nome: ", dados.nome, MAX_STRING);

    dados.tipoMembro = lerInteiro("Tipo de Membro(1- Estudante 2-Docente 3-Tecnico)", 1, 3);

    dados.anoNascimento = lerInteiro("Ano de nascimento", 1900, 2021);

    return dados;
}

void acrescentaMembro(tipoMembro vMembros[], int *qntMembros, int *nEstudantes, int *nDocentes, int *nTecnicos)
{
    tipoMembro infoMembro;
    int posicao;

    printf("\n ACRESCENTA Membro\n");

    if (*qntMembros == MAX_MEMBROS)
    {
        printf("Nao e possivel adicionar mais membros!!");
    }
    else
    {
        infoMembro = lerDadosMembro();
        posicao = procuraMembros(vMembros, *qntMembros, infoMembro.numUtente);
        if( posicao == -1)
        {
            vMembros[*qntMembros] = infoMembro;
            vMembros[*qntMembros].estadoVacinacao = 0;
            vMembros[*qntMembros].estadoConfinamento = 1;
            vMembros[*qntMembros].testesRealizados = 0;

            switch(vMembros[*qntMembros].tipoMembro)
            {
            case 1:
                (*nEstudantes)++;
                break;

            case 2:
                (*nDocentes)++;
                break;

            case 3:
                (*nTecnicos)++;
                break;
            }
            (*qntMembros)++;
        }

        else
        {
            printf("Numero de utente ja foi inserido anteriormente!!\n");
        }

    }
}

int procuraMembros(tipoMembro vMembros[MAX_MEMBROS], int qntMembros, int numUtente)
{
    int i, posicao;
    posicao = -1;

    for(i=0; i<qntMembros; i++)
    {
        if(vMembros[i].numUtente == numUtente)
        {
            posicao = i;
            i = qntMembros;
        }
    }
    return posicao;
}

void mostraDados(tipoMembro vMembros[MAX_MEMBROS], int qntMembros)
{



    int i;

    if (qntMembros == 0)
    {
        printf("\n\nAinda nao foram inseridos membros!\n\n");
    }
    else
    {
        printf("\n\n Numero Utente      nome            tipoMembro   \t anoNascimento   estado Vacinacao      dataUltimaVacina    estado confinamento\n");
        for (i=0; i<qntMembros; i++)
        {
            char infoTipoMembro[50] = "Estudante";
            char infoEstadoConf[50] = "N/Confinado";

            //transforma o codigo de membro numa string
            if(vMembros[i].tipoMembro == 2)
            {
                strcpy(infoTipoMembro, "Docente");
            }
            else
            {
                if(vMembros[i].tipoMembro == 3)
                {
                    strcpy(infoTipoMembro, "Tecnico");
                }

            }
            //transforma o codigo de confinamento numa string
            if(vMembros[i].estadoConfinamento == 2)
            {
                strcpy(infoEstadoConf, "Quarentena");
            }
            else
            {
                if(vMembros[i].estadoConfinamento == 3)
                {
                    strcpy(infoEstadoConf, "Isolamento");
                }

            }



            if(vMembros[i].estadoVacinacao == 1 || vMembros[i].estadoVacinacao == 2 || vMembros[i].estadoVacinacao == 3) //verifica se o membro já se encontra vacinado
            {
                printf("\t%-12d%-16s%-14s \t   %-4d\t \t\t%-3d dose\t\t%2d-%2d-%4d\t   %-6s \n",
                       vMembros[i].numUtente,
                       vMembros[i].nome,
                       infoTipoMembro,
                       vMembros[i].anoNascimento,
                       vMembros[i].estadoVacinacao,
                       vMembros[i].dataUltimaVacina.dia,
                       vMembros[i].dataUltimaVacina.mes,
                       vMembros[i].dataUltimaVacina.ano,
                       infoEstadoConf);
            }
            else
            {
                printf("\t%-12d%-16s%-14s \t   %-4d \t   POR VACINAR \t\tPOR VACINAR  \t   %s  \n",
                       vMembros[i].numUtente,
                       vMembros[i].nome,
                       infoTipoMembro,
                       vMembros[i].anoNascimento,
                       infoEstadoConf);
            }

        }
    }
}


void registaEstadoVacinacao(tipoMembro vMembros[MAX_MEMBROS], int qntMembros, int *qntMembrosVacc)
{

    int numUtente;
    int posicao;
    int infoEstado;

    if(qntMembros == 0)
    {
        printf("Ainda nao foram adicionados membros!\n\n");
    }
    else
    {

        numUtente = lerInteiro("Numero de utente: ", 000000000,999999999);

        posicao = procuraMembros(vMembros, qntMembros, numUtente);
        if( posicao == -1)
        {
            printf("Numero de utente nao encontrado!!");
        }
        else
        {


            if(vMembros[posicao].estadoVacinacao != 0)
            {
                printf("Estado de vacinacao ja registado!!\n Dirija-se ao separador'Atualizar Estado'");
            }
            else
            {
                infoEstado = lerInteiro("Insira o estado de vacinacao(0-s/vacina 1-dose1 2-dose2 3-dose3)", 0, 3);

                if(infoEstado <= vMembros[posicao].estadoVacinacao)
                {
                    printf("Estado de vacinacao invalido");
                }
                else
                {
                    if(vMembros[posicao].estadoVacinacao == 0)
                    {
                        (*qntMembrosVacc)++;
                    }

                    vMembros[posicao].estadoVacinacao = infoEstado;
                    vMembros[posicao].dataUltimaVacina= lerData();
                }
            }
        }

    }

}

void atualizaEstadoVacinacao(tipoMembro vMembros[MAX_MEMBROS], int qntMembros)
{

    int numUtente;
    int posicao;

    if (qntMembros == 0)
    {
        printf("\n\nAinda nao foram inseridos membros!\n\n");
    }
    else
    {
        numUtente = lerInteiro("Numero de utente: ", 000000000,999999999);

        posicao = procuraMembros(vMembros, qntMembros, numUtente);
        if(vMembros[posicao].estadoVacinacao == 0)
        {
            printf("Estado de vacinacao por registar!");
        }
        else
        {

            if( posicao == -1)
            {
                printf("Numero de utente nao encontrado!!");
            }
            else
            {
                if(vMembros[posicao].estadoVacinacao == 3)
                {
                    printf("O membro selecionado ja tem as 3 doses da vacina");
                }
                else
                {
                    vMembros[posicao].estadoVacinacao= lerInteiro("Insira o estado de vacinacao(0-s/vacina 1-dose1 2-dose2 3-dose3)", 0, 3);
                    if(vMembros[posicao].estadoVacinacao != 0)
                    {
                        vMembros[posicao].dataUltimaVacina= lerData();
                    }


                }
            }
        }
    }
}

tipoConf* registaEstadoConfinamento(tipoConf* pConfinados, int qntMembros, int *qntConfinados, tipoMembro vMembros[MAX_MEMBROS])
{

    tipoConf *pAux;
    int numUtente;
    int posicao;
    int estadoConfTemp;

    pAux = pConfinados;

    if(qntMembros == 0)
    {
        printf("Ainda nao foram inseridos membros");
    }
    else
    {
        numUtente = lerInteiro("Numero de utente: ", 000000000,999999999);
        posicao = procuraMembros(vMembros, qntMembros, numUtente);
        if( posicao == -1)
        {
            printf("Numero de utente nao encontrado!!");
        }
        else
        {

            estadoConfTemp = lerInteiro("Insira o estado de confinamento\n"
                                        "( 1-N/confinado 2-Quarentena 3-Isolamento profilactico)", 1, 3);
            //caso o estado de confinamento seja 1(n/confinado) n é necessario armazenar dados de confinamento
            if(estadoConfTemp != 1)
            {
                pConfinados = realloc(pConfinados, ((*qntConfinados)+1)*sizeof(tipoConf) );
                if(pConfinados == NULL)
                {
                    printf("Erro- Impossivel reservar memoria");
                    pConfinados = pAux;
                }
                pConfinados[*qntConfinados].estadoConfinamento= estadoConfTemp;

                pConfinados[*qntConfinados].dataConfinamento = lerData();

                pConfinados[*qntConfinados].duracaoConfinamento = lerInteiro("Duracao do confinamento", 0,30);

                pConfinados[*qntConfinados].numUtente =  vMembros[posicao].numUtente;

                vMembros[posicao].estadoConfinamento = pConfinados[*qntConfinados].estadoConfinamento;

                (*qntConfinados)++;
            }
            else
            {
                vMembros[posicao].estadoConfinamento = estadoConfTemp;
            }
        }
    }

    return pConfinados;
}

tipoConf* atualizaEstadoConfinamento(tipoConf* pConfinados, int qntMembros, int *qntConfinados, tipoMembro vMembros[MAX_MEMBROS])
{

    tipoConf *pAux;
    int numUtente;
    int posicao;
    int estadoConfTemp;

    pAux = pConfinados;

    if(qntMembros == 0)
    {
        printf("Ainda nao foram inseridos membros");
    }
    else
    {
        numUtente = lerInteiro("Numero de utente: ", 000000000,999999999);
        posicao = procuraMembros(vMembros, qntMembros, numUtente);
        if( posicao == -1)
        {
            printf("Numero de utente nao encontrado!!");
        }
        else
        {

            estadoConfTemp = lerInteiro("Insira o estado de confinamento\n"
                                        "( 1-N/confinado 2-Quarentena 3-Isolamento profilactico)", 1, 3);
            if(estadoConfTemp != 1)
            {
                pConfinados = realloc(pConfinados, ((*qntConfinados)+1)*sizeof(tipoConf) );
                if(pConfinados == NULL)
                {
                    printf("Erro- Impossivel reservar memoria");
                    pConfinados = pAux;
                }
                pConfinados[*qntConfinados].estadoConfinamento= estadoConfTemp;

                pConfinados[*qntConfinados].dataConfinamento = lerData();

                pConfinados[*qntConfinados].duracaoConfinamento = lerInteiro("Duracao do confinamento", 0,30);

                pConfinados[*qntConfinados].numUtente =  vMembros[posicao].numUtente;

                vMembros[posicao].estadoConfinamento = pConfinados[*qntConfinados].estadoConfinamento;

                (*qntConfinados)++;
            }
            else
            {
                vMembros[posicao].estadoConfinamento = estadoConfTemp;
            }
        }
    }

    return pConfinados;
}

void mostraDadosConf(tipoConf* pConf, int qntConf, tipoMembro vMembros[MAX_MEMBROS], int qntMembros)
{
    int i;
    int posicao;


    if (qntMembros == 0)
    {
        printf("\n\nAinda nao foram inseridos membros!\n\n");
    }
    else
    {
        printf("\n\n Numero Utente      nome            tipoMembro   \t tipo Confinamento   dataConfinamento     duracao\n");
        for (i=0; i<qntConf; i++)
        {
            char infoTipoMembro[50] = "Estudante";
            char infoEstadoConf[50] = "N/Confinado";

            //transforma o codigo de membro numa string
            if(vMembros[i].tipoMembro == 2)
            {
                strcpy(infoTipoMembro, "Docente");
            }
            else
            {
                if(vMembros[i].tipoMembro == 3)
                {
                    strcpy(infoTipoMembro, "Tecnico");
                }

            }
            //transforma o codigo de confinamento numa string
            if(vMembros[i].estadoConfinamento == 2)
            {
                strcpy(infoEstadoConf, "Quarentena");
            }
            else
            {
                if(vMembros[i].estadoConfinamento == 3)
                {
                    strcpy(infoEstadoConf, "Isolamento");
                }

            }



            posicao = procuraMembros(vMembros, qntMembros, pConf[i].numUtente);

            printf("%-9d\t  %-16s \t%-10s \t %-10s\t  \t%2d-%2d-%4d \t   %-3d\n",
                   pConf[i].numUtente,
                   vMembros[posicao].nome,
                   infoTipoMembro,
                   infoEstadoConf,
                   pConf[i].dataConfinamento.dia,
                   pConf[i].dataConfinamento.mes,
                   pConf[i].dataConfinamento.ano,
                   pConf[i].duracaoConfinamento);

        }
    }
}

