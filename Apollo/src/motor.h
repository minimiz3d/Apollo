#ifndef MOTOR_H_
#define MOTOR_H_

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define F_CPU 16000000

void configMotor(void);

void Wait(void);

void actMotor(uint16_t x);

#endif