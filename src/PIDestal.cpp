// Copyright (c) 2023 Rafael Farias
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#include "PIDestal.h"

PIDestal::PIDestal() {
    kp = new float(0.5);
    kd = new float(0.1);

    shouldDelete = true;
    useIntegral = false;
}

PIDestal::PIDestal(float p, float d) {
    kp = new float(p);
    kd = new float(d);

    shouldDelete = true;
    useIntegral = false;
}
PIDestal::PIDestal(float p, float i, float d) {
    kp = new float(p);
    ki = new float(i);
    kd = new float(d);

    shouldDelete = true;
    useIntegral = true;
}
PIDestal::PIDestal(float &p, float &d) {
    kp = &p;
    kd = &d;

    shouldDelete = false;
    useIntegral = false;
}
PIDestal::PIDestal(float &p, float &i, float &d) {
    kp = &p;
    ki = &i;
    kd = &d;

    shouldDelete = false;
    useIntegral = true;
}

PIDestal::~PIDestal() {
    if (shouldDelete) {
        // Limpando a memoria alocada
        delete kp;
        delete ki;
        delete kd;
    }
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
    float proportional = error * (*kp);
    float integral = cumulativeError * (*ki);
    float derivative = (error - lastError) * (*kd);

    lastError = error;

    // Resultado da computação
    return useIntegral ? proportional + integral + derivative : proportional + derivative;
}
