#include "adc.h"

/* Configuração do conversor A/D */
void ADCconfig(void) {
	/* Desabilita interrupções
		(i.e. instruções seguintes agem como uma instrução atômica) */
	cli();
	
	/* Limpa registradores */
	ADCSRA = ADCSRB = 0;
		
    /* Configura tensão de referência (AVcc = AVref) */
    ADMUX |= (1 << REFS0);

	/* Alinha valores à esquerda p/ ler apenas do ADCH */
	ADMUX |= (1 << ADLAR);

    /* Configura preescaler (CLK/32 = 16 MHz/32 = 500 kHz) */
    ADCSRA |= (1 << ADPS2) | (1 << ADPS0);
	
	/* Habilita autotrigger */
	ADCSRA |= (1 << ADATE);
	
    /* Habilita interrupção ao finalizar medição */
    ADCSRA |= (1 << ADIE);

	/* Habilita ADC */
	ADCSRA |= (1 << ADEN);
	
	/* Inicia ADC */
	ADCSRA |= (1 << ADSC);
	
	/* Reabilita interrupções */
	sei();
}