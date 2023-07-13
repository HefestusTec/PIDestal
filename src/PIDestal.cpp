// Copyright (c) 2023 Rafael Farias
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#include "PIDestal.h"

PIDestal::PIDestal(float &p, float &d) {
    kp = &p;
    kd = &d;
    useIntegral = false;
}
PIDestal::PIDestal(float &p, float &i, float &d) {
    kp = &p;
    ki = &i;
    kd = &d;
    useIntegral = true;
}

float PIDestal::calculate(float error) {
    cumulativeError += error;

    // Resetando o erro acumulado ao alcançar o objetivo
    if (error == 0)
        cumulativeError = 0;

    // Limitando a integral
    if (cumulativeError > 50 / (*ki))
        error = 50 / (*ki);

    // Calculando os valores do PID
    double proportional = error * (*kp);
    double integral = cumulativeError * (*ki);
    double derivative = (error - lastError) * (*kd);

    lastError = error;

    // Resultado da computação
    return useIntegral ? proportional + integral + derivative : proportional + derivative;
}
