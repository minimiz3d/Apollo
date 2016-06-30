#include <avr/io.h>
#include <util/delay.h>
#include "fsm.h"
#include "tuner.h"

/* Variáveis globais */
uint8_t mode = 5;
uint8_t done = 0;

int main() {
	/* Portas B/D como entradas */
	DDRD |= (1 << PORTD2) | (1 << PORTD3);
	DDRB |= (1 << PORTB3);

	PINB |= (1 << PINB3);

	while(1) {		// Aguarda selecionar modo.
		while ( ((PINB & (1 << PINB4)) == 0) && ((PINB & (1 << PINB5)) == 0) ) {
			_delay_ms(1000);	// Aguarda acionamento do switch.
		}

		if ( PINB & (1 << PINB4) ) { // Afinação.
			mode = 0;
			PIND |= (1 << PIND3);
		} else {		// PORTB ativa.
			mode = 1; // Aprendizado.
			PIND |= (1 << PIND2);
		}

		while (!done) {
			initFSM();							// Inicialização e execução da FSM.
		}

	}

	return 0;
}
