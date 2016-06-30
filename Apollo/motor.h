/** @file motor.h
 *  @brief Protótipo de funções utilizados para o acionamento do servo motor.
 *  @author Árthur Pinheiro
 *  @author Gabriel de Jesus
 */

#ifndef MOTOR_H_
#define MOTOR_H_

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

/**
 *	@brief Definição de frequência de operação do ATmega328p.
 */
#define F_CPU 16000000

/**
 *	@brief ???
 */
void configMotor(void);

/**
 *	@brief ???
 */
void Wait(void);

/**
 *	@brief ???
 *  @param highTimeMicroseconds Tempo máximo ????? ñ tenho ctz aqui.... 
 */
void actMotor(uint16_t highTimeMicroseconds);

#endif
