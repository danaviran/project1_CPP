#include <cmath>
#include <iostream>
#include "Matrix.h"

// Nums
#define INIT_VALUE 0
#define CONSTRUCTOR_INIT_DIMS 1
#define VECTOR_COL_NUM 1
#define VECTOR_COL_INDEX 0
#define MINIMAL_VAL 0.1
// Signs
#define NEW_LINE "\n"
#define SPACE " "
#define DOUBLE_SPACE "  "
#define DOUBLE_ASTERIKS "**"
// Errors
#define LENGTH_ERROR "Error: length/width of given matrix is not valid.\n"
#define INDEX_ERROR "Error: index is not valid.\n"
#define FILE_ERROR "Error: error in file.\n"

/**
 * Destructor Helper - Private Function
 * @param matrix_p float** matrix to delete
 * @param row_num number of rows in matrix
 */
void Matrix::delete_matrix(float ***matrix_p, int row_num)
{
  if (*matrix_p != nullptr)
    {
      for (int i=0;i<row_num; i++)
        {
          if (*matrix_p != nullptr)
            {
              delete[] (*matrix_p)[i];
            }
        }
      delete[] *matrix_p;
      *matrix_p = nullptr;
    }
}

/**
 * Constructor Helper - Private Function
 * @param new_rows
 * @param new_cols
 * @return
 */
void Matrix::build_new_matrix(int new_rows, int new_cols)
{
  if (matrix != nullptr)
    {
      delete_matrix (&matrix, dims.rows);
    }
  matrix = new float*[new_rows];
  for(int i = 0; i < new_rows; i++)
    {
      matrix[i] = new float[new_cols];
      for(int j=0; j< new_cols; j++)
        {
          matrix[i][j] = INIT_VALUE;
        }
    }
  dims.rows = new_rows;
  dims.cols = new_cols;
}

/**
 * Constructor Helper - Private Function
 * Gets a Const Matrix, fills This Matrix with it's elements
 * @param matrix_2
 */
void Matrix:: fill_matrix(const Matrix& matrix_2)
{
  for (int i=0; i<dims.rows; i++)
    {
      for (int j=0;j<dims.cols; j++)
        {
          matrix[i][j] = matrix_2.matrix[i][j];
        }
    }
}

/**
 * Constructor
 * @param rows
 * @param cols
 */
Matrix::Matrix (int rows, int cols)
{
  if (rows<=0 || cols<=0)
    {
      throw std::length_error(LENGTH_ERROR);
    }
  build_new_matrix (rows, cols);
}

/**
 * Copy Constructor
 * @param m
 */
Matrix::Matrix (const Matrix &m)
{
  build_new_matrix (m.get_rows(), m.get_cols());
  fill_matrix (m);
}

/**
 * Destructor
 */
Matrix:: ~Matrix()
{
  delete_matrix(&matrix, dims.rows);
}

/**
 * Operator '='
 * @param m
 * @return
 */
Matrix& Matrix:: operator=(const Matrix& m)
{
  if (this == &m || matrix == m.matrix)
    {
      return *this;
    }
  build_new_matrix (m.get_rows(), m.get_cols());
  fill_matrix (m);
  return *this;
}

/**
 * Print Matrix function
 */
void Matrix:: plain_print() const
{
  for (int i=0; i<dims.rows; i++)
    {
      for(int j=0; j<dims.cols; j++)
        {
          if (j==dims.cols-1)
            {
              cout<<matrix[i][j]<< SPACE << endl;
            }
          else
            {
              cout<<matrix[i][j] << SPACE;
            }
        }
    }
  cout<<NEW_LINE;
}

/**
 * Transposes this Matrix
 * @return Transposed Matrix
 */
