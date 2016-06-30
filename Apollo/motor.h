/** @file motor.h
 *  @brief Prot�tipo de fun��es utilizados para o acionamento do servo motor.
 *  @author �rthur Pinheiro
 *  @author Gabriel de Jesus
 *  @see https://www.pololu.com/docs/0J57/8.a
 */

#ifndef MOTOR_H_
#define MOTOR_H_

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

/**
 *	@brief Defini��o de frequ�ncia de opera��o do ATmega328p.
 */
#define F_CPU 16000000

/**
 *	@brief Ajusta configura��es para o motor (i.e. timer etc)
 */
void configMotor(void);

/**
 *	@brief Pausa por certo per�odo para aguardar atua��o do motor
 */
void Wait(void);

/**
 *	@brief Atua motor servo
 *  @param highTimeMicroseconds Tempo de atua��o do PWM no motor
 */
void actMotor(uint16_t highTimeMicroseconds);

#endif
