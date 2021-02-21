#ifndef TINYMATH_H
#define TINYMATH_H

#include <cmath>

// Forward references of each of the structs
struct Vector3D;
struct Vector2D;
struct Matrix3D;

// Vector3D performs vector operations with 3-dimensions
// The purpose of this class is primarily for 3D graphics
// applications.
struct Vector3D {
  // Note: x,y,z are a convention
  // x,y,z could be position, but also any 3-component value.
  float x, y, z;

  // Default conostrutcor
  // 'why default?'
  // https://stackoverflow.com/questions/20828907/the-new-keyword-default-in-c11
  Vector3D() = default;

  // The "Real" constructor we want to use.
  // This initializes the values x,y,z
  Vector3D(float a, float b, float c) : x{a}, y{b}, z{c} {}

  // Index operator, allowing us to access the individual
  // x,y,z components of our vector.
  float& operator[](int i) {
    // x,y,z are stored continuously, so we could recognize x as the first float
    // number of a float[3] array
    //       There is no code to change here.
    return ((&x)[i]);
  }

  // Index operator, allowing us to access the individual
  // x,y,z components of our vector.
  const float& operator[](int i) const {
    // x,y,z are stored continuously, so we could recognize x as the first float
    // number of a float[3] array
    //       There is no code to change here.
    return ((&x)[i]);
  }

  // Multiplication Operator
  // Multiply vector by a uniform-scalar.
  Vector3D& operator*=(float s) {
    x *= s;
    y *= s;
    z *= s;
    return (*this);
  }

  // Division Operator
  Vector3D& operator/=(float s) {
    x /= s;
    y /= s;
    z /= s;
    return (*this);
  }

  // Addition operator
  Vector3D& operator+=(const Vector3D& v) {
    x += v.x;
    y += v.y;
    z += v.z;
    return (*this);
  }

  // Subtraction operator
  Vector3D& operator-=(const Vector3D& v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return (*this);
  }

  // Equal operator
  bool operator==(const Vector3D& v) const {
    return x == v.x && y == v.y && z == v.z;
  }

  // UnEqual operator
  bool operator!=(const Vector3D& v) const {
    return x != v.x || y != v.y || z != v.z;
  }
};

