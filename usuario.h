#ifndef USUARIO_H
#define USUARIO_H

typedef struct {
    char cpf[15];
    char nome[50];
} Usuario;

void cadastrarUsuario(Usuario* usuario);
void listarUsuarios(Usuario* usuario, int quantidade);
void atualizarUsuario(Usuario* usuario);
void excluirUsuario(Usuario* usuario);
#endif // USUARIO_H
