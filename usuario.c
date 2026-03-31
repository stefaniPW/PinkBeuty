#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "usuario.h"

Usuario usuarios[100];
int quantidadeUsuarios = 0;

void cadastrarUsuario(Usuario* usuario){
    printf("Digite o CPF: ");
    scanf("%s", usuario.cpf);

    printf("Digite o nome: ");
    scanf("%s", usuario.nome);  

    printf("Digite a senha: ");
    scanf("%s", usuario.senha); 

    usuarios[quantidadeUsuarios++] = *usuario; // Adiciona o usuário ao array e incrementa o contador
    printf("Usuário cadastrado com sucesso!\n");
}

void listarUsuarios(Usuario* usuario, int quantidade) {
    for (int i = 0; i < quantidade; i++) {
        printf("CPF: %s\n", usuarios[i].cpf);
        printf("Nome: %s\n", usuarios[i].nome);
        printf("Senha: %s\n", usuarios[i].senha);
    }
}

void atualizarUsuario(Usuario* usuario) {
    char cpf[15];

    printf("Digite o CPF do usuário que deseja atualizar: ");
    scanf("%s", cpf);

    for (int i = 0; i < quantidadeUsuarios; i++) {
        if (strcmp(usuarios[i].cpf, cpf) == 0) {

            printf("Digite o novo nome do usuário: ");
            scanf("%s", usuarios[i].nome);

            printf("Digite a nova senha do usuário: ");
            scanf("%s", usuarios[i].senha);

            printf("Usuário atualizado com sucesso!\n");
            return;
        }
    }
    printf("Usuário não encontrado!\n");
}

void excluirUsuario(Usuario* usuario) {
    char cpf[15];

    printf("Digite o CPF do usuário que deseja excluir: ");
    scanf("%s", cpf);

    for (int i = 0; i < quantidadeUsuarios; i++) {
        if (strcmp(usuarios[i].cpf, cpf) == 0) {
            // Move os usuários seguintes para preencher a lacuna
            for (int j = i; j < quantidadeUsuarios - 1; j++) {
                usuarios[j] = usuarios[j + 1];
            }
            quantidadeUsuarios--; // Decrementa o contador de usuários
            printf("Usuário excluído com sucesso!\n");
            return;
        }
    }
    printf("Usuário não encontrado!\n");
}

