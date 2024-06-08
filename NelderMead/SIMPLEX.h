#pragma once
#include <array>
#include <algorithm>
#include <numeric>

namespace OptLib {
    template<size_t dim>
    using Point = std::array<double, dim>;

    // Структура PointVal для хранения точки и значения функции в этой точке
    template<size_t dim>
    struct PointVal {
        Point<dim> P;
        double Val;

        bool operator<(const PointVal& other) const {
            return Val < other.Val;
        }
    };

    // Структура SimplexValSort для работы с отсортированным симплексом
    template<size_t dim>
    struct SimplexValSort {
        std::array<PointVal<dim>, dim + 1> ItsSetOfPoints;

        PointVal<dim> Mean() const {
            Point<dim> meanP{};
            double meanVal = 0.0;
            for (const auto& pval : ItsSetOfPoints) {
                meanP = meanP + pval.P;
                meanVal += pval.Val;
            }
            meanP = meanP / (dim + 1);
            meanVal /= (dim + 1);
            return { meanP, meanVal };
        }

        void Sort() {
            std::sort(ItsSetOfPoints.begin(), ItsSetOfPoints.end());
        }
    };
}