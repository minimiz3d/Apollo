/**
 * @file adc.h
 * @author �rthur Tolfo Pinheiro
 * @author Gabriel de Jesus Coelho da Silva
 * @brief Configura��es do conversor A/D
 *
 * Define fun��es para a configura��o do conversor A/D.
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
