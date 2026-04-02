#include <stdio.h>
#include "arv.h"      // Importando as regras das nossas árvores (o "mapa" da loja), aqui vai puxar a árvore binária em si.
#include "produto.h"  // Importando o que define um produto (nome, preço, etc).

int main() {
    // Aqui a gente cria as duas "prateleira" vazias.
    // "NULL" significa que a prateleira acabou de ser colocada e não tem nada ainda.
    Arv *raizID = NULL;
    Arv *raizPreco = NULL;

    int opcao, idBusca;
    float novoPreco, pMin, pMax, pAlvo; // Variaveis pros novos filtros para os cosmeticos.
    Produto p;

    // Aqui é o menu, usei um do while para rodar pelo menos 1 vez.
    do {
        printf("\n--- PINKBEUTY SYSTEM ---");
        printf("\n1. Cadastrar Produto");
        printf("\n2. Buscar por ID");
        printf("\n3. Atualizar Preço (Reajuste)");
        printf("\n4. Remover Produto");
        printf("\n5. Listar tudo por Código (ID)");
        printf("\n6. Listar tudo por Valor (Preço)");
        printf("\n7. Filtrar por Faixa de Preço");
        printf("\n8. Sugestão: Preço mais próximo");
        printf("\n0. Sair");
        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {

            // CASO 1: Aqui é para cadastrar um produto da nossa loja de cosmeticos, tipo um novo batom ou rímel
            case 1:
                printf("Digite o ID do novo produto: ");
                scanf("%d", &idBusca);

                // Antes de cadastrar, a gente checa se esse ID já existe.
                // É como conferir se já não tem um produto ocupando essa "gaveta".
                if (buscarID(raizID, idBusca) != NULL) {
                    printf("Erro: Já existe um produto com o ID %d!\n", idBusca);
                } else {
                    // Se estiver livre, a gente cria o produto...
                    p = criarProduto(idBusca);

                    // e coloca ele nas DUAS prateleiras ao mesmo tempo.
                    // Se colocar em uma só, o estoque fica bagunçado!
                    // Tu pode pensar tbm, se for ajudar se como se tivesse colocando 1 no físico e 1 no digital. Como é a "mesma coisa" precisa estar "igual" nos dois lugares.
                    raizID = inserirID(raizID, p);
                    raizPreco = inserirPreco(raizPreco, p);
                    printf("\nProduto cadastrado com sucesso!");
                }
                break;

            // CASO 2: Achar um produto pelo código
            case 2:
                printf("Digite o ID para busca: ");
                scanf("%d", &idBusca);

                // Procuramos na prateleira de IDs.
                Arv *encontrado = buscarID(raizID, idBusca);

                if(encontrado)
                    mostrar(encontrado->produto); // Se achou, mostra os detalhes.
                else
                    printf("Produto nao encontrado!\n");
                break;

            // CASO 3: Mudar o preço .
            case 3:
                printf("ID do produto para reajuste: ");
                scanf("%d", &idBusca);
                printf("Novo preço: ");
                scanf("%f", &novoPreco);

                // Aqui é o remover e colocar novamente par ajustar o preço.
                reajustarPreco(&raizID, &raizPreco, idBusca, novoPreco);
                break;

            // CASO 4: Remover / deletar produto das 2 arvores.
            case 4:
                printf("ID do produto para remover: ");
                scanf("%d", &idBusca);

                //chama o removerSincronizado para as 2 ficarem sincronizadas com os itens.
                removerSincronizado(&raizID, &raizPreco, idBusca);
                break;

                // CASO 5: Mostra em ordem crescente por ID
            case 5:
                printf("\n--- CATÁLOGO POR CÓDIGO (ID) ---");
                imprimirEmOrdem(raizID); // Aqui a gente usa a árvore 1.
                break;

                // CASO 6: Mostra em ordem crescente por preço.
            case 6:
                printf("\n--- CATÁLOGO POR PREÇO ---");
                imprimirEmOrdem(raizPreco); // Aqui a gente usa a árvore 2.
                break;

                // CASO 7: aqui é para filtrar entre 2 valores tipo, produtos entre R$ 20 e R$ 100.
            case 7:
                printf("Quanto é o mínimo que quer gastar? ");
                scanf("%f", &pMin);

                printf("E o máximo? ");
                scanf("%f", &pMax);

                printf("\n--- Produtos entre R$ %.2f e R$ %.2f ---", pMin, pMax);
                buscarPorFaixa(raizPreco, pMin, pMax);
                break;

                // CASO 8: Aqui é uma busca por preço "alvo" e caso nãoi encontre mostra o com preço mais próximo.
            case 8:
                printf("Você quer um produto de qual valor? ");
                scanf("%f", &pAlvo);
                Produto prox = buscarMaisProximo(raizPreco, pAlvo);
                printf("\nO item com valor mais próximo:");
                mostrar(prox);
                break;
        }
    } while(opcao != 0); // Se digitar 0, a gente encerra o programa.

    return 0;
}