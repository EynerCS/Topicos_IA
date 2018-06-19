/*********************************************************************************************************/

#include <iostream>
#include "bpnet.h"
using namespace std;
#define PATTERN_COUNT 4
#define PATTERN_SIZE 2
#define NETWORK_INPUTNEURONS 3
#define NETWORK_OUTPUT 1
#define HIDDEN_LAYERS 0
#define EPOCHS 20000

int main()
{
    //Valores XOR de prueba
    float pattern[PATTERN_COUNT][PATTERN_SIZE]=
    {
        {0,0},
        {0,1},
        {1,0},
        {1,1}
    };

    //valores deseados del XOR
    float desiredout[PATTERN_COUNT][NETWORK_OUTPUT]=
    {
        {0},
        {1},
        {1},
        {0}
    };


    bpnet net;//Nuestra red
    float error;
    //Creamos la red
    net.create(PATTERN_SIZE,NETWORK_INPUTNEURONS,NETWORK_OUTPUT,HIDDEN_LAYERS,HIDDEN_LAYERS);

    //Inicio del entrenamiento de la red neuronal
    for(int i=0;i<EPOCHS;i++)
    {
        error=0;
        for(int j=0;j<PATTERN_COUNT;j++)
        {
            error+=net.train(desiredout[j],pattern[j],0.2f,0.1f);
        }
        error/=PATTERN_COUNT;

        cout << "ERROR:" << error << "\r";

    }

    //Una vez entrenado prueba los valores

    for(int i=0;i<PATTERN_COUNT;i++)
    {

        net.propagate(pattern[i]);

        cout << "Prueba " << i << " SALIDA DESEADA: " << *desiredout[i] << " RESULTADO DE LA RED: "<< net.getOutput().neurons[0]->output << endl;
    }


    return 0;
}
