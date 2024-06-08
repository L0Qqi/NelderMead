#include "rosenbrock.h"
#include <cmath>

double rosenbrock(const std::vector<double>& x) {
    return 100 * std::pow(x[1] - std::pow(x[0], 2), 2) + std::pow(1 - x[0], 2);
}
