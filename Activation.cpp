#include "Activation.h"
#include <cmath>

#define VECTOR_COL_INDEX 0
#define INIT_VALUE 0

/**
 * Replaces each negative element in Matrix to zero
 * @param m Matrix Reference
 * @return A new Matrix after the operation
 */
Matrix activation::relu(Matrix& m)
{
  auto *result = new Matrix(m.get_rows(),m.get_cols());
  for (int i=0; i<m.get_rows();i++)
    {
      for (int j=0; j<m.get_cols();j++)
        {
          if (m.operator() (i,j) < INIT_VALUE)
            {
              result->operator() (i,j) = INIT_VALUE;
            }
          else
            {
              result->operator() (i,j) = m.operator() (i,j);
            }
        }
    }
  return *result;
}

/**
 * Creates Distribution Vector from given Matrix
 * @param m Matrix Reference
 * @return A new Matrix after the operation
 */
Matrix activation::softmax(Matrix& m)
{
  auto *result = new Matrix
      (m.get_rows(), m.get_cols());
  float sum = 0;
  for (int i=0; i<result->get_rows();i++)
    {
      for (int j=0; j<result->get_cols();j++)
        {
          result->operator()
          (i, j) = std::exp(m.operator() (i,j));
          sum += (std::exp (m.operator() (i,j)));
        }
    }
  for (int i=0; i<result->get_rows();i++)
    {
      for (int j=0; j<result->get_cols();j++)
        {
          result->operator() (i, j) /= sum;
        }
    }
  return *result;
}

