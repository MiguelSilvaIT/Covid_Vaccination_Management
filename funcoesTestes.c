#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "funcoesTestes.h"


tipoTeste lerDadosTeste(tipoTeste *vTestes)
{
    tipoTeste dados;

    lerString("Insira a designacao: ", dados.designacaoTeste, 50);

    dados.dataRealizacao = lerData();

    dados.tipoTeste = lerInteiro("Tipo de teste(1-ANTIGENIO 2-PCR) ", 1,2);

    dados.numUtente = lerInteiro("Numero de utente: ", 000000000,999999999);

    dados.resultado = -1;

    dados.horaColheita = -1;

    dados.duracao = -1;
    return dados;
}

tipoTeste* acrescentaTeste(tipoTeste *vTestes, int *qntTestes, int nMembros)
{
    tipoTeste *pAux;
    tipoTeste dados;
    tipoTeste infoTeste;
    int qntTestesPCR = 0;


    pAux = vTestes;
    if(nMembros == 0)
    {
        printf("Ainda nao existem membros!!");
    }
    else
    {
        dados = lerDadosTeste( vTestes);
        vTestes = realloc(vTestes, (*qntTestes+1)*sizeof(tipoTeste));
        if(vTestes == NULL)
        {
            printf("Erro, impossivel inserir o teste");
            vTestes = pAux;
        }
        else
        {
            infoTeste = dados;
            if(infoTeste.tipoTeste == 2)
            {
                procuraQntTestesPCR(infoTeste.dataRealizacao.dia, infoTeste.dataRealizacao.mes, infoTeste.dataRealizacao.ano, vTestes, *qntTestes, &qntTestesPCR);

            }
            if(qntTestesPCR == -1)
            {
                printf("Nao é possivel inserir mais testes PCR para este dia");
            }
            else
            {
                vTestes[*qntTestes] = dados;
                (*qntTestes)++;
            }

        }

    }

    return vTestes;
}

void mostraDadosTestes(tipoTeste *vTestes, int qntTestes)
{
    int i;




    if (qntTestes == 0)
    {
        printf("\n\nAinda nao foram agendados testes!\n\n");
    }
    else
    {

        printf("\n\n CodTeste      tipo de teste            data de realização   \t numUtente     resultado      horaColheita    duracao\n");
        for (i=0; i<qntTestes; i++)
        {
            char infoTipoTeste[50] = "Antigenio";
            char infoResultado[50] = "Positivo";

            //transforma o resultado numa stirng
            if(vTestes[i].resultado == 2)
            {
                strcpy(infoResultado, "Negativo");
            }
            else
            {
                if(vTestes[i].resultado == 3)
                {
                    strcpy(infoResultado, "Invalido");
                }
            }

            //transforma o tipoTeste numa stirng
            if(vTestes[i].tipoTeste == 2)
            {
                strcpy(infoTipoTeste, "PCR");
            }

            if(vTestes[i].resultado != -1)
            {
                printf("%-4s \t\t%-6s  \t\t%2d-%2d-%4d \t\t%-9d \t %-10s\t%-3d \t\t%-2d \n",
                       vTestes[i].designacaoTeste,
                       infoTipoTeste,
                       vTestes[i].dataRealizacao.dia,
                       vTestes[i].dataRealizacao.mes,
                       vTestes[i].dataRealizacao.ano,
                       vTestes[i].numUtente,
                       infoResultado,
                       vTestes[i].horaColheita,
                       vTestes[i].duracao);
            }
            else
            {

                printf(" %-4s \t\t%-6s  \t\t%2d-%2d-%4d     %-9d \tPOR REALIZAR \n",
                       vTestes[i].designacaoTeste,
                       infoTipoTeste,
                       vTestes[i].dataRealizacao.dia,
                       vTestes[i].dataRealizacao.mes,
                       vTestes[i].dataRealizacao.ano,
                       vTestes[i].numUtente);
            }

        }
    }
}

