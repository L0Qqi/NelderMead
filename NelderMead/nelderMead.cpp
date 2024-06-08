#include "nelderMead.h"
#include <algorithm>
#include <cmath>
#include <iostream>

std::vector<double> computeCentroid(const std::vector<std::vector<double>>& simplex, int worst) {
    std::vector<double> centroid(simplex[0].size(), 0.0);
    for (int i = 0; i < simplex.size(); ++i) {
        if (i == worst) continue;
        for (int j = 0; j < simplex[0].size(); ++j) {
            centroid[j] += simplex[i][j];
        }
    }
    for (int j = 0; j < centroid.size(); ++j) {
        centroid[j] /= (simplex.size() - 1);
    }
    return centroid;
}

void nelderMead(std::vector<std::vector<double>>& simplex, std::function<double(const std::vector<double>&)> func, int maxIter) {
    int n = simplex.size() - 1;
    std::vector<double> f(n + 1);

    for (int iter = 0; iter < maxIter; ++iter) {
        for (int i = 0; i <= n; ++i) {
            f[i] = func(simplex[i]);
        }

        int best = std::min_element(f.begin(), f.end()) - f.begin();
        int worst = std::max_element(f.begin(), f.end()) - f.begin();
        int secondWorst = best;
        for (int i = 0; i <= n; ++i) {
            if (i != best && f[i] > f[secondWorst]) {
                secondWorst = i;
            }
        }

        std::vector<double> centroid = computeCentroid(simplex, worst);

        std::vector<double> reflected(n);
        for (int i = 0; i < n; ++i) {
            reflected[i] = centroid[i] + (centroid[i] - simplex[worst][i]);
        }
        double fReflected = func(reflected);

        if (fReflected < f[best]) {
            std::vector<double> expanded(n);
            for (int i = 0; i < n; ++i) {
                expanded[i] = centroid[i] + 2 * (centroid[i] - simplex[worst][i]);
            }
            double fExpanded = func(expanded);
            if (fExpanded < fReflected) {
                simplex[worst] = expanded;
            }
            else {
                simplex[worst] = reflected;
            }
        }
        else if (fReflected < f[secondWorst]) {
            simplex[worst] = reflected;
        }
        else {
            std::vector<double> contracted(n);
            for (int i = 0; i < n; ++i) {
                contracted[i] = centroid[i] + 0.5 * (simplex[worst][i] - centroid[i]);
            }
            double fContracted = func(contracted);
            if (fContracted < f[worst]) {
                simplex[worst] = contracted;
            }
            else {
                for (int i = 0; i <= n; ++i) {
                    if (i != best) {
                        for (int j = 0; j < n; ++j) {
                            simplex[i][j] = simplex[best][j] + 0.5 * (simplex[i][j] - simplex[best][j]);
                        }
                    }
                }
            }
        }

        std::wcout << L"Итерация " << iter + 1 << L": ";
        for (int i = 0; i <= n; ++i) {
            std::wcout << f[i] << L" ";
        }
        std::wcout << std::endl;

        for (const auto& vertex : simplex) {
            for (double coord : vertex) {
                std::wcout << coord << L" ";
            }
            std::wcout << std::endl;
        }
        std::wcout << std::endl;

        double maxChange = 0;
        for (int i = 0; i < simplex.size(); ++i) {
            for (int j = 0; j < simplex[0].size(); ++j) {
                maxChange = std::max(maxChange, std::abs(simplex[i][j] - simplex[best][j]));
            }
        }
        if (maxChange < 1e-6) {
            break;
        }
    }
}
