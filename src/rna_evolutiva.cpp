#include "rna_evolutiva.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void inicializa(TLista *L)
{
  int i;

  L->licoes = NULL;
  L->populacao = NULL;
  L->individuoAtual = NULL;
  L->totalIndividuos = 0;

  for (i = 0; i < MAX_Entradas; i++)
  {
    L->entradas[i] = 0;
  } // for

  L->neuronios = NULL;
  L->pesos = NULL;

  printf("\t\t=====| REDE NEURAL ARTIFICIAL EVOLUTIVA |=====");
  printf("\n\n\t\t=====| Configuracao da RNA |=====\n\n");
  printf("\tInforme o TAMANHO da POPULACAO (em termos de individuos):\n");
  printf("\t\tSugestao: 300 individuos.\n\t\tValor: ");
  scanf("%d", &L->Qtd_Populacao);

  geraIndividuos(L);

  printf("\n\n\tInforme a QUANTIDADE de GERACOES maxima:");
  printf("\n\tSugestao: 100 geracoes no total.\n\tValor: ");
  scanf("%d", &L->Total_geracoes);

  L->geracao_atual = 0;

  printf(
      "\n\n\tInforme o INTERVALO de GERACOES para a ocorrencia de MUTACOES:");
  printf(
      "\n\tSugestao: 5 (a cada 5 geracoes devem ocorrer mutacoes).\n\tValor: ");
  scanf("%d", &L->Qtd_Geracoes_para_Mutacoes);

  printf("\n\n\tInforme a QUANTIDADE de MUTACOES que devem ocorrer POR VEZ:");
  printf("\n\tSugestao: 3 mutacoes por intervalo.\n\tValor: ");
  scanf("%d", &L->Qtd_Mutacoes_por_vez);

  printf("\n\nSINAPSE THRESHOLD (Limiar das Conexoes entre Neuronios):\n");
  printf("Define a intensidade do sinal que sensibiliza cada neuronio.\n\n");
  printf("\tInforme o SINAPSE THRESHOLD:\n\tSugestao: 0.60\n\tValor: ");
  scanf("%f", &L->sinapseThreshold);

  printf("\n\nLEARNING RATE (Taxa de Aprendizado): variacao dos pesos em cada "
         "ajuste (Aprendizado).\n");
  printf("\n\tLEARNING RATE:\n\tSugestao: 0.20\n\tValor: ");
  scanf("%f", &L->learningRate);

  strcpy(L->objetivo, "Aprendizado da Funcao Logica P E Q");

  printf("\n\n\tDefinindo as LICOES a serem aprendidas pela Rede Neural "
         "Artificial.\n\n");
  geraLicoes(L);

  printf("\n\n\tDefinindo os NEURONIOS que compoem a REDE NEURAL ARTIFICIAL.");
  insereNeuronio(L, 1);
  insereNeuronio(L, 2);
  insereNeuronio(L, 3);
  insereNeuronio(L, 4);
  insereNeuronio(L, 5);

  printf("\n\n\tEstabelecendo as CONEXOES (Sinapses) entre os NEURONIOS.");
  estabelecendoSinapse(L, 1, 3, 0);
  estabelecendoSinapse(L, 1, 4, 0);
  estabelecendoSinapse(L, 2, 3, 0);
  estabelecendoSinapse(L, 2, 4, 0);
  estabelecendoSinapse(L, 3, 5, 1);
  estabelecendoSinapse(L, 4, 5, 1);

  L->fp = fopen("./output/RNA_EVOLUTIVA_RELATORIO.txt", "w");

  fprintf(L->fp, "\n\t\t=====| REDE NEURAL ARTIFICIAL EVOLUTIVA |=====\n\n");
  fprintf(L->fp, "\tOBJETIVO: %s.\n\n\tLicoes:\n", L->objetivo);
  fprintf(L->fp, "\t LICAO    P    Q  (Resultado Esperado)\n");
  fprintf(L->fp, "\t+------+----+----+---------------------+\n");

  TLicao *licao = L->licoes;
  int cont = 0;
  while (licao != NULL)
  {
    fprintf(L->fp, "\t(%d) - %d   %d   %d\n", ++cont, licao->p, licao->q,
            licao->resultadoEsperado);
    licao = licao->prox;
  } // while

  fprintf(L->fp, "\n\n");
  fprintf(L->fp, "\tLearning Rate: %.2f\n", L->learningRate);
  fprintf(L->fp, "\tSinapse Threshold: %.2f\n", L->sinapseThreshold);
  fprintf(L->fp, "\tPopulacao MAXIMA: %d.\n", L->Qtd_Populacao);
  fprintf(L->fp, "\t%d MUTACOES a cada sequencia de %d GERACOES.\n",
          L->Qtd_Mutacoes_por_vez, L->Qtd_Geracoes_para_Mutacoes);
  fprintf(L->fp, "\tTOTAL de GERACOES: %d.\n\n\n", L->Total_geracoes);

  printf("\n\n\tConfiguracao FINALIZADA!!!\n\n");
}
//====================================================
void geraIndividuos(TLista *L)
{
  TIndividuo *novo;
  int i, x;

  srand((unsigned)time(NULL));

  for (i = 0; i < L->Qtd_Populacao; i++)
  {
    novo = (TIndividuo *)malloc(sizeof(TIndividuo));

    novo->prox = NULL;
    novo->numero = i + 1;
    novo->erros = -1;

    for (x = 0; x < MAX_Pesos; x++)
    {
      novo->genes[x] = rand() % 101;
      novo->genes[x] = novo->genes[x] / 100;
    } // for

    if (L->populacao == NULL)
    {
      L->populacao = novo;
    }
    else
    {
      TIndividuo *atual = L->populacao;

      while (atual->prox != NULL)
      {
        atual = atual->prox;
      } // while

      atual->prox = novo;
    } // if

    L->totalIndividuos++;
  } // for
}
//=====================================================
void geraLicoes(TLista *L)
{
  TLicao *novo;
  int p, q;

  insereLicao(L, 0, 0, 0);
  insereLicao(L, 0, 1, 0);
  insereLicao(L, 1, 0, 0);
  insereLicao(L, 1, 1, 1);
}
//=====================================================
void insereLicao(TLista *L, int p, int q, int resultado)
{
  TLicao *novo = (TLicao *)malloc(sizeof(TLicao));

  novo->prox = NULL;
  novo->p = p;
  novo->q = q;
  novo->resultadoEsperado = resultado;

  if (L->licoes == NULL)
  {
    L->licoes = novo;
  }
  else
  {
    TLicao *atual = L->licoes;

    while (atual->prox != NULL)
    {
      atual = atual->prox;
    } // while
    atual->prox = novo;
  } // if
}
//======================================================
void insereNeuronio(TLista *L, int neuronio)
{
  TNeuronio *novo = (TNeuronio *)malloc(sizeof(TNeuronio));
  novo->prox = NULL;
  novo->neuronio = neuronio;
  novo->peso = 0;
  novo->soma = 0;

  if (L->neuronios == NULL)
  {
    L->neuronios = novo;
  }
  else
  {
    TNeuronio *atual = L->neuronios;

    while (atual->prox != NULL)
    {
      atual = atual->prox;
    } // while
    atual->prox = novo;
  } // if
}
//======================================================
int totalErros(TLista *L)
{
  int totalErros = 0;

  L->individuoAtual = L->populacao;

  while (L->individuoAtual != NULL)
  {
    if (L->individuoAtual->erros != -1)
    {
      totalErros += L->individuoAtual->erros;
    }
    else
    {
      totalErros += 1;
    }

    L->individuoAtual = L->individuoAtual->prox;
  }

  return totalErros;
}
//======================================================
void estabelecendoSinapse(TLista *L, int neuronioDe, int neuronioAte, int camada)
{
  TSinapse *novo = (TSinapse *)malloc(sizeof(TSinapse));
  TSinapse *atual;

  novo->prox = NULL;
  novo->neuronio_origem = neuronioDe;
  novo->neuronio_destino = neuronioAte;
  novo->camada = camada;
  novo->peso = 0;

  if (L->pesos == NULL)
  {
    L->pesos = novo;
  }
  else
  {
    atual = L->pesos;

    while (atual->prox != NULL)
    {
      atual = atual->prox;
    } // while
    atual->prox = novo;
  } // if
}
//=============================================================
void treinamento(TLista *L)
{
  printf("\n\n\t\t=====| INICIADO TREINAMENTO |=====\n\n");
  fprintf(L->fp, "\n\n\tINICIO DO TREINAMENTO: ");
  // ponteiro para a struct que armazena data e hora:
  struct tm *data_hora_atual;
  // variável do tipo time_t para armazenar o tempo em segundos.
  time_t segundos;
  // Obetendo o tempo em segundos.
  time(&segundos);
  // Para converter de segundos para o tempo local
  // utilizamos a função localtime().
  data_hora_atual = localtime(&segundos);

  fprintf(L->fp, "Dia: %d", data_hora_atual->tm_mday);
  fprintf(L->fp, "   Mes: %d", ((data_hora_atual->tm_mon) + 1));
  fprintf(L->fp, "   Ano: %d\n\n", (data_hora_atual->tm_year + 1900));

  fprintf(L->fp, "Dia da Semana: %d.\n", data_hora_atual->tm_wday);

  fprintf(L->fp, "%d", data_hora_atual->tm_hour);
  fprintf(L->fp, ":%d", data_hora_atual->tm_min);
  fprintf(L->fp, ":%d.\n\n", data_hora_atual->tm_sec);

  int i, file_flag = 1;
  for (i = 0; i < L->Total_geracoes; i++)
  {
    cruzamento(L);

    if ((i % L->Qtd_Geracoes_para_Mutacoes) == 0)
    {
      promoveMutacoes(L);
    } // if

    avaliacaoIndividuos(L);

    ordenamentoIndividuos(L);

    poda(L);

    if (!totalErros(L) && file_flag)
    {
      fprintf(L->fp, "\n\n\t=====| PRIMEIRA GERAÇÃO SEM ERROS: %d |=====\n\n", i + 1);
      file_flag = 0;
    }

  } // for
  //printf("\n%d\n", i);
  // Exibindo resultados do terinamento
  printf("\n\n\t\t=====| TERMINADO TREINAMENTO |=====\n\n");
  exibirPopulacao(*L);

  // Gravando resultados do terinamento
  fprintf(L->fp, "\n\n\tFIM DO TREINAMENTO: ");
  // Obetendo informações de data e hora do fim do treinamento
  // Obetendo o tempo em segundos.
  time(&segundos);
  // Para converter de segundos para o tempo local
  // utilizamos a função localtime().
  data_hora_atual = localtime(&segundos);

  fprintf(L->fp, "Dia: %d", data_hora_atual->tm_mday);
  fprintf(L->fp, "   Mes: %d", ((data_hora_atual->tm_mon) + 1));
  fprintf(L->fp, "   Ano: %d\n\n", (data_hora_atual->tm_year + 1900));

  fprintf(L->fp, "Dia da Semana: %d.\n", data_hora_atual->tm_wday);

  fprintf(L->fp, "%d", data_hora_atual->tm_hour);
  fprintf(L->fp, ":%d", data_hora_atual->tm_min);
  fprintf(L->fp, ":%d.\n\n", data_hora_atual->tm_sec);

  // Gravando resultados da populacao
  fprintf(L->fp, "\n\n\tPOPULAÇÃO AO FIM DO PROCESSO EVOLUTIVO: ");
  gravarPopulacao(*L);
}
//=============================================================
void insereIndividuo(TLista *L, TIndividuo *individuo)
{

  // Definindo o último indivíduo
  TIndividuo *atual = L->populacao;
  while (atual->prox != NULL)
    atual = atual->prox;

  (L->totalIndividuos)++;
  individuo->numero = L->totalIndividuos;
  atual->prox = individuo;
  individuo->prox = NULL;
  individuo->erros = -1;
}
//=============================================================
void cruzamento(TLista *L)
{
  /* Função responsável pelo cruzamento de individuos.
     Cada casal (selecionado por proximidade) gera dois
     descendentes. E cada descendente herda segmentos
     do código genético de seus pais.
  */
  TIndividuo
      *
          atual = L->populacao,
         **crias = (TIndividuo **)malloc(sizeof(TIndividuo *) * (L->totalIndividuos)),
         /* Array de crias para armazenar as novas crias, inseri-las direto
               na lista em tempo de criação casuaria um loop infinito porque a
               condiçãod e parada do laço que avança na lista está em função
               do tamanho atual da lista, portanto, se a lista aumenta de
               tamanho dentro desse laço, isso causa um loop infinito*/
      *cria1,
         *cria2;
  int c = 0; // c é nosso contador de crias

  // Promovendo mutações entre indivíduos por proximidade
  while (atual->prox != NULL)
  { // Optamos por não usar for para controlar o laço de repetição
    // pois, nesse caso, a condicional de repetição deveria estar
    // relacionada com o número de indivíduo pertencentes à população
    // (L->Qtd_População), porém isso nos obrigaria a distinguir a
    // paridade dessa quantidade, devido à forma como estamos
    // procedendo o pareamento para prociação. Além disso, seria
    // necessário coordenar melhor a lógica de avanço na lista (sim,
    // ainda precisaríamos dela), etnão a forma de loop em funçãod a
    // posição na lista e a distinção de crias e progenitores por
    // array parece ser a forma mais simples de resolver o problema

    // Alocando memória para as crias
    cria1 = (TIndividuo *)malloc(sizeof(TIndividuo)),
    cria2 = (TIndividuo *)malloc(sizeof(TIndividuo));

    // Populando a metade 1 da cria 1 com a metade 1 do indivíduo 1
    for (int i = 0; i < (MAX_Pesos / 2); i++)
    {
      cria1->genes[i] = atual->genes[i];
    }

    // Populando a metade 2 da cria 1 com a metade 2 do indivíduo 2
    for (int i = (MAX_Pesos / 2); i < MAX_Pesos; i++)
    {
      cria1->genes[i] =
          atual->prox->genes[i]; // O indivíduo 2 é o indivíduo imediatamente
      // após o indivíduo atual
    }

    // Populando a metade 1 da cria 2 com a metade 1 do indivíduo 2
    for (int i = 0; i < (MAX_Pesos / 2); i++)
    {
      cria2->genes[i] = atual->prox->genes[i];
    }

    // Populando a metade 2 da cria 2 com a metade 2 do indivíduo 1
    for (int i = (MAX_Pesos / 2); i < MAX_Pesos; i++)
    {
      cria2->genes[i] = atual->genes[i]; // O indivíduo 2 é o indivíduo
      // imediatamente após o indivíduo atual
    }

    // Inserindo as crias no array de crias

    crias[c] = cria1;
    c++; // Acrescendo 1 ao contador para que a cria2 seja inserida no array de
    // crias imediatamente após a cria 1
    crias[c] = cria2;
    c++; // Contador de crias ainda não foi atualizado nessa iteração do laço,
    // fazemos isso agora, pois ele não deve ser incrmentado caso o loop
    // tenha acabado ou não seja válido (o if acima checa isso nos casos de
    // números ímpares de indivíduos, enquanto a condição do laço funciona
    // de forma que isso seja tratado com indivíduos pares)

    atual = atual->prox->prox; // Avançando na lista
    if (atual == NULL)
      break;
  }

  // Inserindo cada cria do array de crias na lista
  for (int i = 0; i < c; i++)
    insereIndividuo(L, crias[i]);
  free(crias); // Como as referências de segunda ordem em relação ao vertor de
  // crias (as referências geradas pelos malloc's) já estão
  // inseridas na lista, não precisamos mais do vetor para
  // armazená-las, de forma que podemos liberá-lo. OBS.: não
  // podemos mexer no que é referenciado pelas referências que ele
  // armazena, pois agora elas são utilizadas pela lista
}
//=============================================================
void avaliacaoIndividuos(TLista *L)
{
  L->individuoAtual = L->populacao;

  while (L->individuoAtual != NULL)
  {
    L->individuoAtual->erros = 0;

    // Montando as sinapses para esse indivíduo
    TSinapse *sinAtual = L->pesos;
    for (int i = 0; sinAtual != NULL; i++)
    {
      sinAtual->peso = L->individuoAtual->genes[i];
      sinAtual = sinAtual->prox;
    }
    sinAtual = L->pesos; // Reiniciando o ponteiro de sinapses

    // Acessando as lições para avaliar o indivíduo
    TLicao *licAtual = L->licoes;
    while (licAtual != NULL)
    {

      // Montando camada 0
      TNeuronio *neuAtual = L->neuronios;
      neuAtual->peso = licAtual->p;       // Neurônio 1
      neuAtual->prox->peso = licAtual->q; // Neurônio 2

      // Calculando sinapses da camada 1
      TNeuronio *n3 = neuAtual->prox->prox; // Neurônio 3
      TNeuronio *n4 = n3->prox;             // Neurônio 4

      // Pesos das sinapses para a camada 1
      sinAtual = L->pesos;
      float peso13 = sinAtual->peso;
      sinAtual = sinAtual->prox;
      float peso14 = sinAtual->peso;
      sinAtual = sinAtual->prox;
      float peso23 = sinAtual->peso;
      sinAtual = sinAtual->prox;
      float peso24 = sinAtual->peso;
      sinAtual = sinAtual->prox;

      // Somatório para os neurônios da camada 1
      n3->soma = (neuAtual->peso * peso13) + (neuAtual->prox->peso * peso23);
      n4->soma = (neuAtual->peso * peso14) + (neuAtual->prox->peso * peso24);

      // Aplicando a função de ativação (threshold)
      n3->peso = (n3->soma >= L->sinapseThreshold) ? 1 : 0;
      n4->peso = (n4->soma >= L->sinapseThreshold) ? 1 : 0;

      // Calculando sinapses da camada 2
      TNeuronio *n5 = n4->prox; // Neurônio 5
      float peso35 = sinAtual->peso;
      sinAtual = sinAtual->prox;
      float peso45 = sinAtual->peso;

      // Somatório para o neurônio da camada 2
      n5->soma = (n3->peso * peso35) + (n4->peso * peso45);

      // Aplicando a função de ativação (threshold) para o neurônio da camada 2
      n5->peso = (n5->soma >= L->sinapseThreshold) ? 1 : 0;

      // Verificando o resultado da saída
      if (n5->peso != licAtual->resultadoEsperado)
      {
        L->individuoAtual->erros++;
      }

      licAtual = licAtual->prox;
    }

    L->individuoAtual = L->individuoAtual->prox;
  }
}
//==============================================================
void ordenamentoIndividuos(TLista *L)
{
  /* Reordena os indivíduos por ordem ascendente de erros:
     os indivíduos que cometeram menos erros deverão permanecer
     no início da Lista e os que cometeram mais erros deverão
     ficar no final da mesma Lista. */
  TIndividuo *atual, *proximo;
  int trocou;

  // Verifica se a lista está vazia ou tem apenas um elemento
  if (L->populacao == NULL || L->populacao->prox == NULL)
  {
    return;
  }

  do
  {
    trocou = 0; // Flag para indicar se houve troca nesta iteração
    atual = L->populacao;
    proximo = L->populacao->prox;

    while (proximo != NULL)
    {
      // Se o próximo indivíduo tiver menos erros que o atual, troca-os de
      // posição
      if (proximo->erros < atual->erros)
      {
        trocaIndividuos(atual, proximo);
        trocou = 1; // Indica que houve troca nesta iteração
      }
      // Move para o próximo par de indivíduos
      atual = proximo;
      proximo = proximo->prox;
    }
  } while (trocou); // Continua o loop enquanto houver trocas a serem feitas
}
//==============================================================
void trocaIndividuos(TIndividuo *a, TIndividuo *b)
{
  TIndividuo *temp = (TIndividuo *)malloc(sizeof(TIndividuo));

  temp->erros = a->erros;
  memcpy(temp->genes, a->genes, sizeof(float) * MAX_Pesos);

  a->erros = b->erros;
  memcpy(a->genes, b->genes, sizeof(float) * MAX_Pesos);

  b->erros = temp->erros;
  memcpy(b->genes, temp->genes, sizeof(float) * MAX_Pesos);

  free(temp);
}
//==============================================================
void promoveMutacoes(TLista *L)
{
  /* Altera o código genético de um número específico
     de indivíduos (= L->Qtd_Mutacoes_por_vez). */

  TIndividuo *atual = L->populacao, *inicioCrias;
  int randomI,
      *iMutacoes = (int *)malloc(sizeof(int) * L->Qtd_Mutacoes_por_vez),
      iMutacao;
  for (int i = 0; i < L->Qtd_Mutacoes_por_vez; i++)
    iMutacoes[i] = -1; // Populando a área de memeória alocada para não termos
  // probelmas de comparação

  // gerar o número correto de números de indivíduos para alterar, sendo n
  // aleatórios diferentes entre 0 e L->totalIndividuos
  srand((unsigned)time(NULL));

  for (int c = 0; c < L->Qtd_Mutacoes_por_vez; c++)
  {

    do
    {
      // Gerando um número aleatório para algum indivíduo da populaçao; nesse
      // caso, apenas filhos sofrem mutação, isso é apenas uma questão de
      // escolha para ser parecer mais com uma ocasião real
      randomI = randomInRange(L->Qtd_Populacao, L->totalIndividuos); // Gerando um número entre a
      // primeira e última cria
    } while (isInVector(randomI, iMutacoes, L->Qtd_Mutacoes_por_vez));

    iMutacoes[c] = randomI;
  }

  for (int i = 0; i < L->Qtd_Mutacoes_por_vez; i++)
  {

    atual = L->populacao;

    for (int j = 0; j < iMutacoes[i]; j++)
    {
      atual = atual->prox;
    }

    iMutacao = randomInRange(0, (MAX_Pesos - 1));
    randomInRange(0, 1) ? atual->genes[iMutacao] = atual->genes[iMutacao] + (L->learningRate) : atual->genes[iMutacao] = atual->genes[iMutacao] - (L->learningRate);

    if (atual->genes[randomI] < 0)
    {
      atual->genes[randomI] = 0;
    }
    else if (atual->genes[randomI] > 1)
    {
      atual->genes[randomI] = 1;
    }

    atual->erros = -1;
  }

  free(iMutacoes);
}
//==============================================================
int isInVector(int e, int vec[], int len)
{
  int flag = 0;

  for (int i = 0; i < len; i++)
    if (vec[i] == e)
      flag = 1;

  return flag;
}
//==============================================================
int randomInRange(int min, int max)
{
  return min + rand() % (max - min + 1);
}
//==============================================================
void poda(TLista *L)
{
  /* Elimina os indivíduos menos aptos (que estão no
     fim da Lista) até que a população volte ao seu
     Limite estabelecido na configuração inicial
     (L->Qtd_Populacao). */

  TIndividuo *atual = L->populacao;

  for (int i = 1; i < L->Qtd_Populacao; i++)
    atual = atual->prox; // Obtendo a referência para o último indivíduo da população

  // Liberando a memória a partir do indivíduo imediatamente depois da
  // referência da referência
  liberarMemListaPopulacao(atual->prox);
  atual->prox = NULL; // Indicando o novo fim da lista para o último indivíduo
  // da população
  L->totalIndividuos = L->Qtd_Populacao;
}
//==============================================================
void liberarMemListaPopulacao(TIndividuo *individuoInicial)
{ // Libera a memória alocada para todos os
  // indivíduos de uma lista que ficam após
  // uma referêncial inicial
  TIndividuo *aux;

  while (individuoInicial->prox != NULL)
  {
    aux = individuoInicial;
    individuoInicial = individuoInicial->prox;
    free(aux);
  }

  free(individuoInicial);
}
//==============================================================
void exibirPopulacao(TLista L)
{
  TIndividuo *individuoAtual = L.populacao;

  printf("\n\t\t\t=====| População |=====\n\n");

  while (individuoAtual != NULL)
  {
    printf("\tIndivíduo %d:\n", individuoAtual->numero);
    printf("\t\tGenes: [");
    for (int i = 0; i < MAX_Pesos; i++)
    {
      printf("%.2f", individuoAtual->genes[i]);
      if (i < MAX_Pesos - 1)
      {
        printf(", ");
      }
    }
    printf("]\n");
    printf("\t\tErros: %d\n", individuoAtual->erros);

    individuoAtual = individuoAtual->prox;
  }
}
//==============================================================
void gravarPopulacao(TLista L)
{

  FILE *file = L.fp;

  if (file == NULL)
  {
    printf("Erro: ponteiro de arquivo inválido.\n");
    return;
  }

  TIndividuo *individuoAtual = L.populacao;

  fprintf(file, "\n\n");

  while (individuoAtual != NULL)
  {
    fprintf(file, "\tIndivíduo %d:\n", individuoAtual->numero);
    fprintf(file, "\t\tGenes: [");
    for (int i = 0; i < MAX_Pesos; i++)
    {
      fprintf(file, "%.2f", individuoAtual->genes[i]);
      if (i < MAX_Pesos - 1)
      {
        fprintf(file, ", ");
      }
    }
    fprintf(file, "]\n");
    fprintf(file, "\t\tErros: %d\n", individuoAtual->erros);

    individuoAtual = individuoAtual->prox;
  }
}
//==============================================================
void finaliza(TLista *L)
{
  if (L != NULL)
  {
    // Liberar memória para a população
    if (L->populacao != NULL)
    {
      TIndividuo *individuoAtual = L->populacao, *auxIndividuo;

      while (individuoAtual != NULL)
      {
        auxIndividuo = individuoAtual;
        individuoAtual = individuoAtual->prox;
        free(auxIndividuo);
      }
    }

    // Liberar memória para as lições
    if (L->licoes != NULL)
    {
      TLicao *licaoAtual = L->licoes, *auxLicao;

      while (licaoAtual != NULL)
      {
        auxLicao = licaoAtual;
        licaoAtual = licaoAtual->prox;
        free(auxLicao);
      }
    }

    // Liberar memória para os neurônios
    if (L->neuronios != NULL)
    {
      TNeuronio *neuronioAtual = L->neuronios, *auxNeuronio;

      while (neuronioAtual != NULL)
      {
        auxNeuronio = neuronioAtual;
        neuronioAtual = neuronioAtual->prox;
        free(auxNeuronio);
      }
    }

    // Liberar memória para as sinapses
    if (L->pesos != NULL)
    {
      TSinapse *sinapseAtual = L->pesos, *auxSinapse;

      while (sinapseAtual != NULL)
      {
        auxSinapse = sinapseAtual;
        sinapseAtual = sinapseAtual->prox;
        free(auxSinapse);
      }
    }

    // Liberar memória para o arquivo de saída
    if (L->fp != NULL)
    {
      fclose(L->fp);
    }
  }
}
//==============================================================