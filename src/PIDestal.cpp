// Copyright (c) 2023 Rafael Farias
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#include "PIDestal.h"

PIDestal::PIDestal() {
    myConsts = {0.5, 0.1, 0.1};
}

PIDestal::PIDestal(PID constants) {
    myConsts = constants;
}

PIDestal::PIDestal(float kp, float ki, float kd) {
    myConsts = {
        kp,
        ki,
        kd,
    };
}

float PIDestal::calculate(float error) {
    cumulativeError += error;

    unsigned long now = millis();
    float delataTime =
        useDeltaTime ? (float)(now - lastTime) : 1;

    if (!delataTime) {
        delataTime = 0.0001f;
    }

    // Calculando os valores do PID
    float proportional = error;

    float integral = cumulativeError * delataTime;

    float derivative = (error - lastError) / delataTime;

    // Atualizando os parâmetros
    lastError = error;
    lastTime = now;

    return (
        (proportional * myConsts.p) +
        (integral * myConsts.i) +
        (derivative * myConsts.d));
}
