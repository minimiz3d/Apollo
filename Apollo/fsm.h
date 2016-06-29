/** @file fsm.h
 *  @brief Protótipo de funções utilizadas na máquina de estados finitos (FSM).
 *  @author Árthur Pinheiro
 *  @author Gabriel de Jesus
 */

#ifndef FSM_H_
#define FSM_H_

#include "tuner.h"

/**
 *	@brief Declaração de variáveis compartilhadas.
 *
 *	Cada uma destas variáveis será utilizada dentro de outros códigos fonte.
 *
 */
/* Variáveis utilizadas */
extern uint8_t mode;
extern uint8_t done;


/**
 *	@brief Enumeração de todos os possíveis estados da FSM.
 */
/* Todos estados utilizados */
typedef enum {
	S0, S1, S2, S3, S4, S5, S6, S7, S8
} States;


/**
 *	@brief Ponteiro de função para um determinado estado.
 */
/* Ponteiro de função para um determinado estado */
typedef void (*Action)();

/**
 *	@brief Declaração da FSM com os campos necessários.
 */
/* Dados e ponteiros de funções */
typedef struct FSM {
	States state;
	Action action[15];
} fsm;

/**
 *	@brief Declaração de uma variável compartilhada do tipo 'fsm'.
 */
extern volatile fsm sm;


/**
 *	@brief Inicializa a FSM com as funções de todos estados possíveis.
 */
/* Inicialização da FSMs */
void initFSM();

/**
 *	@brief Definição de cada função dos estados inicias.
 */
/* Estados iniciais */
void s0();
void s1();
void s2();

/**
 *	@brief Definição de cada função de estado do modo de afinação.
 */
/* Tuning */
void t_s3();
void t_s4();
void t_s5();
void t_s6();
void t_s7();
void t_s8();

/**
 *	@brief Definição de cada função de estado do modo de aprendizado.
 */
/* Learning */
void l_s3();
void l_s4();
void l_s5();
void l_s6();
void l_s7();
void l_s8();

#endif
