#include "Dense.h"

// Constructor
Dense:: Dense(Matrix& weights, Matrix& bias, active_func_pointer
ActivationFunction)
: _weights(weights), _bias(bias), _activation(ActivationFunction)
{
}

/**
 * Operator of Activation of Current Layer on Input Matrix
 * @param input Matrix reference
 * @return A new Matrix representing the result of activation
 */
Matrix Dense:: operator()(Matrix& input)
{
  return _activation((_weights*input)+_bias);
}