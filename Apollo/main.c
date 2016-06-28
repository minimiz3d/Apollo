#include <avr/io.h>
#include "fsm.h"
#include "guitarTuner.h"

/* Vari�veis globais */
uint8_t mode = 5;
uint8_t done = 1;

int main() {
	STRING string[6];           // 6 cordas para afinar.
	fsm sm;						// Máquina de estados.

	/* Simular leitura de porta */
	DDRD = 0x00; PORTD = 0x01;
	DDRB = 0x00; PORTB = 0x00;

	while(1) {		// Aguarda selecionar modo.
		while (!PORTD || !PORTB);						// Aguarda acionamento do switch.

		if (PORTD)  // Afina��o.
			mode = 0;
		else		// PORTB ativa.
			mode = 1; // Aprendizado.

		while (!done) {
			initFSM(sm, mode);							// Inicialização da FSM.
			sm.state = S0;								// Estado inicial.

			for (int i = 0; i < 8; i++)
				sm.action[sm.state](string);			// Define o próximo estado a ser executado (função do estado S0).
		}

	}

	return 0;
}
