/** @file tuner.h
 *  @brief Protótipo de funções utilizados no modo de afinação e aprendizado.
 *  @author Árthur Pinheiro
 *  @author Gabriel de Jesus
 */

#ifndef TUNER_H_
#define TUNER_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include "adc.h"
#include "motor.h"

/**
 *	@brief Frequência desejada de afinação de cada corda.
 */
typedef struct String {
	float tunedFrequency;
} STRING;


/**
 *	@brief Declaração de variáveis compartilhadas.
 *
 *	Cada uma destas variáveis será utilizada dentro de outros códigos fonte.
 *
 */
extern STRING string[6];

/**
 *	@brief Detecção de frequência em tempo real.
 */
float detectFrequency(void);

/**
 *	@brief Função genérica de afinação.
 */
void tuneString(uint8_t i);

/**
 *	@brief Inicialização do objeto String com suas respectivas frequências padrão de afinação.
 */
void defineStrings(void);

/**
 *	@brief Seleciona a afinação desejada.
 */
void selectTuning(uint8_t tuning);

/**
 *	@brief Salva afinação (modo de aprendizado).
 */
void saveFrequency(float frequency, uint8_t stringNum);

#endif
