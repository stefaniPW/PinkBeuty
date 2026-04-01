//
// Created by luis-tavares on 01/04/2026.
//

#ifndef PINKBEUTY_PRODUTO_H
#define PINKBEUTY_PRODUTO_H

typedef struct {
    int id;
    char nome[50];
    float preco;
} Produto;

Produto criarProduto(int id);
void mostrar(Produto p);
Produto atualizarPrec(Produto *p, float novoPrec);

#endif //PINKBEUTY_PRODUTO_H