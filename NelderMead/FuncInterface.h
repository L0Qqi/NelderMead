#pragma once
#include <array>
#include <cmath>
#include "SIMPLEX.h"

namespace OptLib {
    namespace FuncInterface {
        template<size_t dim>
        struct Grad;

        template<size_t dim>
        class IFunc;

        template<size_t dim>
        PointVal<dim> CreateFromPoint(Point<dim>&& p, const IFunc<dim>* f) {
            PointVal<dim> out{};
            out.Val = (*f)(p);
            out.P = std::move(p);
            return out;
        }

        template<size_t dim>
        class IFunc {
        public:
            virtual double operator() (const Point<dim>& p) const = 0;
        };

        template<size_t dim>
        class IGrad {
        public:
            virtual Grad<dim> grad(const Point<dim>& p) const = 0;
        };

        template<size_t dim>
        class IHess {
        public:
            virtual std::array<Grad<dim>, dim> hess(const Point<dim>& x) const = 0;
        };
    }
}