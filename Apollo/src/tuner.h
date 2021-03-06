#ifndef TUNER_H_
#define TUNER_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include "adc.h"
#include "motor.h"

/* Atributos de cada corda */
typedef struct String {
	float tunedFrequency;
} STRING;

extern STRING string[6];

/* Leitura da frequência */
float detectFrequency();

/* Função genérica de afinamento */
void tuneString(uint8_t i);

/* Inicialização do objeto String com suas respectivas frequências padrão de afinação */
void defineStrings();

/* Seleciona a afinação */
void selectTuning(uint8_t tuning);

/* Salva afinação (modo de aprendizado) */
void saveFrequency(float frequency, uint8_t stringNum);

#endif