void alteraDataTeste(tipoTeste *vTestes, int nTestes, tipoMembro vMembros[], int qntMembros)
{
    int numUtente;
    int posicaoMembro;
    int posicaoTeste;
    char desigTeste[50];

    if(nTestes == 0)
    {
        printf("Ainda nao forma inseridos testes");
    }
    else
    {
        numUtente = lerInteiro("Numero de utente: ", 000000000,999999999);

        posicaoMembro = procuraMembros(vMembros, qntMembros, numUtente);
        if( posicaoMembro == -1)
        {
            printf("O utente nao existe!!");
        }
        else
        {
            lerString("Designacao do teste: ", desigTeste, 50);
            posicaoTeste = procuraTestes(vTestes, nTestes, desigTeste);

            if(posicaoTeste == -1)
            {
                printf("Nao existe teste com esse codigo!!");
            }
            else
            {
                vTestes[posicaoTeste].dataRealizacao =lerData();
            }

        }

    }
}




int procuraTestes(tipoTeste *vTestes, int qntTestes, char desigTeste[50])
{
    int i, posicao;
    posicao = -1;
    int compara;



    for(i=0; i<qntTestes; i++)
    {

        compara = strcmp(desigTeste, vTestes[i].designacaoTeste);
        if(compara == 0)
        {
            posicao = i;
            i = qntTestes;
        }
    }
    return posicao;
}

void registarResultadoTeste(tipoTeste *vTestes, int nTestes, tipoMembro vMembros[], int qntMembros, int *positivos, int *inconclusivo, int *qntTestesRealizados)
{
    int numUtente;
    char desigTeste[50];
    int posicaoTeste;
    int posicaoMembro;
    tipoData dataTeste;

    if(nTestes == 0)
    {
        printf("Ainda nao forma inseridos testes");
    }
    else
    {
        numUtente = lerInteiro("Numero de utente: ", 000000000,999999999);
        posicaoMembro = procuraMembros(vMembros, qntMembros, numUtente);

        if(posicaoMembro == -1)
        {
            printf("O numero de utente nao existe");
        }
        else
        {
            lerString("Designacao de teste: ", desigTeste, 50);
            posicaoTeste = procuraTestes(vTestes, nTestes, desigTeste);

            if(posicaoTeste == -1)
            {
                printf("Nao existe teste com esse codigo!!");

            }
            else
            {
                vTestes[posicaoTeste].resultado = lerInteiro("Resultado (1-Positivo 2-Negativo 3-Invalido): ", 1, 3);

                vTestes[posicaoTeste].horaColheita = lerInteiro("Insira a hora de colheita", 0, 23);

                vTestes[posicaoTeste].duracao = lerInteiro("Insira a duraçao(min)", 0, 60);

                (vMembros[posicaoMembro].testesRealizados)++;

                LogResultados(vTestes[posicaoTeste], vMembros[posicaoMembro]);

                if(vTestes[posicaoTeste].resultado == 1)
                {
                    (*positivos)++;
                }
                else
                {
                    if(vTestes[posicaoTeste].resultado == 3)
                    {
                        (*inconclusivo)++;
                    }
                }
                (*qntTestesRealizados)++;
            }

        }
    }

}


void LogResultados(tipoTeste teste, tipoMembro membro)
{
    FILE *ficheiro;
    ficheiro = fopen("logResultados.txt","a");
    char resultado[50] = "Positivo";
    if (ficheiro == NULL)
    {
        perror("Erro na abertura do ficheiro.");
    }
    else
    {
        //transforma o resultado numa stirng
        if(teste.resultado == 2)
        {
            strcpy(resultado, "Negativo");
        }
        else
        {
            if(teste.resultado == 3)
            {
                strcpy(resultado, "Invalido");
            }
        }

        fprintf(ficheiro,"\n Resultado: %s\t  %d dose    %s   %d    %d  ",
                membro.nome,
                membro.estadoVacinacao,
                resultado,
                teste.horaColheita,
                teste.duracao);
    }

    fclose(ficheiro);
}

