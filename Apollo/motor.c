#include "motor.h"

// This is the time since the last rising edge in units of 0.5us.
uint16_t volatile servoTime = 0;

// This is the pulse width we want in units of 0.5us.
uint16_t volatile servoHighTime = 3000;

// This is true if the servo pin is currently high.
uint8_t volatile servoHigh = 0;

void configMotor(void) {
  DDRB |= (1 << PORTB1);
  
  // Turn on CTC mode.  Timer 2 will count up to OCR2A, then
  // reset to 0 and cause an interrupt.
  TCCR2A = (1 << WGM21);
  // Set a 1:8 prescaler.  This gives us 0.5us resolution.
  TCCR2B = (1 << CS21);
  
  // Put the timer in a good default state.
  TCNT2 = 0;
  OCR2A = 255;
  
  TIMSK2 |= (1 << OCIE2A);  // Enable timer compare interrupt.
  sei();   // Enable interrupts.
}

void Wait() {
	uint8_t i;
	for(i=0;i<50;i++)
	{
		_delay_loop_2(0);
		_delay_loop_2(0);
		_delay_loop_2(0);
	}

}

void actMotor(uint16_t highTimeMicroseconds) {

	TIMSK2 &= ~(1 << OCIE2A); // disable timer compare interrupt
	servoHighTime = highTimeMicroseconds * 2;
	TIMSK2 |= (1 << OCIE2A); // enable timer compare interrupt

	//OCR1A = 375 + x*1.4;   //0 degree
	//Wait();

	//OCR1A=500;  //90 degrees
	//Wait();

	//OCR1A=625;  //180 degrees
	//Wait();
}

// This ISR runs after Timer 2 reaches OCR2A and resets.
// In this ISR, we set OCR2A in order to schedule when the next
// interrupt will happen.
// Generally we will set OCR2A to 255 so that we have an
// interrupt every 128 us, but the first two interrupt intervals
// after the rising edge will be smaller so we can achieve
// the desired pulse width.
ISR(TIMER2_COMPA_vect)
{
	// The time that passed since the last interrupt is OCR2A + 1
	// because the timer value will equal OCR2A before going to 0.
	servoTime += OCR2A + 1;
	
	static uint16_t highTimeCopy = 3000;
	static uint8_t interruptCount = 0;
	
	if(servoHigh)
	{
		if(++interruptCount == 2)
		{
			OCR2A = 255;
		}
		
		// The servo pin is currently high.
		// Check to see if is time for a falling edge.
		// Note: We could == instead of >=.
		if(servoTime >= highTimeCopy)
		{
			// The pin has been high enough, so do a falling edge.
			PINB &= ~(1 << PINB1);
			servoHigh = 0;
			interruptCount = 0;
		}
	}
	else
	{
		// The servo pin is currently low.
		
		if(servoTime >= 40000)
		{
			// We've hit the end of the period (20 ms),
			// so do a rising edge.
			highTimeCopy = servoHighTime;
			PINB |= (1 << PINB1);
			servoHigh = 1;
			servoTime = 0;
			interruptCount = 0;
			OCR2A = ((highTimeCopy % 256) + 256)/2 - 1;
		}
	}
}