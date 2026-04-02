#include <stdio.h>
#include <stdlib.h>
#include <math.h>  // Usamos para a função fabs (valor absoluto), para o preço mais próximo
#include "arv.h"

// Aqui vou criar as bolinhas.
// Cada bolinha tem um produto e aponta para os próximos produtos menores ou maiores.
Arv* criarNo(Produto p) {
    Arv *novo = (Arv*) malloc(sizeof(Arv)); // Reserva um espacinho na memória
    if (novo == NULL) {
        printf("Erro: Memória insuficiente!\n");
        exit(1);
    }
    novo->produto = p;   // Coloca o produto dentro da gaveta
    novo->esq = NULL;    // No começo, não tem nada pendurado nela
    novo->dir = NULL;    // mesma coisa aqui
    return novo;
}

// Aqui é como vai organizar a árvore binária por ID.
// Se não tiver nada, cria o primeiro nó.
// Se tiver e o ID for menor, vai para a esquerda. Se for maior, vai para a direita.
Arv* inserirID(Arv *raiz, Produto p) {
    if (raiz == NULL) return criarNo(p); // Se a prateleira tá vazia, cria o primeiro lugar

    if (p.id < raiz->produto.id)
        raiz->esq = inserirID(raiz->esq, p); // Menor? Vai pra esquerda
    else if (p.id > raiz->produto.id)
        raiz->dir = inserirID(raiz->dir, p); // Maior? Vai pra direita

    return raiz;
}
/*Teste de Mesa (tentaiva de explicação): Inserindo o ID 30

1ª Rodada: Chegamos na Raiz (ID 50)

O código pergunta: raiz == NULL? (A prateleira está vazia?)
Resposta: Não, Já tem o ID 50 lá.

O código pergunta: O ID novo (30) é menor que o ID que está lá (50)?
Resposta: Sim! (30 < 50).

Ação: O computador diz: "Amiga, desce um nível e vai olhar o que tem na esquerda do 50".
Aqui acontece a recursão: a função chama ela mesma, mas agora focando no "braço esquerdo".

2ª Rodada: Olhando a Esquerda do 50

O código pergunta: raiz == NULL? (O braço esquerdo do 50 está vazio?)
Resposta: Sim, Não tinha ninguém ali ainda.

Ação: return criarNo(p). O computador finalmente "prega" a caixinha do ID 30 ali. 🔨
O retorno: Esse novo nó (o 30) é enviado de volta para quem chamou ele.

3ª Rodada: Finalizando a Conexão

O ID 50 recebe o endereço do ID 30 e "estende o braço": raiz->esq = (ID 30).
Prontinho! Agora o 30 é oficialmente o "filho da esquerda" do 50


Resumo:
Então traduzindo, ele vai descendo para a esquerda ou direita dependendo se o
Id é maior ou menor, até encontar um lugar vazio (NULL) para colocar o novo produto.
*/


// Mesma coisa, mas agora é usando preço como parâmetro.
Arv* inserirPreco(Arv *raiz, Produto p) {
    if (raiz == NULL) return criarNo(p);

    if (p.preco < raiz->produto.preco)
        raiz->esq = inserirPreco(raiz->esq, p);
    else
        raiz->dir = inserirPreco(raiz->dir, p); // Iguais ou maiores na direita

    return raiz;
}

// Aqui ele busca por ID para achar
Arv* buscarID(Arv *raiz, int id) {
    if (raiz == NULL || raiz->produto.id == id) //aqui ele pergunta: "Amiga, você tá vazia? Ou você é o que eu tô procurando?"
 //Ae se for qualquer um dos dois casos, ele retorna a raiz (que pode ser o nó encontrado ou NULL se não achou nada).
        return raiz;

    if (id < raiz->produto.id)  //aqui ele pergunta: "O ID que eu quero é menor que o que tá aqui? Se sim, desce para a esquerda."
//ae ele vai seguindo a mesma lógica de antes do adicionar, só que agora para buscar.
        return buscarID(raiz->esq, id);

// Mesma coisa que o da esq, só que aqui não usei IF, pq se ele não caiu no primeiro e nem no da esquerda, só para ser para a direita.
    return buscarID(raiz->dir, id);
}

// Como é o menor, é sempre pra esquerda até não dar mais.
Arv* menorNo(Arv* raiz) {
    Arv* atual = raiz;
    while (atual && atual->esq != NULL)
        atual = atual->esq;
    return atual;
}

// Aqui a gente vai tirar uma bolinha. Ae quando a gente tira uma bolinha tem que colocar outra no lugar se
// a anterior tinha alguma ligação, caso só tiver para a esquerda ele coloca a bolinha da esquerda no lugar.
// mas caso tenha os dois lado pega o da direita.
// porque o da direita ? Pq ele é maior q o da esquerda atual e é menor que os proximos da direita que pode ter.
// então ele é o mais proximo do valor substituido.
Arv* removerID(Arv *raiz, int id) {
    if (raiz == NULL) return NULL;

    if (id < raiz->produto.id)
        raiz->esq = removerID(raiz->esq, id); // aqui ele vai descendo para a esquerda procurando o ID para remover
    else if (id > raiz->produto.id)
        raiz->dir = removerID(raiz->dir, id); // aqui ele vai descendo para a direita procurando o ID para remover
    else {
         // a diferença aqui do raiz->esq e do raiz->dir é que no primeiro ele tá perguntando se tem algo do lado esquerdo,
// se não tiver ele coloca o da direita no lugar, e se tiver só do lado direito ele coloca o da esquerda no lugar.
// Mas se tiver os dois lados, ele pega o menor da direita para colocar no lugar do que foi removido,
// porque ele é o mais próximo do valor removido.
        if (raiz->esq == NULL) {
            Arv *temp = raiz->dir;
            free(raiz);
            return temp;
        } else if (raiz->dir == NULL) {
            Arv *temp = raiz->esq;
            free(raiz);
            return temp;
        }

        // Caso difícil: 2 filhos. Pegamos o sucessor pra não quebrar a lógica.
        Arv *temp = menorNo(raiz->dir);
        raiz->produto = temp->produto;
        raiz->dir = removerID(raiz->dir, temp->produto.id);
    }
    return raiz;
}

