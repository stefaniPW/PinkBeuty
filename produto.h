#ifndef PINKBEUTY_PRODUTO_H
#define PINKBEUTY_PRODUTO_H

// Imagine que a Struct é o "Identidade" do produto.
// Vai ter todas as informações do produto aqui que a gente vai guardar dps
typedef struct {
    int id;          // O "Identificador" único do produto.
    char nome[50];   // O nome (batom, rímel, base, etc), com no máximo 50 letras.
    float preco;     // O valor dele.
} Produto;

// Isso aqui embaixo são os "contratos" de funções.
// O .h só fala que elas existem / vão existir , ae tem que construir elas no .c.

// Criar o produto , ae passa o id para ele alocar esse id dentro do produto.
Produto criarProduto(int id);

// Mostrar as informações do produto.
void mostrar(Produto p);

//Aqui, é só para atualizar o preço do produto, ae como a gente ta mexendo em algo que já existe
//a gente passa o "*p" que vai passar o endereço do produto , para poder alterar o que já existe.
Produto atualizarPrec(Produto *p, float novoPrec);

#endif // Termina a proteção do arquivo.