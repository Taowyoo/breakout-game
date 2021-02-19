// Add your unit tests somewhere in this file
// Provide sufficient 'coverage' of funtions you have implemented.
#include <iostream>

#include "TinyMath.hpp"

// Add a 1 vector with a 0 vector.
bool unitTest1() {
  puts("Testing: Vector3D + Vector3D");
  Vector3D a(1, 1, 1);
  Vector3D b(0, 0, 0);
  Vector3D c = a + b;

  if (c.x == 1 && c.y == 1 && c.z == 1) {
    return true;
  }
  return false;
}

// Testing: Vector3D operator[], value access
bool unitTest2() {
  puts("Testing: Vector3D operator[], value access");
  Vector3D a(1, 2, 3);
  if (a[0] == 1 && a[1] == 2 && a[2] == 3) {
    return true;
  }
  return false;
}
// Testing: Vector3D operator[], value modify
bool unitTest3() {
  puts("Testing: Vector3D operator[], value modify");
  Vector3D a(1, 2, 3);

  if (a[0] == 1 && a[1] == 2 && a[2] == 3) {
    a[0] = 5;
    a[1]++;
    a[2]--;
    if (a[0] == 5 && a[1] == 3 && a[2] == 2) {
      return true;
    }
  }
  return false;
}
// Testing: Vector3D operator*= with number
bool unitTest4() {
  puts("Testing: Vector3D operator*= with number");
  Vector3D a(1, 2, 3);
  a *= 2;
  if (a[0] == 2 && a[1] == 4 && a[2] == 6) {
    return true;
  }
  return false;
}
// Testing: Vector3D operator/= with number
bool unitTest5() {
  puts("Testing: Vector3D operator/= with number");
  Vector3D a(1, 2, 3);
  a /= 2;
  if (a[0] == 0.5 && a[1] == 1 && a[2] == 1.5) {
    return true;
  }
  return false;
}
// Testing: Vector3D operator!=
bool unitTest6() {
  puts("Testing: Vector3D operator!=");
  Vector3D a(1, 2, 3);
  Vector3D b(1, 2, 3);
  return a == b;
}
// Testing: Vector3D operator==
bool unitTest7() {
  puts("Testing: Vector3D operator==");
  Vector3D a(1, 2, 3);
  Vector3D b(2, 3, 4);
  return a != b;
}
// Testing: Vector3D dot product
bool unitTest8() {
  puts("Testing: Vector3D dot product");
  Vector3D a(1, 2, 3);
  Vector3D b(-1, -2, -3);
  if (Dot(a, b) == -14) {
    return true;
  }
  return false;
}
// Testing: Vector3D operator* with number
bool unitTest9() {
  puts("Testing: Vector3D operator* with number");
  Vector3D a(1, 2, 3);
  a = a * 2;
  if (a[0] == 2 && a[1] == 4 && a[2] == 6) {
    return true;
  }
  return false;
}
// Testing: Vector3D operator/ with number
bool unitTest10() {
  puts("Testing: Vector3D operator/ with number");
  Vector3D a(1, 2, 3);
  a = a / 2;
  if (a[0] == 0.5 && a[1] == 1 && a[2] == 1.5) {
    return true;
  }
  return false;
}
// Testing: Negation of a Vector3D
bool unitTest11() {
  puts("Testing: Negation of a Vector3D");
  Vector3D a(1, 2, 3);
  a = -a;
  if (a[0] == -1 && a[1] == -2 && a[2] == -3) {
    return true;
  }
  return false;
}
// Testing: Magnitude of a Vector3D
bool unitTest12() {
  puts("Testing: Magnitude of a Vector3D");
  Vector3D a(2, 3, 6);
  return Magnitude(a) == 7;
}

// Testing: Vector3D - Vector3D
bool unitTest13() {
  puts("Testing: Vector3D - Vector3D");
  Vector3D a(1, 1, 1);
  Vector3D b(2, 3, 4);
  Vector3D c = b - a;

  if (c.x == 1 && c.y == 2 && c.z == 3) {
    return true;
  }
  return false;
}

// Testing: Vector3D Projection
bool unitTest14() {
  puts("Testing: Vector3D Projection");
  Vector3D a(3, 4, 5);
  Vector3D b(7, 14, 35);
  Vector3D c(6, 12, 30);
  Vector3D d = Project(a, b) * 5;
  return d == c;
}

// Testing: Vector3D Normalization
bool unitTest15() {
  puts("Testing: Vector3D Normalization");
  Vector3D a(12, 15, 16);
  Vector3D b(12.0 / 25, 15.0 / 25, 16.0 / 25);
  Vector3D c = Normalize(a);
  return c == b;
}

