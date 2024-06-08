#include <iostream>
#include <vector>
#include "rastrigin.h"
#include "nelderMead.h"

int main() {
    setlocale(LC_ALL, "Russian");

    std::vector<std::vector<double>> simplex = { {-1.2, 1.0}, {0.0, 0.0}, {0.5, 0.5} };
    int maxIter = 200;

    nelderMead(simplex, rastrigin, maxIter);

    std::wcout << L"Оптимальное решение:" << std::endl;
    for (const auto& vertex : simplex) {
        for (double coord : vertex) {
            std::wcout << coord << L" ";
        }
        std::wcout << std::endl;
    }

    return 0;
}
