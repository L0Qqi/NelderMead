//#pragma once
//#include "SIMPLEX.h"
//
//namespace OptLib {
//    template<size_t dim>
//    void serialize(const SimplexValSort<dim>& simplex, std::ostream& out) {
//        for (const auto& pointVal : simplex.ItsSetOfPoints) {
//            for (const auto& coord : pointVal.P) {
//                out << coord << " ";
//            }
//            out << pointVal.Val << std::endl;
//        }
//    }
//
//    template<size_t dim>
//    SimplexValSort<dim> deserialize(std::istream& in) {
//        SimplexValSort<dim> simplex;
//        for (auto& pointVal : simplex.ItsSetOfPoints) {
//            for (auto& coord : pointVal.P) {
//                in >> coord;
//            }
//            in >> pointVal.Val;
//        }
//        return simplex;
//    }
//}
