#include "tuner.h"
#include <avr/io.h>

/* Frequências padrão de afinação */
const float frequencyTable[3][6] = {
	{	329.63,		// E4
		246.94,		// B3
		196.00,		// G3
		146.83,		// D3
		110.00,		// A2
		82.41	},  // E2

    {   10.1,
        10.2,
        10.3,
        10.4,
        10.5,
        10.6    },

	{   20.1,
        20.2,
        20.3,
        20.4,
        20.5,
        20.6    }
};

/* Opcional */
char *stringNames[3][6] = {
	{	"E4",
		"B3",
		"G3",
		"D3",
		"A2",
		"E2"	},
	{
		"x1",
		"x2",
		"x3",
		"x4",
		"x5",
		"x6"
	},
	{
		"y1",
		"y2",
		"y3",
		"y4",
		"y5",
		"y6"
	}
};

/* Variáveis necessárias */
uint8_t stringInTune = 0;
uint8_t tuning;

/* Acionamento do motor */
void actMotor() {}

/* Função genérica de afinamento */
void tuneString(uint8_t i) {
    float currentFrequency = detectFrequency(); // Atualizar essa variável com a frequência desafinada da corda em questão.

    while (currentFrequency != string[i].tunedFrequency) {
        actMotor(); // Ainda não sei o quanto é pra girar e tal
        // Dentro da função actMotor a gente vai atualizando a "currentFrequency".
    }

    stringInTune = 1;    // Avança na FSM.
}

/* Inicialização do objeto String com suas respectivas frequências padrão de afinação */
void defineStrings() {
    for (int i = 0; i < 6; i++) {
        string[i].stringName = stringNames[tuning][i];
        string[i].tunedFrequency = frequencyTable[tuning][i];
    }
}

/* Define afinação */
void selectTuning(uint8_t tuning) {
    // waiting...
	tuning = tuning; // Variável que indexará a frequencyTable e também stringNames.
}

float detectFrequency() {
    float frequency = 81.2; // (......)
	return frequency;
	// waiting...
}

/* Aprende nova afinação */
void saveFrequency(float frequency, uint8_t stringNum) {
      string[stringNum].tunedFrequency = frequency;
}
