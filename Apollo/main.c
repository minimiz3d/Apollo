#include <avr/io.h>
#include "fsm.h"
#include "tuner.h"

/* Vari�veis globais */
uint8_t mode = 5;
uint8_t done = 0;

int main() {
	STRING string[6];           // 6 cordas para afinar.

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
			sm.state = S0;								// Estado inicial.
			initFSM(sm, mode);							// Inicialização da FSM.

			for (int i = 0; i < 8; i++)
				sm.action[sm.state](string);			// Define o próximo estado a ser executado (função do estado S0).
		}

	}

	return 0;
}
