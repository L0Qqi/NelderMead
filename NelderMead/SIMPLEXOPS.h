#pragma once
#include "SIMPLEX.h"

namespace OptLib {
    namespace SimplexOps {
        template<size_t dim>
        Point<dim> computeCentroid(const SimplexValSort<dim>& simplex, size_t exclude) {
            Point<dim> centroid{};
            for (size_t i = 0; i <= dim; ++i) {
                if (i == exclude) continue;
                centroid = centroid + simplex.ItsSetOfPoints[i].P;
            }
            centroid = centroid / dim;
            return centroid;
        }

        template<size_t dim>
        double maxDifference(const SimplexValSort<dim>& simplex, const Point<dim>& reference) {
            double maxDiff = 0;
            for (const auto& pval : simplex.ItsSetOfPoints) {
                for (size_t i = 0; i < dim; ++i) {
                    maxDiff = std::max(maxDiff, std::abs(pval.P[i] - reference[i]));
                }
            }
            return maxDiff;
        }
    }
}
