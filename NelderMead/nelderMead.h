#pragma once
#include "FuncInterface.h"
#include "SIMPLEX.h"
#include "PointOperations.h"
#include <array>
#include <algorithm>
#include <cmath>
#include <iostream>

namespace OptLib {
    template<size_t dim>
    class NelderMead {
    public:
        NelderMead(const FuncInterface::IFunc<dim>* func, int maxIter)
            : func_(func), maxIter_(maxIter) {}

        Point<dim> optimize(SimplexValSort<dim>& simplex) {
            for (int iter = 0; iter < maxIter_; ++iter) {
                simplex.Sort();
                const PointVal<dim>& best = simplex.ItsSetOfPoints[0];
                const PointVal<dim>& worst = simplex.ItsSetOfPoints[dim];
                const PointVal<dim>& secondWorst = simplex.ItsSetOfPoints[dim - 1];

                Point<dim> centroid = computeCentroid(simplex, dim);

                Point<dim> reflected = centroid + (centroid - worst.P);
                double fReflected = (*func_)(reflected);

                if (fReflected < best.Val) {
                    Point<dim> expanded = centroid + 2 * (centroid - worst.P);
                    double fExpanded = (*func_)(expanded);
                    if (fExpanded < fReflected) {
                        simplex.ItsSetOfPoints[dim] = FuncInterface::CreateFromPoint(std::move(expanded), func_);
                    }
                    else {
                        simplex.ItsSetOfPoints[dim] = FuncInterface::CreateFromPoint(std::move(reflected), func_);
                    }
                }
                else if (fReflected < secondWorst.Val) {
                    simplex.ItsSetOfPoints[dim] = FuncInterface::CreateFromPoint(std::move(reflected), func_);
                }
                else {
                    Point<dim> contracted = centroid + 0.5 * (worst.P - centroid);
                    double fContracted = (*func_)(contracted);
                    if (fContracted < worst.Val) {
                        simplex.ItsSetOfPoints[dim] = FuncInterface::CreateFromPoint(std::move(contracted), func_);
                    }
                    else {
                        for (size_t i = 1; i <= dim; ++i) {
                            simplex.ItsSetOfPoints[i].P = best.P + 0.5 * (simplex.ItsSetOfPoints[i].P - best.P);
                            simplex.ItsSetOfPoints[i].Val = (*func_)(simplex.ItsSetOfPoints[i].P);
                        }
                    }
                }

                std::cout << "Итерация " << iter + 1 << ": ";
                for (const auto& pval : simplex.ItsSetOfPoints) {
                    std::cout << pval.Val << " ";
                }
                std::cout << std::endl;

                for (const auto& vertex : simplex.ItsSetOfPoints) {
                    for (double coord : vertex.P) {
                        std::cout << coord << " ";
                    }
                    std::cout << std::endl;
                }
                std::cout << std::endl;

                double maxChange = 0;
                for (const auto& pval : simplex.ItsSetOfPoints) {
                    maxChange = std::max(maxChange, maxAbsDiff(pval.P, best.P));
                }
                if (maxChange < 1e-6) {
                    break;
                }
            }

            return simplex.ItsSetOfPoints[0].P;
        }

    private:
        const FuncInterface::IFunc<dim>* func_;
        int maxIter_;

        Point<dim> computeCentroid(const SimplexValSort<dim>& simplex, size_t exclude) const {
            Point<dim> centroid{};
            for (size_t i = 0; i <= dim; ++i) {
                if (i == exclude) continue;
                centroid = centroid + simplex.ItsSetOfPoints[i].P;
            }
            centroid = centroid / dim;
            return centroid;
        }
    };
}
