#ifndef PINKBEUTY_ARV_H
#define PINKBEUTY_ARV_H
#include "produto.h" // Aqui eu to meio que passando a informação que o produto existe (o molde dele)

// Aqui é aquelas bolinhas das árvores, cada bolinha tem a informação
// e aponta ou para os menos ( esquerda ) ou para os maiores (direita).
typedef struct arv {
    Produto produto;    // O conteúdo (Batom, Rímel, etc.)
    struct arv *esq;    // Braço esquerdo: quem é "menor" vem pra cá. ⬅️
    struct arv *dir;    // Braço direito: quem é "maior" vem pra cá. ➡️
} Arv;

// Aqui ambas fazem a "mesma coisa" só que é uma pra id e outra pra preço.
// Coloca o produto na prateleira seguindo a ordem do ID (1, 2, 3...).
Arv* inserirID(Arv *raiz, Produto p);

// Coloca o mesmo produto em OUTRA prateleira, mas agora olhando o preço.
Arv* inserirPreco(Arv *raiz, Produto p);

// Vai direto ao ponto pelo código do produto.
Arv* buscarID(Arv *raiz, int id);

// Remove um produto do catálogo de IDs.
Arv* removerID(Arv *raiz, int id);

// Remove do catálogo de preços (precisa do ID pra não tirar o produto errado se os preços forem iguais).
// Tipo no ID não pode acontecer, mas aqui pode ter 2 produtos com o mesmo preço, então tem q passar algo único
// para diferenciar.
Arv* removerPreco(Arv *raiz, float preco, int id);

// Aqui é para mostar em ordem crescente.
void imprimirEmOrdem(Arv *raiz);

// Aqui lista em ordem descrescente.
void imprimirDecrescente(Arv *raiz);

// Aqui é para buscar tipo filtro
// tipo valores entre "50-100 reias"
void buscarPorFaixa(Arv *raiz, float min, float max);

// Aqui é uma mais complexa, ela procura por um preço específico, se não achar
// ela pega e mais o mais próximo por "recomendação".
Produto buscarMaisProximo(Arv *raiz, float precoAlvo);

// Se o preço mudou, precisa ajustar nas 2 arvóres.
void reajustarPreco(Arv **raizID, Arv **raizPreco, int id, float novoPreco);

// Aqui é um remover que tira das 2 árvores para ficar alinhado.
void removerSincronizado(Arv **raizID, Arv **raizPreco, int id);

#endif