#include "rna_evolutiva.h"

TLista lista;

int main()
{
  inicializa(&lista);
  treinamento(&lista);
  finaliza(&lista);
  return 0;
}