//#include <iostream>
//#include <vector>
//#include "rastrigin.h"
//#include "nelderMead.h"
//
//int main() {
//    setlocale(LC_ALL, "Russian");
//
//    std::vector<std::vector<double>> simplex = { {-1.2, 1.0}, {0.0, 0.0}, {0.5, 0.5} };
//    int maxIter = 200;
//
//    nelderMead(simplex, rastrigin, maxIter);
//
//    std::wcout << L"Оптимальное решение:" << std::endl;
//    for (const auto& vertex : simplex) {
//        for (double coord : vertex) {
//            std::wcout << coord << L" ";
//        }
//        std::wcout << std::endl;
//    }
//
//    return 0;
//}
#include <iostream>
#include <array>
#include "FuncInterface.h"
#include "nelderMead.h"
#include "SIMPLEX.h"

using namespace OptLib;

int main() {
    setlocale(LC_ALL, "Russian");

    const size_t dim = 2;
    using PointType = Point<dim>;

    // Инициализация начального симплекса
    std::array<PointType, dim + 1> simplex = { {
        PointType{1.0, 2.0},
        PointType{1.0, 3.0},
        PointType{2.0, 2.0}
    } };

    // Пример функции для минимизации
    class ExampleFunc : public FuncInterface::IFunc<dim> {
    public:
        double operator()(const PointType& x) const override {
            // Пример: квадратичная функция (сумма квадратов координат)
            double sum = 0.0;
            for (const auto& xi : x) {
                sum += xi * xi;
            }
            return sum;
        }
    };

    ExampleFunc func;

    // Преобразование начального симплекса в структуру SimplexValSort
    SimplexValSort<dim> simplexVal;
    for (size_t i = 0; i <= dim; ++i) {
        simplexVal.ItsSetOfPoints[i] = FuncInterface::CreateFromPoint(std::move(simplex[i]), &func);
    }

    // Параметры алгоритма Нелдера-Мида
    int maxIter = 100;

    // Вызов функции Нелдера-Мида
    NelderMead<dim> nelderMead(&func, maxIter);
    nelderMead.optimize(simplexVal);

    // Вывод результата
    std::cout << "Результат оптимизации:" << std::endl;
    for (const auto& pointVal : simplexVal.ItsSetOfPoints) {
        for (const auto& coord : pointVal.P) {
            std::cout << coord << " ";
        }
        std::cout << "= " << pointVal.Val << std::endl;
    }

    return 0;
}
