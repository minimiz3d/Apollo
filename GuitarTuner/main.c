#include <avr/io.h>
#include "fsm.h"

int main()
{
        // Supondo selectMode() = afinação:

    /* Leitura/conversão do sinal analógico em digital */
    inputWave();

    /* Com base na representação digital do sinal obtido anteriormente, faz-se a FFT */
    defineFrequency();
    while(1)
    {
        // Do something
    }
}
