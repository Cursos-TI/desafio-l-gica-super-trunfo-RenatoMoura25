#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_CARTAS 10
#define NUM_ATRIBUTOS 3

typedef struct {
    char nome[50];
    int atributos[NUM_ATRIBUTOS];
} Carta;

typedef struct {
    Carta cartas[NUM_CARTAS];
    int num_cartas;
} Jogador;

// Função para inicializar as cartas com valores aleatórios
void inicializar_cartas(Carta cartas[NUM_CARTAS]) {
    for (int i = 0; i < NUM_CARTAS; i++) {
        sprintf(cartas[i].nome, "Carta %d", i + 1);
        for (int j = 0; j < NUM_ATRIBUTOS; j++) {
            cartas[i].atributos[j] = rand() % 100 + 1; // Atributos de 1 a 100
        }
    }
}

// Função para exibir os atributos de uma carta
void exibir_carta(Carta carta) {
    printf("Nome: %s\n", carta.nome);
    for (int i = 0; i < NUM_ATRIBUTOS; i++) {
        printf("Atributo %d: %d\n", i + 1, carta.atributos[i]);
    }
}

// Função para distribuir cartas igualmente entre dois jogadores
void distribuir_cartas(Carta cartas[NUM_CARTAS], Jogador *jogador1, Jogador *jogador2) {
    jogador1->num_cartas = NUM_CARTAS / 2;
    jogador2->num_cartas = NUM_CARTAS / 2;

    for (int i = 0; i < NUM_CARTAS / 2; i++) {
        jogador1->cartas[i] = cartas[i];
        jogador2->cartas[i] = cartas[i + NUM_CARTAS / 2];
    }
}

// Função para executar o jogo
void jogar(Jogador *jogador1, Jogador *jogador2) {
    int turno = 0; // 0 = Jogador 1, 1 = Jogador 2

    while (jogador1->num_cartas > 0 && jogador2->num_cartas > 0) {
        Jogador *jogador_atual = (turno == 0) ? jogador1 : jogador2;
        Jogador *adversario = (turno == 0) ? jogador2 : jogador1;

        printf("\n--- Turno do Jogador %d ---\n", turno + 1);
        printf("Sua carta:\n");
        exibir_carta(jogador_atual->cartas[0]);

        int atributo_escolhido;
        printf("Escolha um atributo (1-%d): ", NUM_ATRIBUTOS);
        scanf("%d", &atributo_escolhido);
        atributo_escolhido--; // Ajusta para índice de array

        if (atributo_escolhido < 0 || atributo_escolhido >= NUM_ATRIBUTOS) {
            printf("Atributo inválido! Tente novamente.\n");
            continue;
        }

        int valor_atual = jogador_atual->cartas[0].atributos[atributo_escolhido];
        int valor_adversario = adversario->cartas[0].atributos[atributo_escolhido];

        printf("\nJogador %d escolheu o atributo %d!\n", turno + 1, atributo_escolhido + 1);
        printf("Valor do Jogador %d: %d\n", turno + 1, valor_atual);
        printf("Valor do Jogador %d: %d\n", (turno == 0) ? 2 : 1, valor_adversario);

        if (valor_atual > valor_adversario) {
            printf("Jogador %d venceu a rodada!\n", turno + 1);
            jogador_atual->cartas[jogador_atual->num_cartas] = adversario->cartas[0];
            jogador_atual->num_cartas++;
            for (int i = 0; i < adversario->num_cartas - 1; i++) {
                adversario->cartas[i] = adversario->cartas[i + 1];
            }
            adversario->num_cartas--;
        } else if (valor_atual < valor_adversario) {
            printf("Jogador %d venceu a rodada!\n", (turno == 0) ? 2 : 1);
            adversario->cartas[adversario->num_cartas] = jogador_atual->cartas[0];
            adversario->num_cartas++;
            for (int i = 0; i < jogador_atual->num_cartas - 1; i++) {
                jogador_atual->cartas[i] = jogador_atual->cartas[i + 1];
            }
            jogador_atual->num_cartas--;
        } else {
            printf("Empate! Nenhuma carta é trocada.\n");
        }

        turno = 1 - turno; // Alterna turno
    }

    printf("\n--- Fim do jogo ---\n");
    if (jogador1->num_cartas == 0) {
        printf("Jogador 2 venceu!\n");
    } else {
        printf("Jogador 1 venceu!\n");
    }
}

int main() {
    srand(time(NULL));

    Carta cartas[NUM_CARTAS];
    Jogador jogador1, jogador2;

    inicializar_cartas(cartas);
    distribuir_cartas(cartas, &jogador1, &jogador2);

    jogar(&jogador1, &jogador2);

    return 0;
}