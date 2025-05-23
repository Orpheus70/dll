#include <windows.h>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <random>
#include <sstream>

// Тип функции обратного вызова
typedef void (*ResultCallback)(int status, float* pulse, float* spo2);

extern "C" __declspec(dllexport) void start_(ResultCallback callback) {
    const char* filePath = "Pulse,SpO2.txt";

    std::ifstream file(filePath);
    if (!file.is_open()) {
        int status = 1;
        callback(status, nullptr, nullptr);
        return;
    }

    std::string line;
    float pulse = 0.0f, spo2 = 0.0f;

    while (std::getline(file, line)) {
        if (line.find("Пульс:") != std::string::npos) {
            std::stringstream ss(line.substr(line.find(":") + 1));
            ss >> pulse;
        } else if (line.find("SpO2:") != std::string::npos) {
            std::stringstream ss(line.substr(line.find(":") + 1));
            ss >> spo2;
        }
    }

    file.close();

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> delayDist(5, 10);
    std::this_thread::sleep_for(std::chrono::seconds(delayDist(gen)));

    std::uniform_int_distribution<> errorDist(1, 5);
    bool showError = errorDist(gen) == 1;

    if (showError || pulse == 0.0f || spo2 == 0.0f) {
        int status = 1;
        callback(status, nullptr, nullptr);
    } else {
        int status = 0;
        callback(status, &pulse, &spo2);
    }
}