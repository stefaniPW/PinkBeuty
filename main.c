#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "produto.h"
#include "usuario.h"

int main (){
    int opcao;
    Produto produto;
    Usuario usuario;

    do {
        printf("Menu:\n");
        printf("1. Cadastrar Produto\n");
        printf("2. Listar Produtos\n");
        printf("3. Atualizar Produto\n");
        printf("4. Excluir Produto\n");
        printf("5. Cadastrar Usuário\n");
        printf("6. Listar Usuários\n");
        printf("7. Atualizar Usuário\n");
        printf("8. Excluir Usuário\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarProduto(&produto);
                break;
            case 2:
                listarProdutos(&produto);
                break;
            case 3:
                atualizarProduto(&produto);
                break;
            case 4:
                excluirProduto(&produto);
                break;
            case 5:
                cadastrarUsuario(&usuario);
                break;
            case 6:
                listarUsuarios(&usuario, 1);
                break;
            case 7:
                atualizarUsuario(&usuario);
                break;
            case 8:
                excluirUsuario(&usuario);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}