Matrix& Matrix::transpose()
{
  int new_rows = dims.cols, new_cols = dims.rows;
  Matrix transposed = Matrix(new_rows, new_cols);
  for (int i = 0; i < dims.rows; ++i)
    {
      for (int j = 0; j < dims.cols; ++j)
        {
          transposed.matrix[j][i] = matrix[i][j];
        }
    }
  build_new_matrix (new_rows, new_cols);
  fill_matrix (transposed);
  delete_matrix (&(transposed.matrix), transposed.dims.rows);
  return *this;
}

/**
 * Vectorizes this Matrix
 * @return Vectorized Matrix
 */
Matrix& Matrix::vectorize ()
{
  Matrix vector = Matrix(dims.rows*dims.cols,VECTOR_COL_NUM);
  for(int i=0;i< dims.rows;i++)
    {
      for (int j = 0; j<dims.cols; j++)
        {
          vector.matrix[i*dims.cols+j][VECTOR_COL_INDEX] = matrix[i][j];
        }
    }
  build_new_matrix (dims.rows*dims.cols, VECTOR_COL_NUM);
  fill_matrix (vector);
  delete_matrix (&(vector.matrix), vector.dims.rows);
  return *this;
}

/**
 * Dot multiplication of This Matrix and the other's elements
 * @param m Other const Matrix
 * @return A new Matrix
 * @owenership Weak, responsibility of the user
 */
Matrix& Matrix:: dot(const Matrix& m)
{
  if (dims.rows == m.dims.rows && dims.cols == m.dims.cols)
    {
      auto *dot = new Matrix(dims.rows, dims.cols);
      for (int i=0;i<dims.rows;i++)
        {
          for (int j=0;j<dims.cols;j++)
            {
              dot->matrix[i][j] = matrix[i][j] * m.matrix[i][j];
            }
        }
      return *dot;
    }
  else
    {
      throw std::length_error(LENGTH_ERROR);
    }
}

/**
 * Returns the Norm of the Matrix
 * @return A float representing the Norm
 */
float Matrix:: norm()
{
  float square_sum = 0;
  for (int i = 0; i < dims.rows; i++)
    {
      for (int j = 0; j < dims.cols; j++)
        {
          square_sum += (matrix[i][j] * matrix[i][j]);
        }
    }
  auto res = std::sqrt(square_sum);
  return res;
}

/**
 * Operator +=. An addition of this Matrix and another
 * @param m
 * @return This Matrix after the operation
 */
Matrix Matrix:: operator+=(const Matrix& m)
{
  if (this->dims.rows == m.dims.rows || this->dims.cols == m.dims.cols)
    {
      for(int i=0;i< dims.rows;i++)
        {
          for(int j=0;j< dims.cols;j++)
            {
              matrix[i][j] += m.matrix[i][j];
            }
        }
    }
  else
    {
      throw std::length_error(LENGTH_ERROR);
    }
  return *this;
}

/**
 * Operator * scalar of type float
 * @param scalar
 * @return This Matrix after the operation
 */
Matrix Matrix:: operator*(float scalar) const
{
  auto *mult = new Matrix(dims.rows, dims.cols);
  mult->fill_matrix (*this);
  for(int i=0;i< dims.rows;i++)
    {
      for(int j=0;j< dims.cols;j++)
        {
          mult->matrix[i][j] *= scalar;
        }
    }
  return *mult;
}

/**
 * Index Operator () - Permits assigment to Matrix element
 * @param i,j integers representing the wanted index
 * @return the matrix element in index position
 */
float& Matrix:: operator()(int i, int j)
{
  if ((i*dims.cols+j) >= dims.cols*dims.rows
  || i<INIT_VALUE || j<INIT_VALUE || j>=dims.cols || i>=dims.rows)
    {
      throw std::out_of_range(INDEX_ERROR);
    }
  return matrix[i][j];
}

/**
 * Index Operator () - Does not permit assigment to Matrix element
 * @param i,j integers representing the wanted index
 * @return the matrix element in index position
 */
float& Matrix:: operator()(int i, int j) const
{
  if ((i*dims.cols+j) >= dims.cols*dims.rows
  || i<INIT_VALUE || j<INIT_VALUE || j>=dims.cols || i>=dims.rows)
    {
      throw std::out_of_range(INDEX_ERROR);
    }
  return matrix[i][j];
}


