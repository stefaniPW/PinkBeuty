#include <stdio.h>
#include "arv.h"
#include "produto.h"

int main() {
    Arv *raizID = NULL;
    Arv *raizPreco = NULL;

    int opcao, idBusca;
    float novoPreco;
    Produto p;

    do {
        printf("\n--- PINKBEUTY SYSTEM ---");
        printf("\n1. Cadastrar Produto");
        printf("\n2. Buscar por ID");
        printf("\n3. Atualizar Preço (Reajuste)");
        printf("\n0. Sair");
        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                printf("Digite o ID do novo produto: ");
                scanf("%d", &idBusca);

                if (buscarID(raizID, idBusca) != NULL) {
                    printf("Erro: Já existe um produto com o ID %d!\n", idBusca);
                } else {
                    p = criarProduto(idBusca);
                    raizID = inserirID(raizID, p);
                    raizPreco = inserirPreco(raizPreco, p);
                    printf("\nProduto cadastrado com sucesso!");
                }
                break;

            case 2:
                printf("Digite o ID para busca: ");
                scanf("%d", &idBusca);
                Arv *encontrado = buscarID(raizID, idBusca);
                if(encontrado) mostrar(encontrado->produto);
                else printf("Produto nao encontrado!\n");
                break;

            case 3:
                printf("ID do produto para reajuste: ");
                scanf("%d", &idBusca);
                printf("Novo preço: ");
                scanf("%f", &novoPreco);
                reajustarPreco(&raizID, &raizPreco, idBusca, novoPreco);
                break;

            case 4:
                printf("ID do produto para remover: ");
                scanf("%d", &idBusca);
                Arv *temp = buscarID(raizID, idBusca);
                if(temp) {
                    float pAntigo = temp->produto.preco;
                    raizID = removerID(raizID, idBusca);
                    raizPreco = removerPreco(raizPreco, pAntigo, idBusca);
                    printf("Removido com sucesso! 🗑️");
                }
                break;
        }
    } while(opcao != 0);

    return 0;
}