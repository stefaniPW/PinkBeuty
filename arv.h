#ifndef PINKBEUTY_ARV_H
#define PINKBEUTY_ARV_H
#include "produto.h"

typedef struct arv {
    Produto produto;
    struct arv *esq;
    struct arv *dir;
} Arv;

Arv* inserirID(Arv *raiz, Produto p);
Arv* inserirPreco(Arv *raiz, Produto p);
Arv* buscarID(Arv *raiz, int id);

Arv* removerID(Arv *raiz, int id);
Arv* removerPreco(Arv *raiz, float preco, int id);

void imprimirEmOrdem(Arv *raiz);
void imprimirDecrescente(Arv *raiz);
void buscarPorFaixa(Arv *raiz, float min, float max);
Produto buscarMaisProximo(Arv *raiz, float precoAlvo);

void reajustarPreco(Arv **raizID, Arv **raizPreco, int id, float novoPreco);
void removerSincronizado(Arv **raizID, Arv **raizPreco, int id);

#endif