// Mesma lógica do ID, mas com um detalhe extra, se tiver dois produtos com
// o mesmo preço, a gente confere o ID pra não deletar o cosmetico errado.
Arv* removerPreco(Arv *raiz, float preco, int id) {
    if (raiz == NULL) return NULL;

    if (preco < raiz->produto.preco)
        raiz->esq = removerPreco(raiz->esq, preco, id);
    else if (preco > raiz->produto.preco)
        raiz->dir = removerPreco(raiz->dir, preco, id);
    else if (id != raiz->produto.id) {
        // Preço igual mas ID diferente? Continua procurando na direita.
        raiz->dir = removerPreco(raiz->dir, preco, id);
    }
    else {
        if (raiz->esq == NULL) {
            Arv *temp = raiz->dir;
            free(raiz);
            return temp;
        } else if (raiz->dir == NULL) {
            Arv *temp = raiz->esq;
            free(raiz);
            return temp;
        }

        Arv *temp = menorNo(raiz->dir);
        raiz->produto = temp->produto;
        raiz->dir = removerPreco(raiz->dir, temp->produto.preco, temp->produto.id);
    }
    return raiz;
}

// Ae para ficar mais fácil, a gente vai remover ele da prateleira de preços,
// atualizar o preço e colocar ele de volta, porque a ordem mudou. Pois ae o inserir já coloca ele no lugar certo.
void reajustarPreco(Arv **raizID, Arv **raizPreco, int id, float novoPreco) {
    Arv *noProd = buscarID(*raizID, id);

    if (noProd != NULL) {
        float precoAntigo = noProd->produto.preco;

        *raizPreco = removerPreco(*raizPreco, precoAntigo, id);
        noProd->produto.preco = novoPreco;
        *raizPreco = inserirPreco(*raizPreco, noProd->produto);

        printf("Preço atualizado com sucesso!\n");
    } else {
        printf("Produto não encontrado.\n");
    }
}

//Mostra ordem crescente
void imprimirEmOrdem(Arv *raiz) {
    if (raiz != NULL) {
        imprimirEmOrdem(raiz->esq);
        mostrar(raiz->produto);
        imprimirEmOrdem(raiz->dir);
    }
}
//Mostra ordem decrescente
void imprimirDecrescente(Arv *raiz) {
    if (raiz != NULL) {
        imprimirDecrescente(raiz->dir);
        mostrar(raiz->produto);
        imprimirDecrescente(raiz->esq);
    }
}

// Aqui vai fazer uma busca e só mostrar o que tiver entre uma faixa de valor exemplo "20-100"
// vai mostrar produtos com preço entre 20 e 100.
void buscarPorFaixa(Arv *raiz, float min, float max) {
    if (raiz == NULL) return;

    if (raiz->produto.preco > min)
        buscarPorFaixa(raiz->esq, min, max);

    if (raiz->produto.preco >= min && raiz->produto.preco <= max)
        mostrar(raiz->produto);

    if (raiz->produto.preco < max)
        buscarPorFaixa(raiz->dir, min, max);
}

// Se a cliente quer algo de 80, mas só temos de 79 ou 85,
// aqui calcula para dar o valor mais proximo desses.
Produto buscarMaisProximo(Arv *raiz, float precoAlvo) {
    if (raiz == NULL) {
        Produto vazio = {0, "Vazio", 0.0};
        return vazio;
    }

    Arv *atual = raiz;
    Arv *melhorNo = raiz;
    float menorDiferenca = fabs(raiz->produto.preco - precoAlvo);

    while (atual != NULL) {
        float diferencaAtual = fabs(atual->produto.preco - precoAlvo);

        if (diferencaAtual < menorDiferenca) {
            menorDiferenca = diferencaAtual;
            melhorNo = atual;
        }

        if (precoAlvo < atual->produto.preco)
            atual = atual->esq;
        else if (precoAlvo > atual->produto.preco)
            atual = atual->dir;
        else
            break;
    }
    return melhorNo->produto;
}

// Delete sincronizado, para remover ambos juntos.
// usei ** porque a gente precisa alterar o ponteiro da raiz,
// e para isso tem que passar o endereço do ponteiro (ou seja, um ponteiro para ponteiro).
void removerSincronizado(Arv **raizID, Arv **raizPreco, int id) {
    Arv *alvo = buscarID(*raizID, id);

    if (alvo != NULL) {
        float precoParaRemover = alvo->produto.preco;
        *raizID = removerID(*raizID, id);
        *raizPreco = removerPreco(*raizPreco, precoParaRemover, id);
        printf("Produto %d removido com sucesso de ambas as árvores!\n", id);
    } else {
        printf("Erro: Produto com ID %d não existe.\n", id);
    }
}