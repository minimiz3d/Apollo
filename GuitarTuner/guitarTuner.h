#ifndef STATE_FUNCTIONS
#define STATE_FUNCTIONS

/* Frequências padrão de afinação */
float frequencyTable[] = {
    329.63,   // E4
    246.94,   // B3
    196.00,   // G3
    146.83,   // D3
    110.00,   // A2
    82.41     // E2
};

/* Opcional */
char stringNames[] = {
    "E4",
    "B3",
    "G3",
    "D3",
    "A2",
    "E2"
};

/* Atributos de cada corda */
typedef struct String {
    char stringName;/* Opcional */
    float tunedFrequency;
} STRING;

/* Leitura de porta digital */
uint8_t readPORTB();

/* Definir modo de operação */
void selectMode();

/* Acionamento do motor */
void actMotor();

/* Função genérica de afinamento */
void tuneString();

/* Inicialização do objeto String com suas respectivas frequências padrão de afinação */
void defineStrings();

#endif
