#include <avr/io.h>
#include "fsm.h"
#include "tuner.h"

int main() {
	STRING string[6];           // 6 cordas para afinar.

	uint8_t mode = selectMode();        // Selecionar modo: afinação ou aprendizado.

	if (!mode) {                // Afinação.
		tfsm fsm;
		initTuneFSM(fsm);       // Inicializa os estados com suas respectivas funções.
		fsm.TS = ST_1;          // Estado inicial da FSM.
		fsm.action[fsm.TS]();   // Inicia afinação.
	}

	else {                      // Aprendizado.
		lfsm fsm;               // Inicia aprendizado.
		initLearnFSM(fsm);      // Inicializa os estados com suas respectivas funções.
		fsm.LS = SL_1;          // Estado inicial da FSM.
		fsm.action[fsm.LS]();
	}
	
	while(1) {
	}

	return 0;
}
