#include <cfloat>
#include <cmath>
#include <string>
#include "utils.h"

namespace utils {
  // Fixed modulo method which can calculate modulo of negative numbers properly
  // e.g. (-803).mod(800) returns 797
  double mod(double context, double num) {
    return std::fmod((std::fmod(context, num) + num), num);
  }

  // Trims number and leaves the number of decimals specified.
  // The "mode" argument specifies which math function should be invoked
  // right after the number has been trimmed.
  // e.g. 12.12345.trim(3, "ceil") returns 12.124
  double trim(double context, int decimals, const std::string mode) {
    double accumulator = context * std::pow(10, decimals);

    if (mode.compare("ceil") == 0)
      accumulator = std::ceil(accumulator);
    else if (mode.compare("floor") == 0)
      accumulator = std::floor(accumulator);
    else
      accumulator = std::round(accumulator);

    return accumulator / std::pow(10, decimals);
  }

  // Tells if number is in specified range based on given precision.
  // See the "compare" method for more information about precision
  bool isBetween(double context, double num1, double num2, const std::string precision) {
    return compare(context, std::min(num1, num2), ">=", precision) &&
           compare(context, std::max(num1, num2), "<=", precision);
  }

  bool compare(double context, double num, const std::string precision) {
    return compare(context, num, "==", precision);
  }

  // Initiates comparison operator between context number and a given number, only here
  // a precision can be specified
  bool compare(double context, double num, const std::string method, const std::string precision) {
    // Fixed precision, "almost equal" with a deviation of ε
    if (precision.compare("f") == 0) {
      if (method.compare("<") == 0 ||
          method.compare("<=") == 0)
        return context <= num + DBL_EPSILON;
      if (method.compare(">") == 0 ||
          method.compare(">=") == 0)
        return context >= num - DBL_EPSILON;
      return std::abs(context - num) <= DBL_EPSILON;
    }
    // Pixel precision, round comparison
    else if (precision.compare("px") == 0) {
      if (method.compare("<") == 0 ||
          method.compare("<=") == 0)
        return std::round(context) <= std::round(num);
      if (method.compare(">") == 0 ||
          method.compare(">=") == 0)
        return std::round(context) >= std::round(num);
      return std::round(context) == std::round(num);
    }
    // Exact precision
    else {
      if (method.compare("<") == 0) return context < num;
      if (method.compare("<=") == 0) return context <= num;
      if (method.compare(">") == 0) return context > num;
      if (method.compare(">=") == 0) return context >= num;
      return context == num;
    }
  }
}