// Copyright 2023 rafae
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <PIDestal.h>

#define SENSOR_L 1
#define SENSOR_M 2
#define SENSOR_R 3

#define MOTOR_L_PWM_PIN 4
#define MOTOR_R_PWM_PIN 5

const float gainConstant = 3;

PIDestal myPid(0.5f, 0.0f, 0.2f);

uint16_t leftSensRead, middleSensRead, rightSensRead;

float pidGain = 4.0f;

void setup() {
    pinMode(SENSOR_L, INPUT);
    pinMode(SENSOR_M, INPUT);
    pinMode(SENSOR_R, INPUT);
    pinMode(MOTOR_L_PWM_PIN, OUTPUT);
    pinMode(MOTOR_R_PWM_PIN, OUTPUT);
}

void loop() {
    // Atualizando a leitura dos sensores
    leftSensRead = analogRead(SENSOR_L);
    middleSensRead = analogRead(SENSOR_M);
    rightSensRead = analogRead(SENSOR_R);

    // Calculando o erro (o delta para o centro)
    float centerError = leftSensRead - middleSensRead;
    float gain = sqrtf(middleSensRead) * gainConstant;

    float pidResult = myPid.calculate(centerError);

    float leftMotor = -(pidResult * pidGain) + gain;
    float rightMotor = (pidResult * pidGain) + gain;

    analogWrite(MOTOR_L_PWM_PIN, leftMotor);
    analogWrite(MOTOR_R_PWM_PIN, rightMotor);
}