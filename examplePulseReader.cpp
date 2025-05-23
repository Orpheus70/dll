#include <iostream>

#ifdef _WIN32
#define IMPORT __declspec(dllimport)
#else
#define IMPORT
#endif

extern "C" {
    typedef void (*ResultCallback)(int status, float* pulse, float* spo2);
    IMPORT void start_(ResultCallback callback);
}

// Реализация callback-функции
void resultReceiver(int status, float* pulse, float* spo2) {
    if (status != 0 || !pulse || !spo2) {
        std::cout << "Данные не считаны. Повторите измерение ещё раз." << std::endl;
    } else {
        std::cout << "Пульс: " << *pulse << " уд./мин." << std::endl;
        std::cout << "SpO2: " << *spo2 << " %" << std::endl;
    }
}

int examplePulseReader() {
    start_(resultReceiver);
    return 0;
}