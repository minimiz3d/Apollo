#include <stdio.h>
#include "guitarTuner.h"

/* Estados da tune_FSM */
typedef enum {
    ST_1, ST_2, ST_3, ST_4, ST_5, ST_6, ST_7, ST_8
} tuneStates;

/* Estados da learn_FSM */
typedef enum {
    SL_1, SL_2, SL_3, SL_4, SL_5, SL_6, SL_8
} learnStates;

/* Ponteiro de função para um determinado estado */
typedef void (*Action)(unsigned char algo); //...

/* Dados e ponteiros de funções */
typedef struct FiniteStateMachine {
    tuneStates TS;
    learnStates LS;
    Action action[8];
} FSM;

int main(int argc, char const *argv[]) {
    // Supondo selectMode() = afinação:

    /* Leitura/conversão do sinal analógico em digital */
    inputWave();

    /* Com base na representação digital do sinal obtido anteriormente, faz-se a FFT */
    defineFrequency();

    return 0;
}
