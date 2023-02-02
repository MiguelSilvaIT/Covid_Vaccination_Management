
#ifndef FUNCOESLEITURA_H_INCLUDED
#define FUNCOESLEITURA_H_INCLUDED


#define MAX_STRING 100


typedef struct
{
    int dia;
    int mes;
    int ano;

} tipoData;


int lerInteiro(char mensagem[MAX_STRING], int minimo, int maximo);
float lerFloat(char mensagem[MAX_STRING], float minimo, float maximo);
void lerString(char mensagem[MAX_STRING], char vetorCaracteres[MAX_STRING], int maximoCaracteres);
void limpaBufferStdin(void);
tipoData lerData(void);
int lerNumUtente(char mensagem[MAX_STRING], int minimo, int maximo);


#endif
