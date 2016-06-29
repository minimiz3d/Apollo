#ifndef STATE_FUNCTIONS
#define STATE_FUNCTIONS

#include <avr/io.h>
#include <stdbool.h>

/* Atributos de cada corda */
typedef struct String {
	char *stringName;/* Opcional */
	float tunedFrequency;
} STRING;

extern STRING string[6];

/* Leitura da frequência */
float detectFrequency();

/* Acionamento do motor */
void actMotor();

/* Função genérica de afinamento */
void tuneString(STRING *string, uint8_t i);

/* Inicialização do objeto String com suas respectivas frequências padrão de afinação */
void defineStrings(STRING *string);

/* Seleciona a afinação */
void selectTuning(uint8_t tuning);

/* Salva afinação (modo de aprendizado) */
void saveFrequency(float frequency, STRING *string, uint8_t stringNum);

#endif
