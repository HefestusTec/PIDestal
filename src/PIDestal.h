// Copyright (c) 2023 Rafael Farias
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#ifndef PIDESTAL_H
#define PIDESTAL_H

#include <arduino.h>

struct PID {
    float p;
    float i;
    float d;

    // Define o operador != da PID struct
    bool operator!=(const PID& other) const {
        return (p != other.p) || (i != other.i) || (d != other.d);
    }
};

class PIDestal {
   public:
    PIDestal();
    PIDestal(PID constants);
    PIDestal(float kp, float ki, float kd);

    // Recebe um erro e retorna o resultado do calculo de PID ou PD
    float calculate(float error);

    // Seta o valor das constantes, recebe uma struct PID
    void setPidConsts(PID newConstants) { myConsts = newConstants; }
    // Seta o valor das constantes, recebe as constantes p, i, d.
    void setPidConsts(float kp, float ki, float kd) { myConsts = {kp, ki, kd}; }
    // Retorna uma Struct do tipo PID com as constantes atuais.
    PID getPidConsts() { return myConsts; }

    // Seta o "useDeltaTime" variável que indica se o deltaTime deve ou não ser utilizado nas computações
    void setUseDeltaTime(bool use) { useDeltaTime = use; }
    // Retorna o "useDeltaTime" variável que indica se o deltaTime deve ou não ser utilizado nas computações
    bool getUseDeltaTime() { return useDeltaTime; }

    float cumulativeError = 0;
    float maxCumulativeError = 100;

    /*
    Qual a tolerância para poder zerar o "cumulativeError"?

    Zerar o erro acumulado é importante para que o mesmo não saia de controle.
    */
    float errorTolerance = 0;

   private:
    PID myConsts;

    // O calculo de PID deve levar o tempo em consideração?
    bool useDeltaTime = true;

    float lastError = 0;
    unsigned long lastTime = 0;
};

#endif