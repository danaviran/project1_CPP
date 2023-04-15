#include <iostream>
using std::cout;
using std::endl;

// Matrix.h
#ifndef MATRIX_H
#define MATRIX_H
#define INIT_DIMS 0
#define CONSTRUCTOR_INIT_DIMS 1

/**
 * @struct matrix_dims
 * @brief Matrix dimensions container. Used in MlpNetwork.h and main.cpp
 */
typedef struct matrix_dims
{
    int rows, cols;
} matrix_dims;

/**
 * @class Matrix
 * For full Documentation of methods check the Matrix.cpp file
 */
class Matrix
{
  // Private Members
  matrix_dims dims{INIT_DIMS,INIT_DIMS};
  float **matrix = nullptr;
  // Helper Private Functions
  void build_new_matrix(int rows, int cols);
  void fill_matrix (const Matrix& matrix);
  void delete_matrix (float ***matrix_p, int row_num);

 public:
  // Constructors & Destructor
  Matrix(int rows, int cols); // Main Constructor
  // Default Constructor
  Matrix(): Matrix (CONSTRUCTOR_INIT_DIMS,CONSTRUCTOR_INIT_DIMS) {};
  Matrix(Matrix const &m); // Copy Constructor
  Matrix& operator=(const Matrix& matrix); // Assignment Operator
  ~Matrix(); // Destructor

  // Getters
  int get_rows() const{return dims.rows;}
  int get_cols() const{return dims.cols;}

  // Getters and Assigment Operators
  float& operator()(int i, int j);
  float& operator()(int i, int j) const;
  float& operator[](int k);
  float& operator[](int k) const;

  // Matrix operations
  Matrix& transpose();
  Matrix& vectorize();
  Matrix& dot(const Matrix& m);
  float norm();

  // Arithmetic Operators
  Matrix operator+=(const Matrix& matrix);
  Matrix operator*(float scalar) const;

  // Print & IO
  void plain_print() const;
  friend std::ostream& operator<<(std::ostream&, const Matrix&);
  friend std::istream& operator>>(std::istream& ,Matrix&);

  // Friend Functions
  friend Matrix& operator+(const Matrix& a, const Matrix& b);
  friend Matrix& operator*(const Matrix& a, const Matrix& b);
  friend Matrix operator*(float scalar, const Matrix& b);
};

#endif //MATRIX_H