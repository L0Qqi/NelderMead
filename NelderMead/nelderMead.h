#ifndef NELDER_MEAD_H
#define NELDER_MEAD_H

#include <vector>
#include <functional>

std::vector<double> computeCentroid(const std::vector<std::vector<double>>& simplex, int worst);
void nelderMead(std::vector<std::vector<double>>& simplex, std::function<double(const std::vector<double>&)> func, int maxIter);

#endif // NELDER_MEAD_H
