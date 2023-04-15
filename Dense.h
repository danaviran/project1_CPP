#ifndef DENSE_H
#define DENSE_H

#include "Activation.h"

/**
 * Dense Class
 * Creates Object of Current Layer in the Neural Network
 * For full Documentation of methods check the Dense.cpp file
 */
class Dense
{
  // Privates
  const Matrix& _weights; // Current Layer's Weight
  const Matrix& _bias;  // Current Layer's Bias
  const active_func_pointer _activation; // Current Layer's Activation Function

 public:
  // Constructor
  Dense(Matrix& weights, Matrix& bias, active_func_pointer ActivationFunction);

  // Getters
  Matrix get_weights() const {return _weights;}
  Matrix get_bias() const {return _bias;}
  active_func_pointer get_activation() const {return _activation;}

  // Operator - The Operation of Layer on Matrix
  Matrix operator()(Matrix& input);
};

#endif //DENSE_H
