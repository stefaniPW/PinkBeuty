#ifndef USUARIO_H
#define USUARIO_H

typedef struct {
    char cpf[15];
    char nome[50];
    char senha[20];
} Usuario;

void cadastrarUsuario(Usuario* usuario);
void listarUsuarios(Usuario* usuario, int quantidade);
void atualizarUsuario(Usuario* usuario);
void excluirUsuario(Usuario* usuario);
int login(Usuario* usuario, char* cpf, char* senha);

#endif // USUARIO_H
