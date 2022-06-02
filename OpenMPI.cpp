#include <iostream>
#include <chrono>

using namespace std;

void sequential() {
    std::cout << "sequential" << std::endl;
    const auto startTime = std::chrono::system_clock::now();
    const int intervalNum = 200000000;
    const double lBound = 0, rBound = 1;
    const double h = (rBound - lBound) / intervalNum;
    double area = 0;
    for (int i = 0; i < intervalNum; ++i) {
        double x = h * i;
        area += sin(x + x * x * x);
    }
    const double res = area * h;
    const auto endTime = std::chrono::system_clock::now();
    std::cout << "Res " << res << std::endl;
    const auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
    std::cout << "Spent time: " << duration.count() / 1000. << "ms" << std::endl;
}

void openmp() {
    std::cout << "openmp" << std::endl;
    const auto startTime = std::chrono::system_clock::now();
    const int intervalNum = 200000000;
    const double lBound = 0, rBound = 1;
    const double h = (rBound - lBound) / intervalNum;
    double area = 0;
#pragma omp parallel for reduction( + : area )
    for (int i = 0; i < intervalNum; ++i) {
        double x = h * i;
        area += sin(x + x * x * x);
    }
    const double res = area * h;
    const auto endTime = std::chrono::system_clock::now();
    std::cout << "Res " << res << std::endl;
    const auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
    std::cout << "Spent time: " << duration.count() / 1000. << "ms" << std::endl;
}


int main(int argc, char* argv[]) {

    sequential();
    openmp();

    return 0;
}