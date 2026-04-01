//
// Created by luis-tavares on 01/04/2026.
//
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "arv.h"

Arv* criarNo(Produto p) {
    Arv *novo = (Arv*) malloc(sizeof(Arv));
    if (novo == NULL) {
        printf("Erro: Memória insuficiente!\n");
        exit(1);
    }
    novo->produto = p;
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
}

Arv* inserirID(Arv *raiz, Produto p) {
    if (raiz == NULL) return criarNo(p);

    if (p.id < raiz->produto.id)
        raiz->esq = inserirID(raiz->esq, p);
    else if (p.id > raiz->produto.id)
        raiz->dir = inserirID(raiz->dir, p);

    return raiz;
}

Arv* inserirPreco(Arv *raiz, Produto p) {
    if (raiz == NULL) return criarNo(p);

    if (p.preco < raiz->produto.preco)
        raiz->esq = inserirPreco(raiz->esq, p);
    else
        raiz->dir = inserirPreco(raiz->dir, p);

    return raiz;
}

Arv* buscarID(Arv *raiz, int id) {
    if (raiz == NULL || raiz->produto.id == id)
        return raiz;

    if (id < raiz->produto.id)
        return buscarID(raiz->esq, id);

    return buscarID(raiz->dir, id);
}

Arv* menorNo(Arv* raiz) {
    Arv* atual = raiz;
    while (atual && atual->esq != NULL)
        atual = atual->esq;
    return atual;
}

Arv* removerID(Arv *raiz, int id) {
    if (raiz == NULL) return NULL;

    if (id < raiz->produto.id)
        raiz->esq = removerID(raiz->esq, id);
    else if (id > raiz->produto.id)
        raiz->dir = removerID(raiz->dir, id);
    else {
        if (raiz->esq == NULL) {
            Arv *temp = raiz->dir;
            free(raiz);
            return temp;
        } else if (raiz->dir == NULL) {
            Arv *temp = raiz->esq;
            free(raiz);
            return temp;
        }

        Arv *temp = menorNo(raiz->dir);
        raiz->produto = temp->produto;
        raiz->dir = removerID(raiz->dir, temp->produto.id);
    }
    return raiz;
}

Arv* removerPreco(Arv *raiz, float preco, int id) {
    if (raiz == NULL) return NULL;

    if (preco < raiz->produto.preco)
        raiz->esq = removerPreco(raiz->esq, preco, id);
    else if (preco > raiz->produto.preco)
        raiz->dir = removerPreco(raiz->dir, preco, id);
    else if (id != raiz->produto.id) {
        raiz->dir = removerPreco(raiz->dir, preco, id);
    }
    else {
        if (raiz->esq == NULL) {
            Arv *temp = raiz->dir;
            free(raiz);
            return temp;
        } else if (raiz->dir == NULL) {
            Arv *temp = raiz->esq;
            free(raiz);
            return temp;
        }

        Arv *temp = menorNo(raiz->dir);
        raiz->produto = temp->produto;
        raiz->dir = removerPreco(raiz->dir, temp->produto.preco, temp->produto.id);
    }
    return raiz;
}

void reajustarPreco(Arv **raizID, Arv **raizPreco, int id, float novoPreco) {
    Arv *noProd = buscarID(*raizID, id);

    if (noProd != NULL) {
        float precoAntigo = noProd->produto.preco;

        *raizPreco = removerPreco(*raizPreco, precoAntigo, id);
        noProd->produto.preco = novoPreco;
        *raizPreco = inserirPreco(*raizPreco, noProd->produto);

        printf("Preço atualizado com sucesso!\n");
    } else {
        printf("Produto não encontrado.\n");
    }
}

void imprimirEmOrdem(Arv *raiz) {
    if (raiz != NULL) {
        imprimirEmOrdem(raiz->esq);
        mostrar(raiz->produto);
        imprimirEmOrdem(raiz->dir);
    }
}

void imprimirDecrescente(Arv *raiz) {
    if (raiz != NULL) {
        imprimirDecrescente(raiz->dir);
        mostrar(raiz->produto);
        imprimirDecrescente(raiz->esq);
    }
}

void buscarPorFaixa(Arv *raiz, float min, float max) {
    if (raiz == NULL) return;

    if (raiz->produto.preco > min)
        buscarPorFaixa(raiz->esq, min, max);

    if (raiz->produto.preco >= min && raiz->produto.preco <= max)
        mostrar(raiz->produto);

    if (raiz->produto.preco < max)
        buscarPorFaixa(raiz->dir, min, max);
}

Produto buscarMaisProximo(Arv *raiz, float precoAlvo) {
    if (raiz == NULL) {
        Produto vazio = {0, "Vazio", 0.0};
        return vazio;
    }

    Arv *atual = raiz;
    Arv *melhorNo = raiz;
    float menorDiferenca = fabs(raiz->produto.preco - precoAlvo);

    while (atual != NULL) {
        float diferencaAtual = fabs(atual->produto.preco - precoAlvo);

        if (diferencaAtual < menorDiferenca) {
            menorDiferenca = diferencaAtual;
            melhorNo = atual;
        }

        if (precoAlvo < atual->produto.preco)
            atual = atual->esq;
        else if (precoAlvo > atual->produto.preco)
            atual = atual->dir;
        else
            break;
    }
    return melhorNo->produto;
}

void removerSincronizado(Arv **raizID, Arv **raizPreco, int id) {
    Arv *alvo = buscarID(*raizID, id);

    if (alvo != NULL) {
        float precoParaRemover = alvo->produto.preco;
        *raizID = removerID(*raizID, id);
        *raizPreco = removerPreco(*raizPreco, precoParaRemover, id);
        printf("Produto %d removido com sucesso de ambas as árvores!\n", id);
    } else {
        printf("Erro: Produto com ID %d não existe.\n", id);
    }
}