#pragma once
#include <array>

namespace OptLib {
    template<size_t dim>
    std::array<double, dim> operator+(const std::array<double, dim>& a, const std::array<double, dim>& b) {
        std::array<double, dim> result;
        for (size_t i = 0; i < dim; ++i) {
            result[i] = a[i] + b[i];
        }
        return result;
    }

    template<size_t dim>
    std::array<double, dim> operator-(const std::array<double, dim>& a, const std::array<double, dim>& b) {
        std::array<double, dim> result;
        for (size_t i = 0; i < dim; ++i) {
            result[i] = a[i] - b[i];
        }
        return result;
    }

    template<size_t dim>
    std::array<double, dim> operator*(const std::array<double, dim>& a, double scalar) {
        std::array<double, dim> result;
        for (size_t i = 0; i < dim; ++i) {
            result[i] = a[i] * scalar;
        }
        return result;
    }

    template<size_t dim>
    std::array<double, dim> operator*(double scalar, const std::array<double, dim>& a) {
        return a * scalar;
    }

    template<size_t dim>
    std::array<double, dim> operator/(const std::array<double, dim>& a, double scalar) {
        std::array<double, dim> result;
        for (size_t i = 0; i < dim; ++i) {
            result[i] = a[i] / scalar;
        }
        return result;
    }

    template<size_t dim>
    double maxAbsDiff(const std::array<double, dim>& a, const std::array<double, dim>& b) {
        double maxDiff = 0.0;
        for (size_t i = 0; i < dim; ++i) {
            double diff = std::abs(a[i] - b[i]);
            if (diff > maxDiff) {
                maxDiff = diff;
            }
        }
        return maxDiff;
    }
}
