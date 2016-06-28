/*
 * fsm.c
 *
 * This file defines a finite state machine for the tuner
 */

#include "fsm.h"

/* Inicialização das FSMs */
void initTuneFSM(tfsm fsm) {
    fsm.action[ST_1] = st1;
    fsm.action[ST_2] = st2;
    fsm.action[ST_3] = st3;
    fsm.action[ST_4] = st4;
    fsm.action[ST_5] = st5;
    fsm.action[ST_6] = st6;
    fsm.action[ST_7] = st7;
    fsm.action[ST_8] = st8;
}
void initLearnFSM(lfsm fsm) {
    fsm.action[SL_1] = sl1;
    fsm.action[SL_2] = sl2;
    fsm.action[SL_3] = sl3;
    fsm.action[SL_4] = sl4;
    fsm.action[SL_5] = sl5;
    fsm.action[SL_6] = sl6;
    fsm.action[SL_7] = sl7;
    fsm.action[SL_8] = sl8;
}

/* Funções de estados de afinação */
void st1() {
    tuneString();
    fsm.TS = ST_2;  // Avança na FSM.
}
void st2() {
    tuneString();
    fsm.TS = ST_3;  // Avança na FSM.
}
void st3() {
    tuneString();
    fsm.TS = ST_4;  // Avança na FSM.
}
void st4() {
    tuneString();
    fsm.TS = ST_5;  // Avança na FSM.
}
void st5() {
    tuneString();
    fsm.TS = ST_6;  // Avança na FSM.
}
void st6() {
    tuneString();
    fsm.TS = ST_7;  // Avança na FSM.
}
void st7() {
    tuneString();
    fsm.TS = ST_8;  // Avança na FSM.
}
void st8() {
    tuneString();
    fsm.TS = S0;  // Avança na FSM.
}

/* Funções de estados de aprendizado */
void sl1() {
    string[i].tunedFrequency = detectFrequency();
    fsm.LS = SL_2;  // Avança na FSM.
}
void sl2() {
    string[i].tunedFrequency = detectFrequency();
    fsm.LS = SL_3;  // Avança na FSM.
}
void sl3() {
    string[i].tunedFrequency = detectFrequency();
    fsm.LS = SL_4;  // Avança na FSM.
}
void sl4() {
    string[i].tunedFrequency = detectFrequency();
    fsm.LS = SL_5;  // Avança na FSM.
}
void sl5() {
    string[i].tunedFrequency = detectFrequency();
    fsm.LS = SL_6;  // Avança na FSM.
}
void sl6() {
    string[i].tunedFrequency = detectFrequency();
    fsm.LS = SL_7;  // Avança na FSM.
}
void sl7() {
    string[i].tunedFrequency = detectFrequency();
    fsm.LS = SL_8;  // Avança na FSM.
}
void sl8() {
    string[i].tunedFrequency = detectFrequency();
    fsm.LS = S0;  // Avança na FSM.
}
