#ifndef STATE_FUNCTIONS
#define STATE_FUNCTIONS

/* Frequências padrão de afinação */
float frequencyTable[6] = {
    329.63,   // E4
    246.94,   // B3
    196.00,   // G3
    146.83,   // D3
    110.00,   // A2
    82.41     // E2
};

/* Opcional */
char *stringNames[6] = {
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
uint8_t selectMode();

/* Acionamento do motor */
void actMotor();

/* Função genérica de afinamento */
void tuneString(STRING string, uint8_t i);

/* Inicialização do objeto String com suas respectivas frequências padrão de afinação */
void defineStrings();

#endif
