// Copyright (c) 2023 Rafael Farias
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#ifndef PIDESTAL_H
#define PIDESTAL_H

class PIDestal {
   public:
    PIDestal(float &p, float &d);
    PIDestal(float &p, float &i, float &d);

    /*
    Recebe um erro e retorna o resultado do calculo de PID ou PD
    */
    float calculate(float error);

    float *kp, *ki, *kd;
    bool useIntegral = false;

   private:
    double cumulativeError = 0;
    double lastError = 0;
};

#endif