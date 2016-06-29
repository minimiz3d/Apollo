#include "tuner.h"

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

/* Variáveis necessárias */
uint8_t stringInTune = 0;
uint8_t tuning;

/* Acionamento do motor */
void actMotor() {}

/* Função genérica de afinamento */
void tuneString(uint8_t i) {
    float currentFrequency = 0; // Atualizar essa variável com a frequência desafinada da corda em questão.

	do {
		currentFrequency = detectFrequency();
		actMotor();
	} while ( currentFrequency >= (string[i].tunedFrequency)*0.9 || currentFrequency <= (string[i].tunedFrequency)*1.1 );

    stringInTune = 1;    // Avança na FSM.
}

/* Inicialização do objeto String com suas respectivas frequências padrão de afinação */
void defineStrings() {
    for (int i = 0; i < 6; i++)
        string[i].tunedFrequency = frequencyTable[tuning][i];
}

/* Define afinação */
void selectTuning(uint8_t tuning) {
    // waiting...
	tuning = tuning; // Variável que indexará a frequencyTable e também stringNames.
}

float detectFrequency() {
	float frequency = 0;

	ADCconfig();

	checkClipping();

	if (checkMaxAmp > ampThreshold){
		frequency = 38462/(float)period;//calculate frequency timer rate/period
		return frequency;
	}
}

/* Aprende nova afinação */
void saveFrequency(float frequency, uint8_t stringNum) {
      string[stringNum].tunedFrequency = frequency;
}


/* Reinicia variáveis */
void reset(void){
	index = 0;
	noMatch = 0;
	maxSlope = 0;
}

/* Verifica saturação do sinal */
void checkClipping(void){
	if (clipping)
	clipping = 0;
}

/* Valor do conversor A/D está pronto */
ISR(ADC_vect) {
	prevData = newData;//store previous value
	newData = ADCH;//get value from A0
	if (prevData < 127 && newData >=127){//if increasing and crossing midpoint
		newSlope = newData - prevData;//calculate slope
		if (abs(newSlope-maxSlope)<slopeTol){//if slopes are ==
			//record new data and reset time
			slope[index] = newSlope;
			timer[index] = time;
			time = 0;
			if (index == 0){//new max slope just reset
				noMatch = 0;
				index++;//increment index
			}
			else if (abs(timer[0]-timer[index])<timerTol && abs(slope[0]-newSlope)<slopeTol){//if timer duration and slopes match
				//sum timer values
				totalTimer = 0;
				for (uint8_t i=0;i<index;i++){
					totalTimer+=timer[i];
				}
				period = totalTimer;//set period
				//reset new zero index values to compare with
				timer[0] = timer[index];
				slope[0] = slope[index];
				index = 1;//set index to 1
				noMatch = 0;
			}
			else{//crossing midpoint but not match
				index++;//increment index
				if (index > 9){
					reset();
				}
			}
		}
		else if (newSlope>maxSlope){//if new slope is much larger than max slope
			maxSlope = newSlope;
			time = 0;//reset clock
			noMatch = 0;
			index = 0;//reset index
		}
		else{//slope not steep enough
			noMatch++;//increment no match counter
			if (noMatch>9){
				reset();
			}
		}
	}

	if (newData == 0 || newData == 1023){//if clipping
		clipping = 1;//currently clipping
	}

	time++;//increment timer at rate of 38.5kHz

	ampTimer++;//increment amplitude timer
	if (abs(127-ADCH)>maxAmp){
		maxAmp = abs(127-ADCH);
	}
	if (ampTimer==1000){
		ampTimer = 0;
		checkMaxAmp = maxAmp;
		maxAmp = 0;
	}

}
