#include "rastrigin.h"
#include <cmath>

const double PI = 3.14159265358979323846;  // Определяем константу PI

double rastrigin(const std::vector<double>& x) {
    const double A = 10.0;
    return A * x.size() + (x[0] * x[0] - A * std::cos(2 * PI * x[0])) + (x[1] * x[1] - A * std::cos(2 * PI * x[1]));
}