// Compute the dot product of a Vector3D
inline float Dot(const Vector3D& a, const Vector3D& b) {
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

// Multiplication of a vector by a scalar values
inline Vector3D operator*(const Vector3D& v, float s) {
  Vector3D vec(v.x * s, v.y * s, v.z * s);
  return vec;
}

// Division of a vector by a scalar value.
inline Vector3D operator/(const Vector3D& v, float s) {
  Vector3D vec(v.x / s, v.y / s, v.z / s);
  return vec;
}

// Negation of a vector
// Use Case: Sometimes it is handy to apply a force in an opposite direction
inline Vector3D operator-(const Vector3D& v) {
  Vector3D vec(-v.x, -v.y, -v.z);
  return vec;
}

// Return the magnitude of a vector
inline float Magnitude(const Vector3D& v) {
  return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}

// Add two vectors together
inline Vector3D operator+(const Vector3D& a, const Vector3D& b) {
  Vector3D vec(a.x + b.x, a.y + b.y, a.z + b.z);
  return vec;
}

// Subtract two vectors
inline Vector3D operator-(const Vector3D& a, const Vector3D& b) {
  Vector3D vec(a.x - b.x, a.y - b.y, a.z - b.z);
  return vec;
}

// Vector Projection
inline Vector3D Project(const Vector3D& a, const Vector3D& b) {
  return b * (Dot(a, b) / Dot(b, b));
}

// Set a vectors magnitude to 1
// Note: This is NOT generating a normal vector
inline Vector3D Normalize(const Vector3D& v) { return v / Magnitude(v); }

// a x b (read: 'a crossed b')
// Produces a new vector perpendicular to a and b.
// (So long as a and b are not parallel which returns zero vector)
inline Vector3D CrossProduct(const Vector3D& a, const Vector3D& b) {
  Vector3D vec(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z,
               a.x * b.y - a.y * b.x);
  return vec;
}

// Vector2D performs vector operations with 2-dimensions
// The purpose of this class is primarily for 2D graphics
// applications.
struct Vector2D : public Vector3D {
  Vector2D() = default;

  Vector2D(float a, float b) : Vector3D(a, b, 0) {}
};

enum Direction { UP, RIGHT, DOWN, LEFT };

inline Direction VectorDirectionSDL(Vector2D target) {
  Vector2D compass[] = {
      Vector2D(0.0f, -1.0f),  // up
      Vector2D(-1.0f, 0.0f),  // right
      Vector2D(0.0f, 1.0f),   // down
      Vector2D(1.0f, 0.0f)    // left
  };
  float max = 0.0f;
  unsigned int best_match = -1;
  for (unsigned int i = 0; i < 4; i++) {
    float dot_product = Dot(Normalize(target), compass[i]);
    if (dot_product > max) {
      max = dot_product;
      best_match = i;
    }
  }
  return (Direction)best_match;
}

// Matrix 3D represents 3x3 matrices in Math
struct Matrix3D {
 private:
  float n[3][3];  // Store each value of the matrix

 public:
  Matrix3D() = default;

  // Matrix constructor with 9 scalar values.
  // Row-major order
  Matrix3D(float n00, float n01, float n02, float n10, float n11, float n12,
           float n20, float n21, float n22) {
    n[0][0] = n00;
    n[0][1] = n01;
    n[0][2] = n02;
    n[1][0] = n10;
    n[1][1] = n11;
    n[1][2] = n12;
    n[2][0] = n20;
    n[2][1] = n21;
    n[2][2] = n22;
  }

  // Matrix constructor from three vectors, putting each Vector to each column
  Matrix3D(const Vector3D& a, const Vector3D& b, const Vector3D& c) {
    n[0][0] = a.x;
    n[0][1] = b.x;
    n[0][2] = c.x;
    n[1][0] = a.y;
    n[1][1] = b.y;
    n[1][2] = c.y;
    n[2][0] = a.z;
    n[2][1] = b.z;
    n[2][2] = c.z;
  }

  // Index operator with two dimensions
  // Example: M(1,1) returns row 1 and column 1 of matrix M.
  float& operator()(int i, int j) { return (n[i][j]); }

  // Index operator with two dimensions
  // Example: M(1,1) returns row 1 and column 1 of matrix M.
  const float& operator()(int i, int j) const { return (n[i][j]); }

  // Return a row from a matrix as a vector.
  Vector3D& operator[](int i) { return (*reinterpret_cast<Vector3D*>(n[i])); }

  // Return a row from a matrix as a vector.
  const Vector3D& operator[](int i) const {
    return (*reinterpret_cast<const Vector3D*>(n[i]));
  }

  bool operator==(const Matrix3D& m) const {
    return n[0][0] == m[0][0] && n[0][1] == m[0][1] && n[0][2] == m[0][2] &&
           n[1][0] == m[1][0] && n[1][1] == m[1][1] && n[1][2] == m[1][2] &&
           n[2][0] == m[2][0] && n[2][1] == m[2][1] && n[2][2] == m[2][2];
  }
  bool operator!=(const Matrix3D& m) const { return !(this->operator==(m)); }

  // Return a column from a matrix as a vector.
  Vector3D column(int j) const {
    Vector3D vec{n[0][j], n[1][j], n[2][j]};
    return vec;
  }
};

// Matrix Multiplication
inline Matrix3D operator*(const Matrix3D& A, const Matrix3D& B) {
  Matrix3D n;
  n[0][0] = Dot(A[0], B.column(0));
  n[0][1] = Dot(A[0], B.column(1));
  n[0][2] = Dot(A[0], B.column(2));
  n[1][0] = Dot(A[1], B.column(0));
  n[1][1] = Dot(A[1], B.column(1));
  n[1][2] = Dot(A[1], B.column(2));
  n[2][0] = Dot(A[2], B.column(0));
  n[2][1] = Dot(A[2], B.column(1));
  n[2][2] = Dot(A[2], B.column(2));
  return n;
}

// Matrix multiply by a vector
inline Vector3D operator*(const Matrix3D& M, const Vector3D& v) {
  Vector3D vec;
  vec[0] = Dot(M[0], v);
  vec[1] = Dot(M[1], v);
  vec[2] = Dot(M[2], v);
  return vec;
}

#endif  // TINYMATH_H