void mostraInfoTestes(tipoMembro vMembro[], tipoTeste *vTeste, int nTestes, int nMembros, int positivos)
{

    int posicao;
    char desigTeste[50];


    if(nTestes == 0)
    {
        printf("Ainda nao foram agendados testes!");
    }
    else
    {
        lerString("Insira a desiganacao do teste: ", desigTeste, 50);
        posicao = procuraTestes(vTeste, nTestes, desigTeste);

        if(posicao == -1)
        {
            printf("A designacao que inseriu nao e valida!");
        }
        else
        {
            mostraDadosTesteIndividual(vTeste, nTestes, posicao, vMembro, nMembros);
        }
    }

}
void mostraDadosTesteIndividual(tipoTeste *vTestes, int qntTestes, int posicao, tipoMembro vMembro[MAX_MEMBROS], int nMembros)
{
    int i;
    int posicaoMembro;
    char infoTipoMembro[50] = "Estudante";
    char infoEstadoConf[50] = "N/Confinado";
    char infoTipoTeste[50] = "Antigenio";
    char infoResultado[50] = "Positivo";

    posicaoMembro = procuraMembros(vMembro,nMembros, vTestes[posicao].numUtente);

    //transforma o codigo de membro numa string
    if(vMembro[posicao].tipoMembro == 2)
    {
        strcpy(infoTipoMembro, "Docente");
    }
    else
    {
        if(vMembro[posicao].tipoMembro == 3)
        {
            strcpy(infoTipoMembro, "Tecnico");
        }

    }


    //transforma o codigo de confinamento numa string
    if(vMembro[posicao].estadoConfinamento == 2)
    {
        strcpy(infoEstadoConf, "Quarentena");
    }
    else
    {
        if(vMembro[posicao].estadoConfinamento == 3)
        {
            strcpy(infoEstadoConf, "Isolamento");
        }

    }

    //transforma o resultado numa string
    if(vTestes[posicao].resultado == 2)
    {
        strcpy(infoResultado, "Negativo");
    }
    else
    {
        if(vTestes[posicao].resultado == 3)
        {
            strcpy(infoResultado, "Invalido");
        }
    }

    //transforma o tipoTeste numa string
    if(vTestes[posicao].tipoTeste == 2)
    {
        strcpy(infoTipoTeste, "PCR");
    }

    if (qntTestes == 0)
    {
        printf("\n\nAinda nao foram agendados testes!\n\n");
    }

    else
    {
        printf("\n\n Designacao    tipo de teste   data de realização   \t numUtente   resultado   hora Colheita   duracao nomeMembro   tipo de membro\n");



        if(vTestes[posicao].resultado != -1)
        {

            printf("  %s \t \t%s \t\t%2d-%2d-%4d\t\t%-9d    %-9s \t\t%-3d    \t%-2d\t %s     %-14s \n",
                   vTestes[posicao].designacaoTeste,
                   infoTipoTeste,
                   vTestes[posicao].dataRealizacao.dia,
                   vTestes[posicao].dataRealizacao.mes,
                   vTestes[posicao].dataRealizacao.ano,
                   vTestes[posicao].numUtente,
                   infoResultado,
                   vTestes[posicao].horaColheita,
                   vTestes[posicao].duracao,
                   vMembro[posicaoMembro].nome,
                   infoTipoMembro);

        }
        else
        {
            printf("  %s \t\t %-10s  \t\t %2d-%2d-%4d \t   %-9d POR REALIZAR \n",
                   vTestes[posicao].designacaoTeste,
                   infoTipoTeste,
                   vTestes[posicao].dataRealizacao.dia,
                   vTestes[posicao].dataRealizacao.mes,
                   vTestes[posicao].dataRealizacao.ano,
                   vTestes[posicao].numUtente,
                   vTestes[posicao].resultado,
                   vTestes[posicao].horaColheita,
                   vTestes[posicao].duracao);
        }
    }
}

void estatisticas(int nEstudantes, int nDocentes, int nTecnicos, tipoTeste  *vTestes, int nTestes, int invalidos, tipoMembro vMembro[MAX_MEMBROS], int nMembros)
{
    float tempMedRealTeste;
    int somaTempTeste;
    float percInvalidos;

    int i;
    for(i = 0; i <nTestes; i++)
    {
        somaTempTeste += vTestes[i].duracao;
    }


    tempMedRealTeste = (float)somaTempTeste / nTestes;

    percInvalidos = (float)invalidos * 100/ nTestes;

    printf("Qnt. Estudantes: %d\n", nEstudantes);
    printf("Qnt. Docentes: %d\n", nDocentes);
    printf("Qnt. Tecnicos: %d\n", nTecnicos);
    printf("Tempo Medio de Realizacao de um teste: %.2f\n", tempMedRealTeste);
    printf("Percentagem Testes Invalidos: %.2f\n", percInvalidos);
    membrosMenoresTestes(vMembro, nMembros, nTestes);

    printf("Teste realizado mais recentemente: \n");
    mostraDataTesteMaisRecente(vTestes, nTestes, vMembro, nMembros);

}

