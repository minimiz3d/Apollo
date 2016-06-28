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
fsm sm;

/* Inicialização da FSM */
void initFSM(fsm sm, uint8_t mode) {
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
}

/* Seleciona modo: 0 - afinação e 1 - aprendizado. */
void s0(STRING *string) {
    if (!mode)  // Tuning
        sm.state = S1;
    else        // Learning
        sm.state = S2;
}

/* Estado inicial de afinação */
void s1(STRING *string) {
	// SIMULADO
	uint8_t tuning = 2;

	selectTuning(tuning); // Define afinação (frequências desejadas).
	defineStrings(string);		// Inicializa o objeto strings com os nomes e frequï¿½ncias de cada corda.
    sm.state = S3;   // Avança na FSM.
}

/* Estado inicial de aprendizado */
void s2(STRING *string) {
    // VERIFICAR O QUE ESSE ESTADO FAZ.
    sm.state = S3;  // Avança na FSM.
}

/* Funções de estados de afinação */
void t_s3(STRING *string) {
    tuneString(string, 0);
    sm.state = S4;  // Avança na FSM.
}
void t_s4(STRING *string) {
    tuneString(string, 1);
    sm.state = S5; // Avança na FSM.
}
void t_s5(STRING *string) {
    tuneString(string, 2);
    sm.state = S6;  // Avança na FSM.
}
void t_s6(STRING *string) {
    tuneString(string, 3);
    sm.state = S7;  // Avança na FSM.
}
void t_s7(STRING *string) {
    tuneString(string, 4);
    sm.state = S8;
}
void t_s8(STRING *string) {
    tuneString(string, 5);
    done = 1;
    sm.state = S0;  // Avança na FSM.
}

/* Funções de estados de aprendizado */
void l_s3(STRING *string) {
    float frequency = detectFrequency();
    uint8_t stringNum = 0;

    saveFrequency(frequency, string, stringNum);
    sm.state = S4;  // Avança na FSM.
}
void l_s4(STRING *string) {
    float frequency = detectFrequency();
    uint8_t stringNum = 1;

    saveFrequency(frequency, string, stringNum);
    sm.state = S5;  // Avança na FSM.
}
void l_s5(STRING *string) {
    float frequency = detectFrequency();
    uint8_t stringNum = 2;

    saveFrequency(frequency, string, stringNum);
    sm.state = S6;  // Avança na FSM.
}
void l_s6(STRING *string) {
    float frequency = detectFrequency();
    uint8_t stringNum = 3;

    saveFrequency(frequency, string, stringNum);
    sm.state = S7;  // Avança na FSM.
}
void l_s7(STRING *string) {
    float frequency = detectFrequency();
    uint8_t stringNum = 4;

    saveFrequency(frequency, string, stringNum);
    sm.state = S8;  // Avança na FSM.
}
void l_s8(STRING *string) {
    float frequency = detectFrequency();
    uint8_t stringNum = 5;

    saveFrequency(frequency, string, stringNum);
    done = 1;
    sm.state = S0;  // Avança na FSM.
}
