/**
 * @file adc.h
 * @author Árthur Pinheiro
 * @author Gabriel de Jesus
 * @brief Configurações do conversor A/D
 *
 * Define funções para a configuração do conversor A/D.
 * @see http://www.instructables.com/id/Arduino-Guitar-Tuner/?ALLSTEPS#step6
 */

#ifndef ADC_H_
#define ADC_H_

#include <avr/io.h>
#include <avr/interrupt.h>

/**
 *	@brief Configuração do conversor A/D utilizado na detecção de frequência em tempo real.
 */
void ADCconfig(void);

#endif
