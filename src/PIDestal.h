// Copyright (c) 2023 Rafael Farias
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#ifndef PIDESTAL_H
#define PIDESTAL_H

class PIDestal {
   public:
    PIDestal();
    PIDestal(float p, float d);
    PIDestal(float p, float i, float d);
    PIDestal(float &p, float &d);
    PIDestal(float &p, float &i, float &d);
    ~PIDestal();

    /*
    Recebe um erro e retorna o resultado do calculo de PID ou PD
    */
    float calculate(float error);

    float *kp, *ki, *kd;

   private:
    bool useIntegral = false;
    bool shouldDelete = false;
    float cumulativeError = 0;
    float lastError = 0;
};

#endif