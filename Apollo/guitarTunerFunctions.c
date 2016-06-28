#include "guitarTuner.h"
#include <avr/io.h>

/* Definir modo de operação: afinação ou aprendizado */
uint8_t selectMode() {
    uint8_t mode = readPORTB();
    
	return mode;
}
uint8_t readPORTB() {
    DDRD = 0x00;    // Porta D - entrada.
    uint8_t mode = PORTD;   // Leitura.

    return mode;
}

/* Acionamento do motor */
void actMotor() {}

/* Função genérica de afinamento */
void tuneString(STRING string, uint8_t i) {
    currentFrequency = detectFrequency(); // Atualizar essa variável com a frequência desafinada da corda em questão.

    while (currentFrequency != string[i].frequency) {
        actMotor(); // Ainda não sei o quanto é pra girar e tal
        // Dentro da função actMotor a gente vai atualizando a "currentFrequency".
    }

    stringInTune = true;    // Avança na FSM.
}

/* Inicialização do objeto String com suas respectivas frequências padrão de afinação */
void defineStrings() {
    for (int i = 0; i < 6; i++) {
        string[i].stringName = stringNames[i];
        string[i].tunedFrequency = frequencyTable[i];
    }
}
