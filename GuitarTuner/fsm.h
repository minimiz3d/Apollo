#ifndef FSM_H_
#define FSM_H_

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
    Action action[16];
} fsm;

/* Inicialização das FSMs */
void initTuneFSM();
void initLearnFSM();

/* Funções de estados de afinação */
void st1();
void st2();
void st3();
void st4();
void st5();
void st6();
void st7();
void st8();

/* Funções de estados de aprendizado */
void stL1();
void stL2();
void stL3();
void stL4();
void stL5();
void stL6();
void stL7();
void stL8();

#endif
