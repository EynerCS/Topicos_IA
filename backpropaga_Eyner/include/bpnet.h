#ifndef BPNET_H
#define BPNET_H

struct neuron
{
    float *weights; // array de pesos
    float *deltavalues; //valores neurona delta
    float output; //valor de salida
    float gain;//valor del bias
    float wgain;//peso del bias

    neuron();
    ~neuron();
    void create(int inputcount);
};

struct layer
{
    neuron **neurons;//Array de neuronas
    int neuroncount;//Numero de neuronas
    float *layerinput;//Array de entradas
    int inputcount;//Numero de entradas

    layer();

    ~layer();

    void create(int inputsize, int _neuroncount);
    void calculate();//calcula las salidas de cada neurona de la capa
};
/******************************** RED NEURONAL ********************************/
class bpnet
{
private:
    layer m_inputlayer;//capa de entrada
    layer m_outputlayer;//capa de salida
    layer **m_hiddenlayers;//Array de capas ocultas
    int m_hiddenlayercount;//numero de capas ocultas

public:

    bpnet();
    ~bpnet();

    void create(int inputcount,int inputneurons,int outputcount,int *hiddenlayers,int hiddenlayercount);

    void propagate(const float *input);//Calculamos los valores de la red dados en la entrada
    //Actualizamos los valores de los pesos de la red dando un resultado deseado y aplicamos la retropropagacion

    float train(const float *desiredoutput,const float *input,float alpha, float momentum);

    //Actualizamos los valores de la siguiente capa
    void update(int layerindex);

    //Retorna la capa de salida
    inline layer &getOutput()
    {
        return m_outputlayer;
    }

};

#endif // BPNET_H