/**
 * Index Operator [] - permits assigment to Matrix element
 * @param k integer representing the wanted index
 * @return the matrix element in the k position
 */
float& Matrix::operator[](int k)
{
  int counter = 0;
  for (int i=0; i<dims.rows; i++)
    {
      for (int j=0; j<dims.cols; j++)
        {
          counter++;
          if (counter-1 == k)
            {
              return matrix[i][j];
            }
        }
    }
  throw std::out_of_range(INDEX_ERROR);
}

/**
 * Index Operator [] - Does not permit assigment to Matrix element
 * @param k integer representing the wanted index
 * @return the matrix element in the k position
 */
float& Matrix::operator[](int k) const
{
  int counter = 0;
  for (int i=0; i<dims.rows; i++)
    {
      for (int j=0; j<dims.cols; j++)
        {
          counter++;
          if (counter-1 == k)
            {
                  return matrix[i][j];
            }
        }
    }
  throw std::out_of_range(INDEX_ERROR);
}

/**
 * Friend of Matrix Class - Ostream Operator of Matrix
 * @param os wanted ostream
 * @param m wanted Matrix
 * @return ostream element
 */
std::ostream& operator<<(std::ostream& os, const Matrix& m)
{
  for (int i=0; i<m.get_rows();i++)
    {
      for (int j=0; j<m.get_cols(); j++)
        {
          if (m(i,j) > MINIMAL_VAL)
            {
              cout << DOUBLE_ASTERIKS;
            }
          else
            {
              cout << DOUBLE_SPACE;
            }
        }
      cout << NEW_LINE;
    }
  return os;
}

/**
 * Friend of Matrix Class - Istream Operator of Matrix
 * @param is wanted istream
 * @param m wanted Matrix to read into
 * @return istream element
 */
std::istream& operator>>(std::istream& is, Matrix& m)
{
  if (is.good() && !is.eof())
    {
      for (int i =0; i<m.dims.rows && (!is.eof()); i++)
        {
          is.read ((char*) m.matrix[i], (m.dims.cols)*sizeof (float));
        }
      return is;
    }
  throw std::runtime_error(FILE_ERROR);
}

/**
 * Friend of Matrix Class - Operator of Addition of two Matrix
 * @param a Matrix a
 * @param b Matrix b
 * @return Result New Matrix
 */
Matrix& operator+(const Matrix& a, const Matrix& b)
{
  if (a.get_rows() == b.get_rows() || a.get_cols() == b.get_cols())
    {
      auto *addition = new Matrix(a.get_rows(), a.get_cols());
      *addition+=a;
      *addition+=b;
      return *addition;
    }
  else
    {
      throw std::length_error(LENGTH_ERROR);
    }
}

/**
 * Friend of Matrix Class - Operator of Multiplication of two Matrix
 * @param a Matrix a
 * @param b Matrix b
 * @return Result New Matrix
 */
Matrix& operator*(const Matrix& a, const Matrix& b)
{
  if (a.get_cols() == b.get_rows())
    {
      auto *mult = new Matrix(a.get_rows(), b.get_cols());
      for(int i = 0; i < a.get_rows(); ++i)
        {
          for(int j = 0; j < b.get_cols(); ++j)
            {
              for(int k = 0; k < b.get_rows(); ++k)
                {
                  (*mult).matrix[i][j] += a(i,k) * b(k,j);
                }
            }
        }
      return *mult;
    }
  else
    {
      throw std::length_error(LENGTH_ERROR);
    }
}

/**
 * Friend of Matrix Class - Operator of Scalar Multiplication Matrix
 * @param scalar float to multiply with
 * @param a Matrix
 * @return Result New Matrix
 */
Matrix operator*(float scalar, const Matrix& a)
{
  auto *mult = new Matrix(a);
  *mult = mult->operator* (scalar);
  return *mult;
}