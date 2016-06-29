#ifndef TUNER_H_
#define TUNER_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include "adc.h"

/* Atributos de cada corda */
typedef struct String {
	float tunedFrequency;
} STRING;

extern STRING string[6];

//clipping indicator variables
extern uint8_t clipping = 0;

//data storage variables
extern uint8_t newData = 0;
extern uint8_t prevData = 0;
extern unsigned int time = 0;//keeps time and sends vales to store in timer[] occasionally
extern int timer[10];//storage for timing of events
extern int slope[10];//storage for slope of events
extern unsigned int totalTimer;//used to calculate period
extern unsigned int period;//storage for period of wave
extern uint8_t index = 0;//current storage index
extern float frequency;//storage for frequency calculations
extern int maxSlope = 0;//used to calculate max slope as trigger point
extern int newSlope;//storage for incoming slope data

//variables for decided whether you have a match
extern uint8_t noMatch = 0;//counts how many non-matches you've received to reset variables if it's been too long
extern uint8_t slopeTol = 3;//slope tolerance- adjust this if you need
extern int timerTol = 10;//timer tolerance- adjust this if you need

//variables for amp detection
extern unsigned int ampTimer = 0;
extern uint8_t maxAmp = 0;
extern uint8_t checkMaxAmp;
extern uint8_t ampThreshold = 30;//raise if you have a very noisy signal

/* Leitura da frequência */
float detectFrequency();

/* Acionamento do motor */
void actMotor();

/* Função genérica de afinamento */
void tuneString(uint8_t i);

/* Inicialização do objeto String com suas respectivas frequências padrão de afinação */
void defineStrings();

/* Seleciona a afinação */
void selectTuning(uint8_t tuning);

/* Salva afinação (modo de aprendizado) */
void saveFrequency(float frequency, uint8_t stringNum);

#endif
