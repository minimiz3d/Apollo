#include <avr/io.h>
#include "fsm.h"
#include "guitarTuner.h"

int main() {
    while(1) {
        STRING string[6];       // 6 cordas para afinar.

        mode = selectMode();    // Selecionar modo: afinação ou aprendizado.

        if (!mode) {            // Afinação.
            tfsm fsm;
            initTuneFSM(fsm);
            fsm.TS = ST_1;
            fsm.action[fsm.TS]();
        } else {                // Aprendizado.
            lfsm fsm;
            initLearnFSM(fsm);
            fsm.LS = SL_1;
            fsm.action[fsm.LS]();
        }
    }

    return 0;
}
