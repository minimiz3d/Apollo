#include <avr/io.h>

/* ADC config. */
void ADCconfig(void) {
    /* AVcc = AVref */
    ADMUX |= (1 << REFS0);

    /* Preescaler setting - CLK/128 */
    ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

    // DÚVIDA SE VAMOS USAR FREE RUNNING MODE AINDA
    // /* Selecionar modo de conversão - FreeRunningMode */
    // ADCSRB |= (0 << ADTS2) | (0 << ADTS1) | (0 << ADTS0);

    // Daria pra fazer com interrupções
    /* Habilita interrupções */
    ADCSRA |= (1 << ADIE);

    /* Enables ADC */
    ADCSRA |= (1 << ADEN);
}

/* ADC conversion */
uint16_t ADCconversion(uint8_t channelNum) {
    uint16_t ADCresult;

    /* Como são 8 canais possíveis, então o num_canal deve ser algum entre 0~7 */
    channelNum &= 0x7;
    ADMUX |= channelNum;

    /* Inicia conversão */
    ADCSRA |= (1 << ADSC);

    /* Aguarda conversão chegar ao fim */
    while(!(ADCSRA & (1 << ADIF)));

    /* Obtém o resultado da conversão */
    ADCresult = ADCL;
    ADCresult = (ADCH << 8) + ADCresult;

    return ADCresult;
}