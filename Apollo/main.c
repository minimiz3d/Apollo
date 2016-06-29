#include <avr/io.h>
#include "fsm.h"
#include "tuner.h"

/* Vari�veis globais */
uint8_t mode = 5;
uint8_t done = 0;

int main() {
	// STRING string[6];           // 6 cordas para afinar.

	/* Simular leitura de porta */
	DDRD = 0x00; PORTD = 0x01;
	DDRB = 0x00; PORTB = 0x00;

	while(1) {		// Aguarda selecionar modo.
		while (!PORTD1 || !PORTB1);						// Aguarda acionamento do switch.

		if (PORTD1)  // Afina��o.
			mode = 0;
		else		// PORTB ativa.
			mode = 1; // Aprendizado.

		while (!done) {
			initFSM();							// Inicialização da FSM.
		}

	}

	return 0;
}