void membrosMenoresTestes(tipoMembro vMembro[MAX_MEMBROS], int nMembros, int nTestes)
{
    int i;
    int j;
    int k;
    int menor = vMembro[0].testesRealizados;
    int vMembrosMenores[nTestes];
    int tamanhoVetorMenor;

    for(i = 0; i < nMembros; i++)
    {
        if(vMembro[i].testesRealizados <= menor)
        {
            menor = vMembro[i].testesRealizados;
        }
    }


    printf("Membro(s) com menor numero de testes: \n");
    for(k = 0; k < nMembros ; k++)
    {
        if (vMembro[k].testesRealizados == menor)
        {
            printf("%d \n", vMembro[k].numUtente);
        }

    }


}

void mostraDataTesteMaisRecente(tipoTeste *vTestes, int nTestes, tipoMembro vMembro[MAX_MEMBROS], int nMembros)
{
    int anoMaior = vTestes[0].dataRealizacao.ano;
    int i;
    char desigTesteMaisRecente[50];
    int posicao;

    for(i = 0; i < nTestes; i++)
    {
        if(vTestes[i].dataRealizacao.ano >= anoMaior)
        {
            anoMaior = vTestes[i].dataRealizacao.ano;

        }
    }

    int mesMaior = vTestes[0].dataRealizacao.mes;

    for(i = 0; i < nTestes; i++)
    {
        if(vTestes[i].dataRealizacao.ano == anoMaior)
        {

            if(vTestes[i].dataRealizacao.mes >= mesMaior)
            {
                mesMaior = vTestes[i].dataRealizacao.mes;
            }
        }
    }

    int diaMaior = vTestes[0].dataRealizacao.dia;

    for(i = 0; i < nTestes; i++)
    {
        if(vTestes[i].dataRealizacao.ano == anoMaior && vTestes[i].dataRealizacao.mes == mesMaior)
        {

            if(vTestes[i].dataRealizacao.dia >= diaMaior)
            {
                diaMaior = vTestes[i].dataRealizacao.dia;
            }
        }
    }


    int horaMaior = vTestes[0].horaColheita;

    for(i = 0; i < nTestes; i++)//estrutura para encontrar
    {
        if(vTestes[i].dataRealizacao.ano == anoMaior && vTestes[i].dataRealizacao.mes == mesMaior && vTestes[i].dataRealizacao.dia == diaMaior)
        {

            if(vTestes[i].horaColheita >= horaMaior)
            {
                horaMaior = vTestes[i].horaColheita;
            }
        }
    }


    for(i=0 ; i < nTestes; i++)//estrutura para inserir no array as datas mais recentes
    {
        if(vTestes[i].dataRealizacao.ano == anoMaior && vTestes[i].dataRealizacao.mes == mesMaior && vTestes[i].dataRealizacao.dia == diaMaior && vTestes[i].horaColheita)
        {

            strcpy(desigTesteMaisRecente,  vTestes[i].designacaoTeste);
        }
    }

    posicao = procuraTestes(vTestes, nTestes, desigTesteMaisRecente);

    mostraDadosTesteIndividual(vTestes, nTestes, posicao, vMembro,nMembros);
}

int procuraQntTestesPCR(int dia, int mes, int ano, tipoTeste *vTestes,int qntTestes, int *qntPCR)
{
    int i = 0;
    for(i = 0; i < qntTestes; i++)
    {
        if(vTestes[i].dataRealizacao.dia == dia && vTestes[i].dataRealizacao.ano == ano && vTestes[i].dataRealizacao.mes == mes)//verifica de existe uma data igual à inserida
        {

            if(vTestes[i].tipoTeste == 2 && *qntPCR <= 15)//caso exista verifica se tem testes PCR associados
            {

                (*qntPCR)++; //aumenta o valor da qnt de PCR´s
            }
            else
            {

                *qntPCR = -1;//caso seja maior que 16 retorna o valor "-1"
            }
        }
    }
}
