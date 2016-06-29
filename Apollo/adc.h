/**
 * @file adc.h
 * @author Árthur Tolfo Pinheiro, Gabriel de Jesus Coelho da Silva
 * @brief Configurações do conversor A/D
 * 
 * Define funções para a configuração do conversor A/D.
 * @see http://www.instructables.com/id/Arduino-Guitar-Tuner/?ALLSTEPS#step6
 */


#ifndef ADC_H_
#define ADC_H_

#include <avr/io.h>
#include <avr/interrupt.h>

void ADCconfig(void);

void reset(void);

void checkClipping(void);

#endif