// Testing: Vector3D Cross Production
bool unitTest16() {
  puts("Testing: Vector3D Cross Production");
  Vector3D a(1, 2, 3);
  Vector3D b(1, 5, 7);
  Vector3D c(-1, -4, 3);
  return CrossProduct(a, b) == c;
}

// Testing: Matrix3D Constructor
bool unitTest17() {
  {
    puts("Testing: Matrix3D Construct with 3 vector");
    Vector3D a(1, 2, 3);
    Vector3D b(4, 5, 6);
    Vector3D c(7, -4, 9);
    Matrix3D mat(a, b, c);

    if (!(mat(0, 0) == 1 && mat(1, 0) == 2 && mat(2, 0) == 3 &&
          mat(0, 2) == 7 && mat(1, 2) == -4 && mat(2, 2) == 9)) {
      return false;
    }
  }
  puts("Testing: Matrix3D Construct with 9 value");
  Matrix3D mat(0, 1, 2, 10, 11, 12, 20, 21, 22);
  if (!(mat(0, 0) == 0 && mat(1, 1) == 11 && mat(2, 2) == 22 &&
        mat(0, 2) == 2 && mat(2, 0) == 20)) {
    return false;
  }
  return true;
}

// Testing: Matrix3D get row as vector and get column as vector
bool unitTest18() {
  puts("Testing: Matrix3D get row as vector");
  Vector3D a(1, 2, 3);
  Vector3D b(4, 5, 6);
  Vector3D c(7, -4, 9);
  Matrix3D mat(a, b, c);
  Vector3D d(1, 4, 7);
  if (mat[0] != d) {
    return false;
  }

  puts("Testing: Matrix3D get column as vector");
  if (mat.column(0) != a) {
    return false;
  }
  return true;
}

// Testing: Matrix3D * Matrix3D
bool unitTest19() {
  puts("Testing: Matrix3D * Matrix3D");
  Vector3D a(1, 2, 3);
  Vector3D b(4, 5, 6);
  Vector3D c(7, 8, 9);
  Matrix3D mat(a, b, c);

  Vector3D aa(30, 36, 42);
  Vector3D bb(66, 81, 96);
  Vector3D cc(102, 126, 150);
  Matrix3D mat2(aa, bb, cc);
  if (mat * mat == mat2) {
    return true;
  }
  return false;
}
// Testing: Matrix3D multiply by a vector
bool unitTest20() {
  puts("Testing: Matrix3D multiply by a vector");
  Vector3D a(1, 2, 3);
  Vector3D b(4, 5, 6);
  Vector3D c(7, 8, 9);
  Matrix3D mat(a, b, c);

  Vector3D d(-1, -2, -3);

  Vector3D res(-30, -36, -42);

  if (mat * d == res) {
    return true;
  }
  return false;
}

// Testing: Matrix3D operator== and operator!=
bool unitTest21() {
  puts("Testing: Matrix3D operator==");
  Vector3D a(1, 2, 3);
  Vector3D b(4, 5, 6);
  Vector3D c(7, 8, 9);
  Matrix3D mat(a, b, c);

  Vector3D a2(1, 2, 3);
  Vector3D b2(4, 10, 6);
  Vector3D c2(7, 8, 9);
  Matrix3D mat2(a2, b2, c2);

  if (!(mat == mat)) {
    return false;
  }
  puts("Testing: Matrix3D operator!=");

  if (!(mat != mat2)) {
    return false;
  }
  return true;
}

bool (*unitTests[])(void) = {
    unitTest1,  unitTest2,  unitTest3,  unitTest4,  unitTest5,  unitTest6,
    unitTest7,  unitTest8,  unitTest9,  unitTest10, unitTest11, unitTest12,
    unitTest13, unitTest14, unitTest15, unitTest16, unitTest17, unitTest18,
    unitTest19, unitTest20, unitTest21, NULL};

// ====================================================
// ================== Program Entry ===================
// ====================================================
int main() {
  unsigned int testsPassed = 0;
  // List of Unit Tests to test your data structure
  int counter = 0;
  while (unitTests[counter] != NULL) {
    std::cout << "========unitTest " << counter+1 << "========\n";
    if (true == unitTests[counter]()) {
      std::cout << "passed test\n";
      testsPassed++;
    } else {
      std::cout << "failed test, missing functionality, or incorrect test\n";
    }
    counter++;
  }

  std::cout << "\n\n" << testsPassed << " of " << counter << " tests passed\n";

  return 0;
}
