<!--
 Copyright (c) 2023 Rafael Farias

 This software is released under the MIT License.
 https://opensource.org/licenses/MIT
-->

# PIDestal

## Métodos e estruturas

### PID struct

Definição

```cpp
struct PID {
    float p;
    float i;
    float d;
};
```

Exemplo de utilização

```cpp
#include <PIDestal.h>

PID ConstantesPID = {
    0.5,
    0.001,
    0.1,
};
```

### Objeto PID

O construtor de PID recebe como argumentos uma estrutura `PID` ou o valor de constantes;

```cpp
#include <PIDestal.h>

PIDestal pid1(1, 2, 3);
```

ou

```cpp
#include <PIDestal.h>

PID ConstantesPID = {
    0.5,
    0.001,
    0.1,
};
PIDestal pid1(ConstantesPID);
```

### Usar deltaTime

Para a computação do PID pode ser utlizado ou não o `deltaTime`, este parametro é por padrão `true`.

Exemplo

```cpp
#include <PIDestal.h>

PIDestal pid1(1, 2, 3);

// Desativando o deltaTime
pid1.setUseDeltaTime(false);
```

## Incluindo a biblioteca no Arduino IDE

1. Coloque esse repositório em `Documentos -> Arduino -> libraries`.
2. Reinicie sua IDE

> Caso algo dê errado verifique [como adicionar bibliotecas na Arduino IDE](https://support.arduino.cc/hc/en-us/articles/5145457742236-Add-libraries-to-Arduino-IDE)

## Classe completa

> Atenção esse tópico pode estar desatualizado, por favor verifique o arquivo mais recente em [PIDestal.h](https://github.com/HefestusTec/PIDestal/blob/main/src/PIDestal.h)

```cpp
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

   private:
    PID myConsts;

    // O calculo de PID deve levar o tempo em consideração?
    bool useDeltaTime = true;

    float cumulativeError = 0;
    float lastError = 0;
    unsigned long lastTime = 0;
};
```

## Exemplos de utilização

Os exemplos de utilização podem ser encontrados [aqui](https://github.com/HefestusTec/PIDestal/tree/main/examples).
