#ifndef ASSERTS_H
#define ASSERTS_H

#include <iostream>
#include <stdexcept>
#include <sstream>

/// Assert that the left and right value are equal.
template <class T>
void assert_eq(const T& lhs, const T& rhs)
{
  if (lhs != rhs)
  {
    std::stringstream s;
    s
      << "Assertion failed: 'lhs == rhs'\n"
      << "lhs: " << lhs << '\n'
      << "rhs: " << rhs
    ;
    std::cerr << s.str();
    std::abort();
    //throw std::logic_error(s.str());
  }
}

/// Tests the asserts
void test_asserts();


#endif // ASSERTS_H
