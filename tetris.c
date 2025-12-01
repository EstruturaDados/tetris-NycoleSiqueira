#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

// Desafio Tetris Stack
// Tema 3 - Integração de Fila e Pilha
// Este código segue a organização oficial do template fornecido.

// ============================================================================
// 🧩 Nível Novato: Fila de Peças Futuras
//
// - Struct Peca com tipo (char) e id (int)
// - Fila circular com capacidade para 5 peças
// - Funções: inicializarFila(), enqueue(), dequeue(), filaCheia(), filaVazia()
// - Geração automática de peças com tipo aleatório e id sequencial
// - Exibir a fila com mostrarFila()
// - Menu:
//        1 - Jogar peça (dequeue)
//        0 - Sair
// - Após cada remoção, inserir automaticamente nova peça (enqueue)
// ============================================================================

#define TAM_FILA 5

// ---------------------------
// Estrutura de uma peça
// ---------------------------
typedef struct {
    char tipo;   // 'I', 'O', 'T', 'L'
    int  id;     // identificador único
} Peca;

// ---------------------------
// Fila circular de peças
// ---------------------------
typedef struct {
    Peca itens[TAM_FILA];
    int frente;
    int tras;
    int quantidade;
} Fila;

// ---------------------------
// Protótipos
// ---------------------------
void inicializarFila(Fila *f);
bool filaCheia(Fila *f);
bool filaVazia(Fila *f);
bool enqueue(Fila *f, Peca p);
bool dequeue(Fila *f);
Peca gerarPeca(int idAtual);
void mostrarFila(Fila *f);

void executarNivelNovato();

// ============================================================================
// MAIN
// ============================================================================
int main() {

    // Apenas executa o nível Novato (fila)
    executarNivelNovato();

    return 0;
}

// ============================================================================
// Implementações
// ============================================================================

// Inicializa a fila vazia
void inicializarFila(Fila *f) {
    f->frente = 0;
    f->tras = -1;
    f->quantidade = 0;
}

// Verifica se está cheia
bool filaCheia(Fila *f) {
    return f->quantidade == TAM_FILA;
}

// Verifica se está vazia
bool filaVazia(Fila *f) {
    return f->quantidade == 0;
}

// Gera automaticamente uma peça aleatória
Peca gerarPeca(int idAtual) {
    char tipos[] = {'I', 'O', 'T', 'L'};
    Peca nova;
    nova.tipo = tipos[rand() % 4];
    nova.id = idAtual;
    return nova;
}

// Insere peça no final (enqueue)
bool enqueue(Fila *f, Peca p) {
    if (filaCheia(f)) {
        printf("\n⚠️  Fila cheia! Não é possível inserir.\n");
        return false;
    }

    f->tras = (f->tras + 1) % TAM_FILA;
    f->itens[f->tras] = p;
    f->quantidade++;
    return true;
}

// Remove da frente (dequeue)
bool dequeue(Fila *f) {
    if (filaVazia(f)) {
        printf("\n⚠️  Fila vazia! Nada a remover.\n");
        return false;
    }

    Peca removida = f->itens[f->frente];
    printf("\nPeça jogada: [%c %d]\n", removida.tipo, removida.id);

    f->frente = (f->frente + 1) % TAM_FILA;
    f->quantidade--;

    return true;
}

// Mostra a fila atual
void mostrarFila(Fila *f) {
    printf("\n=== FILA DE PEÇAS ===\n");

    if (filaVazia(f)) {
        printf("(vazia)\n");
        return;
    }

    int i = f->frente;
    for (int c = 0; c < f->quantidade; c++) {
        printf("[%c %d] ", f->itens[i].tipo, f->itens[i].id);
        i = (i + 1) % TAM_FILA;
    }

    printf("\n");
}

// ============================================================================
// Função principal do nível Novato
// ============================================================================
void executarNivelNovato() {
    Fila fila;
    inicializarFila(&fila);

    int contadorID = 0;
    int opcao;

    srand(time(NULL));

    // Preenche a fila inicial com 5 peças
    for (int i = 0; i < TAM_FILA; i++) {
        enqueue(&fila, gerarPeca(contadorID++));
    }

    do {
        mostrarFila(&fila);

        printf("\nOpções:\n");
        printf("1 - Jogar peça (dequeue)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                if (dequeue(&fila)) {
                    enqueue(&fila, gerarPeca(contadorID++)); // repõe a peça
                }
                break;

            case 0:
                printf("\nSaindo...\n");
                break;

            default:
                printf("\nOpção inválida!\n");
        }

    } while (opcao != 0);
}
