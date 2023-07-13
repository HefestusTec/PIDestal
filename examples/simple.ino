// Copyright (c) 2023 Rafael Farias
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

// Para incluir a biblioteca vá na pasta "Documentos -> Arduino -> libraries"
// E crie uma biblioteca e arraste o .h e .cpp
#include <PIDestal.h>

float p = 0.5;
float i = 0.000001;
float d = 0.1;

// Criando um PID chamado "pid1"
// Voce pode alterar os valores para ver como eles afetam
PIDestal pid1(p, i, d);

void setup() {
    Serial.begin(115200);
}

int t = 2000;
float result1 = 0;
float objetivo = 0;

void loop() {
    if (t > 20) {
        // O objetivo fica mudando de tempo em tempo
        objetivo = random(-100, 100);
        t = 0;
    }

    // Calcula o PID e adiciona ao resultado
    result1 += pid1.calculate(objetivo - result1);

    // Cria um teto maximo e min para o grafico nao ficar mudando toda hora
    Serial.print(100);
    Serial.print("\t");
    Serial.print(-100);
    Serial.print("\t");

    // Plota o grafico
    Serial.print(objetivo);
    Serial.print("\t");
    Serial.println(result1);

    t += 1;
    delay(50);
}