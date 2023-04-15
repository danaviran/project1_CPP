#include "MlpNetwork.h"

#define NUM_OF_LAYERS 4
#define INIT_VAL 0
#define INIT_F_VAL 0.0
#define VECTOR_COL_INDEX 0
#define DISTRIBUTION_VECTOR_ROWS 10
#define FIRST_LAYER 0
#define SECOND_LAYER 1
#define THIRD_LAYER 2
#define FOURTH_LAYER 3

/**
 * Main Constructor
 * @param weights Matrix Array - each matrix represents weight of it's layer
 * @param biases Matrix Array - each matrix represents bias of it's layer
 */
MlpNetwork:: MlpNetwork(const Matrix weights[], const Matrix biases[]):
    _weights(const_cast<Matrix *>(weights)),
    _biases(const_cast<Matrix *>(biases))
{
  _weights = new Matrix[NUM_OF_LAYERS];
  for (int i=0;i<NUM_OF_LAYERS;i++)
    {
      _weights[i] = weights[i];
    }
  _biases = new Matrix[NUM_OF_LAYERS];
  for (int i=0;i<NUM_OF_LAYERS;i++)
    {
      _biases[i] = biases[i];
    }
  _result = new digit{INIT_VAL,INIT_VAL};
}

/**
 * Assignment Operator
 * @param network another MlpNetwork object to copy from
 * @return This MlpNetwork after copy operation
 */
MlpNetwork& MlpNetwork:: operator=(const MlpNetwork network)
{
  if (this != &network)
    {
      _weights = new Matrix[NUM_OF_LAYERS];
      for (int i=0;i<NUM_OF_LAYERS;i++)
        {
          _weights[i] = network._weights[i];
        }
      _biases = new Matrix[NUM_OF_LAYERS];
      for (int i=0;i<NUM_OF_LAYERS;i++)
        {
          _biases[i] = network._biases[i];
        }
      _result = new digit{INIT_VAL,INIT_VAL};
    }
  return *this;
}

/**
 * Destructor of Matrix Arrays Created in the Class
 * Weak Ownership for the Matrix inside Arrays (User responsibility)
 * Deletes also the created Digit Struct object
 */
MlpNetwork:: ~MlpNetwork()
{
  delete[] _weights;
  delete[] _biases;
  delete _result;
}

/**
 * Private Helper: Activation of the whole Neural Network Operation
 * @param input The input Matrix representing an image
 * @return Result New Matrix (Distribution Vector)
 */
Matrix MlpNetwork:: activate_layers(Matrix& input)
{
  // Creation of Layer Objects
  Dense first_layer = {_weights[FIRST_LAYER], _biases
  [FIRST_LAYER],activation::relu};
  Matrix result_layer1 = first_layer.operator() (input);
  Dense second_layer = {_weights[SECOND_LAYER],_biases
  [SECOND_LAYER],activation::relu};
  Matrix result_layer2 = second_layer.operator() (result_layer1);
  Dense third_layer = {_weights[THIRD_LAYER], _biases
  [THIRD_LAYER], activation::relu};
  Matrix result_layer3 = third_layer.operator() (result_layer2);
  Dense softmax_layer = {_weights[FOURTH_LAYER], _biases
  [FOURTH_LAYER], activation::softmax};
  Matrix result_layer4 = softmax_layer.operator() (result_layer3);
  // Result Vector
  return result_layer4;
}

/**
 * Operator Of Activation of the whole Neural Network Operation
 * @param input The input Matrix representing an image
 * @return Digit Struct of Result
 */
digit& MlpNetwork:: operator()(Matrix& input)
{
  // result of Neural Network Operation
  Matrix result = activate_layers (input);
  float max_prob = INIT_F_VAL; // Initialization of Max Probability
  unsigned int digit = INIT_VAL; // Initialization of First Digit Index
  for(int i=0;i<DISTRIBUTION_VECTOR_ROWS;i++)
    {
      if (max_prob < result.operator() (i,VECTOR_COL_INDEX))
        {
          max_prob = result.operator() (i,VECTOR_COL_INDEX);
          digit = i;
        }
    }
   // Return Result of Struct Digit
  _result->value = digit;
  _result->probability = max_prob;
  return *_result;
}