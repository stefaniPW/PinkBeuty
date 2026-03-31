#include <stdio.h>
#include "produto.h"

Poduto produtos[100]; // Array para armazenar os produtos
int quantideProdutos = 0; // Contador de produtos cadastrados
void cadastrarProduto(){
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

void listarProdutos() {
    for (int i = 0; i < quantideProdutos; i++) {
        printf ("ID: %d\n", produtos[i].id);
        printf ("Nome: %s\n", produtos[i].nome);    
        printf ("Preço: %.2f\n", produtos[i].preco);
        printf ("Estoque: %d\n", produtos[i].estoque);
    }
}
