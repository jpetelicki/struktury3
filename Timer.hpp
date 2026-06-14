#pragma once
#include <chrono>

class Timer {
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
    std::chrono::time_point<std::chrono::high_resolution_clock> endTime;
    bool isRunning;

public:
    Timer() {
        isRunning = false;
    }

    void start() {
        startTime = std::chrono::high_resolution_clock::now();
        isRunning = true;
    }

    void stop() {
        endTime = std::chrono::high_resolution_clock::now();
        isRunning = false;
    }

    long long getNanoseconds() {
        std::chrono::time_point<std::chrono::high_resolution_clock> endPoint;

        if (isRunning) {
            endPoint = std::chrono::high_resolution_clock::now();
        }
        else {
            endPoint = endTime;
        }

        return std::chrono::duration_cast<std::chrono::nanoseconds>(endPoint - startTime).count();
    }
};