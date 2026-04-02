#include <stdio.h>
#include <string.h> // Não esquece de incluir essa aqui pro strcspn funcionar!
#include "produto.h"

// Função para criar um produto novo.
Produto criarProduto(int id) {
    Produto p;
    p.id = id; // aqui ele guarda dentro do produto o id que a gente passou

    // Esse getchar é para limpar "sujeira" que pode ter dps de colocar id que passou antes.
    // Qualquer coisa taca no gpt para fazer uma explicação mas detalhada.
    // Mas não é mt importante de momento.
    getchar(); 

    printf("Digite o nome do produto: ");
    // Aqui eu usei o fgets para o nome do produto pq ele permite o espaço e colocar o limite até 50 caracteres
    // mais facil que o scan. Ae da para colocar tipo "Lindo Baton Vermelho da Ste"
    fgets(p.nome, 50, stdin);
    //A sintaxe do fgets é: fgets(variável onde vai guardar, tamanho máximo, de onde vem a informação),
    // stdin é o "teclado" significa para ele ler o que a gente digitar ali via teclado.

    // O fgets tem uma mania chata: ele guarda o "Enter" (\n) no final do nome. 
    // Essa linha aqui embaixo é para limpar esse problema
    p.nome[strcspn(p.nome, "\n")] = '\0'; 

    // Aqui a gente pega o preço. O %f é porque o valor tem centavos (quebrado).
    printf("Digite o valor do produto: ");
    scanf("%f", &p.preco);

    return p; // Retorna o produto como resultado da função.
}

// Função para mostrar as informações do produto.
void mostrar(Produto p) {
    printf("\n==========================");
    printf("\nID: %d", p.id);
    printf("\nNome: %s", p.nome);
    printf("\nPreço: R$ %.2f", p.preco); // O .2 faz o preço ter só 2 casas decimais.
    printf("\n==========================");
}

Produto atualizarPrec(Produto *p, float novoPrec) {
    // Aqui a gente usa o p->preco para acessar o preço do produto
    // dentro do produto original que seria a mesma coisa de fazer *p.preco.
    // podendo assim alterar o preço do produto.
    p->preco = novoPrec;
    
    return *p; // Retorna o produto com o preço atualizado.
}