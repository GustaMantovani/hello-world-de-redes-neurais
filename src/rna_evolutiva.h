#ifndef rna_evolutiva_h
#define rna_evolutiva_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_Entradas 2
#define MAX_Pesos 6

typedef char string[60];

typedef struct tipoLicao
{
    int p;                 // proposição P
    int q;                 // Proposição Q
    int resultadoEsperado; // Proposição Composta P "E" Q (A Classe)
    tipoLicao *prox;
} TLicao;

typedef struct tipoIndividuo
{
    float genes[MAX_Pesos];
    int erros;
    int numero; // numero identificador
    tipoIndividuo *prox;
} TIndividuo;

typedef struct tipoSinapse
{
    int camada;
    int neuronio_origem;
    int neuronio_destino;
    float peso;
    tipoSinapse *prox;
} TSinapse;

typedef struct tipoNeuronio
{
    int neuronio;
    float soma;
    float peso;
    tipoNeuronio *prox;
} TNeuronio;

typedef struct tipoLista
{
    FILE *fp; // Arquivo de Saída (Relatório).
    string objetivo;
    TLicao *licoes; // Conjunto de lições a serem aprendidas
    float entradas[MAX_Entradas];
    TNeuronio *neuronios;
    TSinapse *pesos;
    TIndividuo *populacao;
    TIndividuo *individuoAtual;
    int totalIndividuos;
    int Qtd_Populacao;
    int Qtd_Mutacoes_por_vez;
    int Total_geracoes;
    int geracao_atual;
    int Qtd_Geracoes_para_Mutacoes;
    float sinapseThreshold;
    float learningRate;
} TLista;

void inicializa(TLista *L);
void geraIndividuos(TLista *L);
void geraLicoes(TLista *L);
void insereLicao(TLista *L, int p, int q, int resultado);
void insereNeuronio(TLista *L, int neuronio);
void estabelecendoSinapse(TLista *L, int neuronioDe, int neuronioAte, int camada);
void treinamento(TLista *L);
void insereIndividuo(TLista *L, TIndividuo *individuo);
void cruzamento(TLista *L);
void avaliacaoIndividuos(TLista *L);
void ordenamentoIndividuos(TLista *L);
void trocaIndividuos(TIndividuo *a, TIndividuo *b);
void promoveMutacoes(TLista *L);
int isInVector(int e, int vec[], int len);
int randomInRange(int min, int max);
void poda(TLista *L);
void liberarMemListaPopulacao(TIndividuo *individuoInicial);
void exibirPopulacao(TLista L);
void gravarPopulacao(TLista L);
void finaliza(TLista *L);
int totalErros(TLista *L);

#endif