#include "tuner.h"
#include "motor.h"

//clipping indicator variables
uint8_t clipping = 0;

//data storage variables
uint8_t newData = 0;
uint8_t prevData = 0;
unsigned int time = 0;//keeps time and sends vales to store in timer[] occasionally
int timer[10];//storage for timing of events
int slope[10];//storage for slope of events
unsigned int totalTimer;//used to calculate period
unsigned int period;//storage for period of wave
uint8_t index = 0;//current storage index
float frequency;//storage for frequency calculations
int maxSlope = 0;//used to calculate max slope as trigger point
int newSlope;//storage for incoming slope data

//variables for decided whether you have a match
uint8_t noMatch = 0;//counts how many non-matches you've received to reset variables if it's been too long
uint8_t slopeTol = 3;//slope tolerance- adjust this if you need
int timerTol = 10;//timer tolerance- adjust this if you need

//variables for amp detection
unsigned int ampTimer = 0;
uint8_t maxAmp = 0;
uint8_t checkMaxAmp;
uint8_t ampThreshold = 30;//raise if you have a very noisy signal

/* Frequências padrão de afinação */
const float frequencyTable[3][6] = {
		/* DROP D TUNING */
	{	329.63,
		246.94,
		196.00,
		146.83,
		110.00,
		82.41	},

		/* DROP C TUNING */
    {   293.66,
        220.00,
        174.61,
        130.81,
        98.00,
        64.41    },

		/* OPEN G TUNING */
	{   293.66,
        246.94,
        196.00,
        146.83,
        98.00,
        73.42    }
};

/* Variáveis necessárias */
uint8_t stringInTune = 0;
uint8_t tuning = 0;

/* Função genérica de afinamento */
void tuneString(uint8_t i) {
    float currentFrequency = 0; // Atualizar essa variável com a frequência desafinada da corda em questão.
	uint16_t x = 0;
	do {
		x++;
		currentFrequency = detectFrequency();
		actMotor(x);
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
	tuning = tuning; // Variável que indexará a frequencyTable e também stringNames.
}

/* Detecção de frequência usando o ADC */
float detectFrequency() {
	float frequency = 0;

	ADCconfig();

	checkClipping();

	if (checkMaxAmp > ampThreshold){
		frequency = 38462/(float)period;//calculate frequency timer rate/period
		return frequency;
	}

	return 0;
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
