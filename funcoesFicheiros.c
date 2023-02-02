#include <stdio.h>
#include <stdlib.h>

#include "funcoesFicheiros.h"



tipoTeste* gravaFicheiroBinario(tipoTeste *vTestes, int qntTestes) //grava informações dos testes
{
    int quantEscritaParaFicheiro;
    FILE *ficheiro;
    ficheiro=fopen("dadosTestesAg.dat","wb");
    if (ficheiro == NULL)
    {
        printf ("Erro abrir ficheiro");
    }
    else
    {

        quantEscritaParaFicheiro = fwrite(
                                       &qntTestes,
                                       sizeof(int),
                                       1,ficheiro);
        if(quantEscritaParaFicheiro != qntTestes)
        {
            printf("Erro ao escrever os dados dos membros\n");
        }
        printf("\n");
        quantEscritaParaFicheiro = fwrite(
                                       vTestes,
                                       sizeof(tipoTeste),
                                       qntTestes,ficheiro);
        if(quantEscritaParaFicheiro != qntTestes)
        {
            printf("Erro ao escrever os dados dos membros\n");
        }
        else
        {
            printf("Dados adicionados com sucesso!!");
        }


        fclose(ficheiro);
    }
}


tipoTeste* leFicheiroBinario(tipoTeste *vTestes, int *qntTestes)//lê informações dos testes
{
    int quantLeituraDeFicheiro;
    FILE *ficheiro;

    ficheiro=fopen("dadosTestesAg.dat","rb");
    if (ficheiro == NULL)
    {
        printf ("Erro abrir ficheiro");
    }
    else
    {
        quantLeituraDeFicheiro = fread(
                                     *(&qntTestes),
                                     sizeof(int),
                                     1,ficheiro);
        vTestes = realloc(vTestes, (*qntTestes)* sizeof(tipoTeste));
        if(vTestes == NULL && *qntTestes != 0)
        {
            printf("Erro ao reservar memoria");

        }
        else
        {
            if(quantLeituraDeFicheiro != 1)
            {
                printf("Erro ao obter a informacao da quantidade de testes.\n");
            }
            quantLeituraDeFicheiro = fread(
                                         vTestes,
                                         sizeof(tipoTeste),
                                         *qntTestes,ficheiro);
            if(quantLeituraDeFicheiro != *qntTestes)
            {
                printf("Erro ao obter a informacao dos membros.\n");
            }
        }

        fclose(ficheiro);

        return vTestes;
    }
}



void gravaMembrosFicheiroBinario(tipoMembro vMembros[MAX_MEMBROS], int qntMembros, int nEst, int nTec, int nFunc)//grava informações dos membros
{
    int quantEscritaParaFicheiro;
    FILE *ficheiro;
    ficheiro=fopen("dadosMembros.dat","wb");
    if (ficheiro == NULL)
    {
        printf ("Erro abrir ficheiro");
    }
    else
    {

        fwrite(&qntMembros,sizeof(int),1,ficheiro);
        fwrite(&nEst, sizeof(int),1,ficheiro);
        fwrite(&nTec, sizeof(int),1,ficheiro);
        fwrite(&nFunc, sizeof(int),1,ficheiro);


        printf("\n");
        quantEscritaParaFicheiro = fwrite(
                                       vMembros,
                                       sizeof(tipoMembro),
                                       qntMembros,ficheiro);
        if(quantEscritaParaFicheiro != qntMembros)
        {
            printf("Erro ao escrever os dados dos membros\n");
        }
        else
        {
            printf("Dados adicionados com sucesso!!");
        }


        fclose(ficheiro);
    }
}


void leMembrosFicheiroBinario(tipoMembro vMembros[MAX_MEMBROS], int *qntMembros, int *nEst, int *nTec, int *nFunc)//le informações dos membros
{
    int quantLeituraDeFicheiro;
    FILE *ficheiro;

    ficheiro=fopen("dadosMembros.dat","rb");
    if (ficheiro == NULL)
    {
        printf ("Erro abrir ficheiro");
    }
    else
    {
        quantLeituraDeFicheiro = fread(*(&qntMembros),sizeof(int),1,ficheiro);
        fread(*(&nEst),sizeof(int),1,ficheiro);
        fread(*(&nTec),sizeof(int),1,ficheiro);
        fread(*(&nFunc),sizeof(int),1,ficheiro);

        if(quantLeituraDeFicheiro != 1)
        {
            printf("Erro ao obter a informacao da quantidade de testes.\n");
        }
        quantLeituraDeFicheiro = fread(
                                     vMembros,
                                     sizeof(tipoMembro),
                                     *qntMembros,ficheiro);
        if(quantLeituraDeFicheiro != *qntMembros)
        {
            printf("Erro ao obter a informacao dos membros.\n");
        }

        fclose(ficheiro);

    }
}


