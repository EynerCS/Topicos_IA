/*********************************************************************************************************/
#include "bpnet.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/***************************** Neurona *******************************/
neuron::neuron():weights(0),deltavalues(0),output(0),gain(0),wgain(0) { }

neuron::~neuron(){
    if(weights)
        delete [] weights;
    if(deltavalues)
        delete [] deltavalues;
}

//Inicializa los pesos
void neuron::create(int inputcount){
    assert(inputcount);
    float sign=-1;//cambiamos el signo
    float random;//indicador aleatorio
    weights=new float[inputcount];
    deltavalues=new float[inputcount];
    //inicializamos todos los pesos de forma aleatoria

    for(int i=0;i<inputcount;i++){
        //Valor aleatorio -0.5 and 0.5
        random=(float(rand()) / float(RAND_MAX))/2.f;
        random*=sign;
        sign*=-1;
        weights[i]=random;
        deltavalues[i]=0;
    }
    gain=1;

    random=(float(rand()) / float(RAND_MAX))/2.f;
    random*=sign;
    sign*=-1;
    wgain=random;
}

/*********************************** Capa ********************************/
layer::layer():neurons(0),neuroncount(0),layerinput(0),inputcount(0){ }

layer::~layer(){
    if(neurons){
        for(int i=0;i<neuroncount;i++){
            delete neurons[i];
        }
        delete [] neurons;
    }
    if(layerinput){
        delete [] layerinput;
    }
}

void layer::create(int inputsize, int _neuroncount){
    assert(inputsize && _neuroncount);//revisa los errores
    neurons=new neuron*[_neuroncount];
    for(int i=0;i<_neuroncount;i++){
        neurons[i]=new neuron;
        neurons[i]->create(inputsize);
    }

    layerinput=new float[inputsize];
    neuroncount=_neuroncount;
    inputcount=inputsize;
}
//Calcula la salida resultante de cada neuron en una capa dada
void layer::calculate(){
    float sum;

    for(int i=0;i<neuroncount;i++){
        sum=0;//inicializar suma en cada neurona
        for(int j=0;j<inputcount;j++){
            sum+=neurons[i]->weights[j] * layerinput[j]; //input * peso
        }
        sum+=neurons[i]->wgain * neurons[i]->gain; //agregar el bias * peso del bias

        neurons[i]->output= 1.f/(1.f + exp(-sum));//calcula la funcion simoidea
       // neuronas[i]->output=-1 + 2*(1.f + exp(-sum));
    }
}


/*************************** RED NEURONAL **************/
bpnet::bpnet():m_hiddenlayers(0),m_hiddenlayercount(0){ }

bpnet::~bpnet(){
    if(m_hiddenlayers){
        for(int i=0;i<m_hiddenlayercount;i++){
            delete m_hiddenlayers[i];
        }
        delete [] m_hiddenlayers;
    }
}

void bpnet::create(int inputcount, int inputneurons, int outputcount, int *hiddenlayers, int hiddenlayercount){
            assert(inputcount && inputneurons && outputcount);
            m_inputlayer.create(inputcount,inputneurons); // crea la capa de entrada
            if(hiddenlayers && hiddenlayercount){
                m_hiddenlayers=new layer*[hiddenlayercount]; // crea las capas ocultas
                m_hiddenlayercount=hiddenlayercount;
                for(int i=0;i<hiddenlayercount;i++){
                    m_hiddenlayers[i]=new layer;
                    if(i==0){
                        m_hiddenlayers[i]->create(inputneurons,hiddenlayers[i]);
                    }
                    else{
                        m_hiddenlayers[i]->create(hiddenlayers[i-1],hiddenlayers[i]);
                    }
                }
                m_outputlayer.create(hiddenlayers[hiddenlayercount - 1],outputcount);
            }
            else{
                m_outputlayer.create(inputneurons,outputcount);
            }
}

