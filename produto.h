#ifndef PRODUTOS_H
#define PRODUTOS_H

typedef struct {
    int id;
    char nome[50];
    float preco;
} Produto;

void cadastrarProduto(Produto*   produto);   
void listarprodutos(Produto* produto, int quantidade); 
void atualizarProduto(Produto* produto);
void excluirProduto(Produto* produto);  

#endif // PRODUTOS_H