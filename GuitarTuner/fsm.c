/*
 * fsm.c
 *
 * This file defines a finite state machine for the tuner
 */

/* Tuning states*/
typedef enum {
    ST_INIT, ST_1, ST_2, ST_3, ST_4, ST_5, ST_6;
} tuneStates;

/* Learning states */
typedef enum {
    SL_INIT, SL_1, SL_2, SL_3, SL_4, SL_5, SL_6;
} learnStates;

/* Ponteiro de função para um determinado estado */
typedef void (*Action)(unsigned char algo); //...

/* Dados e ponteiros de funções */
typedef struct FiniteStateMachine {
    tuneStates TS;
    learnStates LS;
    Action action[8];
} FSM;

/* Atributos de cada corda */
typedef struct String {
    char stringName;
    uint8_t tunedFrequency;
} STRING;
