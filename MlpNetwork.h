#ifndef MLPNETWORK_H
#define MLPNETWORK_H

#include "Dense.h"

#define MLP_SIZE 4

/**
 * @struct digit
 * @brief Identified (by Mlp network) digit with
 *        the associated probability.
 * @var value - Identified digit value
 * @var probability - identification probability
 */
typedef struct digit {
	unsigned int value;
	float probability;
} digit;

const matrix_dims img_dims = {28, 28};
const matrix_dims weights_dims[] = {{128, 784},
									{64,  128},
									{20,  64},
									{10,  20}};
const matrix_dims bias_dims[] = {{128, 1},
								 {64,  1},
								 {20,  1},
								 {10,  1}};

/**
 * MlpNetwork Class
 * Represents the whole Neural Network Operation
 * For full Documentation of methods check the MlpNetwork.cpp file
 */
class MlpNetwork
{
  // Private Members
  Matrix *_weights;
  Matrix *_biases;
  digit *_result;
  // Private Helper Function
  Matrix activate_layers(Matrix& input);
 public:
  // Default Constructor
  MlpNetwork(const Matrix weights[], const Matrix biases[]);
  // Copy Constructor
  MlpNetwork(const MlpNetwork& network): MlpNetwork (network._weights,
                                                     network._biases){};
  // Assignment Operator
  MlpNetwork& operator=(MlpNetwork network);
  // Destructor
  ~MlpNetwork();
  // Operator Of Activation of the whole Neural Network Operation
  digit& operator()(Matrix& input);
};

#endif // MLPNETWORK_H