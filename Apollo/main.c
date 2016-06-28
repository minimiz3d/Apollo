#include <avr/io.h>
#include "fsm.h"
#include "guitarTuner.h"

int main() {
	STRING string[6];           // 6 cordas para afinar.

	while(1) {
		if (PORTA0) { // readPORTA0
			mode = 1;
		} else if (PORTA1) {
			mode = 0; // readPORTA1
		} else {
			// uint8_t mode = selectMode();        // Selecionar modo: afina��o ou aprendizado.
			fsmInit(mode);						// Inicialização da FSM.
			fsm.state = S0;
			fsm.action[fsm.state]();			// Define o próximo estado a ser executado (função do estado S0).
		}
	}

	return 0;
}


// if (!mode) {                // Afina��o.
// 	tfsm fsm;
// 	initTuneFSM(fsm);       // Inicializa os estados com suas respectivas fun��es.
// 	fsm.TS = ST_1;          // Estado inicial da FSM.
// 	fsm.action[fsm.TS]();   // Inicia afina��o.
// }
//
// else {                      // Aprendizado.
// 	lfsm fsm;               // Inicia aprendizado.
// 	initLearnFSM(fsm);      // Inicializa os estados com suas respectivas fun��es.
// 	fsm.LS = SL_1;          // Estado inicial da FSM.
// 	fsm.action[fsm.LS]();
// }
