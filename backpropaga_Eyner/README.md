BACKPROPAGATION

Primero, el data_set está en formato csv, solo intercambiamos las comas por los espacios. El archivo está con el nombre "data_set.csv"

Segundo, el codigo se ejecuta en cualquier IDE C++ (Codeblocks por ejemplo). El proyecto incluye un archivo .h y .cpp que son de la clase 
"red" y el main.cpp
-----------------------------------------------------------------------------------------------------------------------------------------
1) ESTRUCTURA DE NEURON
La estructura neuronal debe contener todo lo que representa una neurona:

- Una matriz de números flotantes como el "conector sináptico" o pesos
- El valor de salida de la neurona
- El valor de ganancia de la neurona es generalmente 1
- El peso o conector sináptico del valor de ganancia
- Además, una matriz de valores flotantes para contener los valores delta, que es la última actualización del valor delta de una iteración anterior.
-----------------------------------------------------------------------------------------------------------------------------------------
2) ESTRUCTURA DE CAPA

Nuestra siguiente estructura es la "capa". Básicamente, contiene una matriz de neuronas junto con la entrada de la capa. 
Todas las neuronas de la capa comparten la misma entrada, por lo que la entrada de capa está representada por una matriz de valores flotantes.

La estructura de "capa" contiene un bloque de neuronas que representa una capa de la red. Contiene puntero a una matriz de la estructura "neurona",
la matriz que contiene la entrada de la neurona y sus respectivas descripciones.
-----------------------------------------------------------------------------------------------------------------------------------------
3) LA ESTRUCTURA DE LA RED NEURONAL

La clase "bpnet" representa toda la red neuronal. Contiene su capa de entrada, capa de salida y capas ocultas opcionales.
El algoritmo de entrenamiento se centra en la función primaria bpnet :: propagate (....) y la función layer :: calculate ().
Estas funciones lo que hacen es propagar y calcular los valores de salida de la red neuronal. La función de propagación es la que se debe 
usar en la parte final.
-----------------------------------------------------------------------------------------------------------------------------------------
4)  Cálculo de los valores de red

Para calcular los valores de la red, el primer objetivo es calcular cada capa de neuronas, y no hay mejor manera que implementar 
una función miembro en el objeto "capa". La función layer :: calculate () muestra cómo implementar esta fórmula ya conocida.
-----------------------------------------------------------------------------------------------------------------------------------------
5)CÁLCULO Y PROPAGACIÓN DE LOS VALORES DE LA RED

Función de propagación, calcula el valor de la red dada una entrada. Comienza a calcular la capa de entrada y luego se propaga a la 
siguiente capa, calculando la siguiente capa hasta que alcanza la capa de salida. Una vez que la red se ha propagado y calculado, 
solo se ocuparía del valor de salida.
-----------------------------------------------------------------------------------------------------------------------------------------
6) ENTRENAMIENTO DE LA RED

El entrenamiento de la red es lo que hace que la red neuronal sea útil. La función de entrenamiento es lo que aplica el algoritmo de 
retropropagación. 

. Primero calcula la red con la función de propagación.
. Necesitamos un resultado deseado para el patrón dado, así que debemos incluir esta información.
. Calcular el error cuadrático y el error de capa para la capa de salida.
. Calcular el valor de error de la capa actual.
. Actualizamos los pesos para cada neurona aplicando la regla.
. La misma regla se aplica para las capas ocultas y de entrada. Sin embargo, el error de capas ocultas se calcula de una manera diferente.
-----------------------------------------------------------------------------------------------------------------------------------------

Sistema Operativo: Windows 10 Pro
Procesador: Intel(R) Core(TM) i7 @ 2.20GHz
Memoria RAM: 4.00 GB
Tipo de sistema: Sistema Operativo de 64 bits.

REFERENCIAS:

- http://www.learnartificialneuralnetworks.com/backpropagation.html
- https://machinelearningmastery.com/implement-backpropagation-algorithm-scratch-python/
