/*
 * fsm.c
 *
 * This file defines a finite state machine for the tuner
 */

#include "fsm.h"
#include "tuner.h"

/* Variáveis utilizadas */
uint8_t mode;
uint8_t done;
volatile fsm sm;
STRING string[6];

/* Inicialização da FSM */
void initFSM() {
	sm.state = S0;								// Estado inicial.

    /* Estados inicias */
    sm.action[S0] = s0;
    sm.action[S1] = s1;
    sm.action[S2] = s2;

    if (!mode) {    // Afinação
        sm.action[S3] = t_s3;
        sm.action[S4] = t_s4;
        sm.action[S5] = t_s5;
        sm.action[S6] = t_s6;
        sm.action[S7] = t_s7;
        sm.action[S8] = t_s8;
    }

    else {          // Aprendizado
        sm.action[S3] = l_s3;
        sm.action[S4] = l_s4;
        sm.action[S5] = l_s5;
        sm.action[S6] = l_s6;
        sm.action[S7] = l_s7;
        sm.action[S8] = l_s8;
    }

	sm.action[sm.state](); // Vai para a função do próximo estado.
}

/* Seleciona modo: 0 - afinação e 1 - aprendizado. */
void s0() {
    defineStrings();		// Inicializa o objeto strings com os nomes e frequï¿½ncias de cada corda.

	if (!mode)  // Tuning
        sm.state = S1;
    else        // Learning
        sm.state = S2;

	sm.action[sm.state](); // Vai para a função do próximo estado.
}

/* Estado inicial de afinação */
void s1() {
	// SIMULADO
	uint8_t tuning = 0;

	configMotor();

	selectTuning(tuning); // Define afinação (frequências desejadas).
    sm.state = S3;   // Avança na FSM.
    sm.action[sm.state](); // Vai para a função do próximo estado.
}


/* Estado inicial de aprendizado */
void s2() {
    // VERIFICAR O QUE ESSE ESTADO FAZ.
    sm.state = S3;  // Avança na FSM.
    sm.action[sm.state](); // Vai para a função do próximo estado.
}

/* Funções de estados de afinação */
void t_s3() {
    tuneString(0);
    sm.state = S4;  // Avança na FSM.
    sm.action[sm.state](); // Vai para a função do próximo estado.
}
void t_s4() {
    tuneString(1);
    sm.state = S5; // Avança na FSM.
    sm.action[sm.state](); // Vai para a função do próximo estado.
}
void t_s5() {
    tuneString(2);
    sm.state = S6;  // Avança na FSM.
    sm.action[sm.state](); // Vai para a função do próximo estado.
}
void t_s6() {
    tuneString(3);
    sm.state = S7;  // Avança na FSM.
    sm.action[sm.state](); // Vai para a função do próximo estado.
}
void t_s7() {
    tuneString(4);
    sm.state = S8;
    sm.action[sm.state](); // Vai para a função do próximo estado.
}
void t_s8() {
    tuneString(5);
    done = 1;
    sm.state = S0;  // Avança na FSM.
    sm.action[sm.state](); // Vai para a função do próximo estado.
}

/* Funções de estados de aprendizado */
void l_s3() {
    float frequency = detectFrequency();
    uint8_t stringNum = 0;

    saveFrequency(frequency, stringNum);
    sm.state = S4;  // Avança na FSM.
    sm.action[sm.state](); // Vai para a função do próximo estado.
}
void l_s4() {
    float frequency = detectFrequency();
    uint8_t stringNum = 1;

    saveFrequency(frequency, stringNum);
    sm.state = S5;  // Avança na FSM.
    sm.action[sm.state](); // Vai para a função do próximo estado.
}
void l_s5() {
    float frequency = detectFrequency();
    uint8_t stringNum = 2;

    saveFrequency(frequency, stringNum);
    sm.state = S6;  // Avança na FSM.
    sm.action[sm.state](); // Vai para a função do próximo estado.
}
void l_s6() {
    float frequency = detectFrequency();
    uint8_t stringNum = 3;

    saveFrequency(frequency, stringNum);
    sm.state = S7;  // Avança na FSM.
    sm.action[sm.state](); // Vai para a função do próximo estado.
}
void l_s7() {
    float frequency = detectFrequency();
    uint8_t stringNum = 4;

    saveFrequency(frequency, stringNum);
    sm.state = S8;  // Avança na FSM.
    sm.action[sm.state](); // Vai para a função do próximo estado.
}
void l_s8() {
    float frequency = detectFrequency();
    uint8_t stringNum = 5;

    saveFrequency(frequency, stringNum);
    done = 1;
    sm.state = S0;  // Avança na FSM.
    sm.action[sm.state](); // Vai para a função do próximo estado.
}
