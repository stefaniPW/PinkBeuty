//
// Created by luis-tavares on 01/04/2026.
//

#include <stdio.h>
#include <string.h>
#include "produto.h"

Produto criarProduto(int id) {
    Produto p;
    p.id = id;

    getchar(); //limpa buffer

    printf("Digite o nome do produto:");
    fgets(p.nome, 50, stdin); //utilizado fgets para pegar até maximo de 50 caracters e pegar com espaçamento

    p.nome[strcspn(p.nome, "\n")] = '\0'; //Limpeza de "\n" que o fgets pega , problema do fgets.

    printf("Digite o valor do produto");
    scanf("%f", &p.preco);

    return p;
}

void mostrar(Produto p) {
    printf("\n==========================");
    printf("\nID: %d", p.id);
    printf("\nNome: %s", p.nome);
    printf("\nPreço: R$ %.2f", p.preco);
    printf("\n==========================");

}

Produto atualizarPrec(Produto *p, float novoPrec) {
    p->preco = novoPrec;
    return *p;
}

