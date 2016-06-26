#ifndef STATE_FUNCTIONS
#define STATE_FUNCTIONS

/* Definir modo de operação */
void selectMode();

/* Leitura de porta digital */
uint8_t readPORTB();

/* Definir modo de operação: afinação ou aprendizado */
void selectMode();

/* Acionamento do motor */
void actMotor();

/* Função genérica de afinamento */
void tuneString();

#endif
