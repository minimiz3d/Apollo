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
typedef void (*Action)(STRING *string);

/* Dados e ponteiros de funções */
typedef struct FSM {
	States state;
	Action action[15];
} fsm;

extern volatile fsm sm;

/* Inicialização da FSMs */
void initFSM(fsm sm, uint8_t mode);

/* Estados iniciais */
void s0(STRING *string);
void s1(STRING *string);
void s2(STRING *string);

/* Tuning */
void t_s3(STRING *string);
void t_s4(STRING *string);
void t_s5(STRING *string);
void t_s6(STRING *string);
void t_s7(STRING *string);
void t_s8(STRING *string);

/* Learning */
void l_s3(STRING *string);
void l_s4(STRING *string);
void l_s5(STRING *string);
void l_s6(STRING *string);
void l_s7(STRING *string);
void l_s8(STRING *string);

#endif
