/** @file motor.h
 *  @brief Protótipo de funções utilizados para o acionamento do servo motor.
 *  @author Árthur Pinheiro
 *  @author Gabriel de Jesus
 *  @see https://www.pololu.com/docs/0J57/8.a
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
 *	@brief Ajusta configurações para o motor (i.e. timer etc)
 */
void configMotor(void);

/**
 *	@brief Pausa por certo período para aguardar atuação do motor
 */
void Wait(void);

/**
 *	@brief Atua motor servo
 *  @param highTimeMicroseconds Tempo de atuação do PWM no motor
 */
void actMotor(uint16_t highTimeMicroseconds);

#endif
