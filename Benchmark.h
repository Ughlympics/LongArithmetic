#pragma once
#include <iostream>
#include <chrono>

class Benchmark
{
public:
    Benchmark(const std::string& operationName = "Operation")
        : start(std::chrono::high_resolution_clock::now()), name(operationName) {}

    ~Benchmark() {
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        std::cout << name << " took " << elapsed.count() << " seconds.\n";
    }

    void stop() {
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        std::cout << name << " took " << elapsed.count() << " seconds.\n";
    }
    double getElapsedTime() const {
        return elapsedTime;
    }

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start;
    std::string name;
    double elapsedTime;  
    bool stopped = false;
};

