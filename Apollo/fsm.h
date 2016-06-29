#ifndef FSM_H_
#define FSM_H_

#include "tuner.h"

/* Variáveis utilizadas */
extern uint8_t mode;
extern uint8_t done;

/* Todos estados utilizados */
typedef enum {
	S0, S1, S2, S3, S4, S5, S6, S7, S8
} States;

/* Ponteiro de função para um determinado estado */
typedef void (*Action)();

/* Dados e ponteiros de funções */
typedef struct FSM {
	States state;
	Action action[15];
} fsm;

extern volatile fsm sm;

/* Inicialização da FSMs */
void initFSM(fsm sm, uint8_t mode);

/* Estados iniciais */
void s0();
void s1();
void s2();

/* Tuning */
void t_s3();
void t_s4();
void t_s5();
void t_s6();
void t_s7();
void t_s8();

/* Learning */
void l_s3();
void l_s4();
void l_s5();
void l_s6();
void l_s7();
void l_s8();

#endif