void bpnet::propagate(const float *input){
    //La propagacion empieza desde la capa de inicio

    memcpy(m_inputlayer.layerinput,input,m_inputlayer.inputcount * sizeof(float));
    //calcular las nuevas entradas de la siguiente capa
    m_inputlayer.calculate();

    update(-1);//propagar de la capa input a la siguiente capa
    if(m_hiddenlayers){
        for(int i=0;i<m_hiddenlayercount;i++){
            m_hiddenlayers[i]->calculate();
            update(i);
        }
    }
    //calcular la ultima capa
    m_outputlayer.calculate();
}
//Funcion principal de entrenamiento. Corre en un bucle cuantas veces sea necesario
float bpnet::train(const float *desiredoutput, const float *input, float alpha, float momentum){
    //Enseña a la red a reconocer un patron dado un resultado deseado
    float errorg=0; //error cuadratico general
    float errorc; //error local
    float sum=0,csum=0;
    float delta,udelta;
    float output;
    //propagamos el input
    propagate(input);
    //el backpropagation empieza de la capa de salida propagando el error
    for(int i=0;i<m_outputlayer.neuroncount;i++){
        //calcula el valor de error para la capa de salida
        output=m_outputlayer.neurons[i]->output; //copiar este valor para para facilitar operaciones
        //tomamos el valor de error
        errorc=(desiredoutput[i] - output) * output * (1 - output);
        //delta es la diferencia cuadratica
        //del valor deseado con el valor de salida
        errorg+=(desiredoutput[i] - output) * (desiredoutput[i] - output) ;

        //actualizamos los pesos de la neurona
        for(int j=0;j<m_outputlayer.inputcount;j++)
        {
            delta=m_outputlayer.neurons[i]->deltavalues[j];
            //actualizar el valor delta
            udelta=alpha * errorc * m_outputlayer.layerinput[j] + delta * momentum;
            //actualizar los pesos
            m_outputlayer.neurons[i]->weights[j]+=udelta;
            m_outputlayer.neurons[i]->deltavalues[j]=udelta;

            sum+=m_outputlayer.neurons[i]->weights[j] * errorc;
        }

        //calculamos el peso obtenido
        m_outputlayer.neurons[i]->wgain+= alpha * errorc * m_outputlayer.neurons[i]->gain;

    }

    for(int i=(m_hiddenlayercount - 1);i>=0;i--)
    {
        for(int j=0;j<m_hiddenlayers[i]->neuroncount;j++)
        {
            output=m_hiddenlayers[i]->neurons[j]->output;
            //calcular el error para para esta capa
            errorc= output * (1-output) * sum;
            //actualizamos los pesos de la neurona
            for(int k=0;k<m_hiddenlayers[i]->inputcount;k++)
            {
                delta=m_hiddenlayers[i]->neurons[j]->deltavalues[k];
                udelta= alpha * errorc * m_hiddenlayers[i]->layerinput[k] + delta * momentum;
                m_hiddenlayers[i]->neurons[j]->weights[k]+=udelta;
                m_hiddenlayers[i]->neurons[j]->deltavalues[k]=udelta;
                csum+=m_hiddenlayers[i]->neurons[j]->weights[k] * errorc;

            }

            m_hiddenlayers[i]->neurons[j]->wgain+=alpha * errorc * m_hiddenlayers[i]->neurons[j]->gain;

        }
        sum=csum;
        csum=0;
    }

    //la capa input
    for(int i=0;i<m_inputlayer.neuroncount;i++)
    {
        output=m_inputlayer.neurons[i]->output;
        errorc=output * (1 - output) * sum;

        for(int j=0;j<m_inputlayer.inputcount;j++)
        {
            delta=m_inputlayer.neurons[i]->deltavalues[j];
            udelta=alpha * errorc * m_inputlayer.layerinput[j] + delta * momentum;
            //actualizamos pesos
            m_inputlayer.neurons[i]->weights[j]+=udelta;
            m_inputlayer.neurons[i]->deltavalues[j]=udelta;
        }

        m_inputlayer.neurons[i]->wgain+=alpha * errorc * m_inputlayer.neurons[i]->gain;
    }

    //retorna el error general
    return errorg / 2;
}

void bpnet::update(int layerindex){
    if(layerindex==-1){
        //propagacion de la capa inicial a la siguiente
        for(int i=0;i<m_inputlayer.neuroncount;i++){
            if(m_hiddenlayers){
                m_hiddenlayers[0]->layerinput[i]=m_inputlayer.neurons[i]->output;
            }
            else{
                m_outputlayer.layerinput[i]=m_inputlayer.neurons[i]->output;
            }
        }
    }
    else{
        for(int i=0;i<m_hiddenlayers[layerindex]->neuroncount;i++){
            //Toca capa menos la ultima
            if(layerindex < m_hiddenlayercount -1){
                m_hiddenlayers[layerindex + 1]->layerinput[i]=m_hiddenlayers[layerindex]->neurons[i]->output;
            }
            else{
                m_outputlayer.layerinput[i]=m_hiddenlayers[layerindex]->neurons[i]->output;
            }
        }
    }
}
