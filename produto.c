#include <stdio.h>
#include "produto.h"

Poduto produtos[100];
int quantidadeProdutos = 0;

void cadastrarProduto( Produto* produto) {
    produto p;

    printf("Nome: ");
    scanf ("%s", p.nome);

    printf("Preço: ");
    scanf("%f", &p.preco);

    printf ("Estoque: ");
    scanf("%d", &p.estoque);

    p.id = quantideProdutos + 1; // Atribui um ID único ao produto
    produtos[quantideProdutos++] = p; // Adiciona o produto ao array e incrementa o contador    

    printf("Produto cadastrado com sucesso!\n");
}

void listarProdutos( Produto* produto, int quantidade) {
    for (int i = 0; i < quantidadeProdutos; i++) {
        printf ("ID: %d\n", produtos[i].id);
        printf ("Nome: %s\n", produtos[i].nome);    
        printf ("Preço: %.2f\n", produtos[i].preco);
        printf ("Estoque: %d\n", produtos[i].estoque);
    }
}

void atualizarProduto(Produto *produto) {
    int id;

    printf("Digite o ID do produto que deseja atualizar: ");
    scanf("%d", &id);

    for (int i = 0; i < quantidadeProdutos; i++) {
        if (produtos[i].id == id) {
            printf("Digite o novo nome do produto: ");
            scanf("%s", produtos[i].nome);

            printf("Digite o novo preço do produto: ");
            scanf("%f", &produtos[i].preco);

            printf("Digite o novo estoque do produto: ");
            scanf("%d", &produtos[i].estoque);

            printf("Produto atualizado com sucesso!\n");
            return;
        }
    }
    printf("Produto não encontrado!\n");
}

void excluirProduto(){
    int id;

    printf("Digite o ID do produto que deseja excluir: ");
    scanf("%d", &id);

    for (int i = 0; i < quantidadeProdutos; i++) {
        if (produtos[i].id == id) {
            // Move os produtos seguintes para preencher a lacuna
            for (int j = i; j < quantidadeProdutos - 1; j++) {
                produtos[j] = produtos[j + 1];
            }
            quantidadeProdutos--; // Decrementa o contador de produtos
            printf("Produto excluído com sucesso!\n");
            return;
        }
    }
    printf("Produto não encontrado!\n");
}

