#ifndef ACTIVATION_H
#define ACTIVATION_H

#include "Matrix.h"

/**
 * Type Declaration of Pointer to Activation Functions
 * Both Get a Reference to a Matrix and return a New Matrix after Activation
 */
typedef Matrix (*active_func_pointer)(Matrix& m);

/**
 * A Namespace to define the Two Activation Functions
 */
namespace activation
{
    /**
     * Replaces each negative element in Matrix to zero
     * @param m Matrix Reference
     * @return A new Matrix after the operation
     */
    Matrix relu(Matrix& m);

    /**
     * Creates Distribution Vector from given Matrix
     * @param m Matrix Reference
     * @return A new Matrix after the operation
     */
    Matrix softmax(Matrix& m);
}

#endif //ACTIVATION_H