#include <iostream>
#include <string>

#ifdef _WIN32
#define DOORCONTROL_API __declspec(dllexport)
#else
#define DOORCONTROL_API
#endif

extern "C" {
    DOORCONTROL_API bool OpenDoor();
    DOORCONTROL_API bool CloseDoor();
    DOORCONTROL_API void TriggerAlarm(const char* reason);
}

static bool doorIsOpen = false;

bool OpenDoor() {
    if (doorIsOpen) {
        TriggerAlarm("Дверь уже открыта!");
        return false;
    }
    doorIsOpen = true;
    std::cout << "Дверь успешно открыта." << std::endl;
    return true;
}

bool CloseDoor() {
    if (!doorIsOpen) {
        TriggerAlarm("Дверь уже закрыта!");
        return false;
    }
    doorIsOpen = false;
    std::cout << "Дверь успешно закрыта." << std::endl;
    return true;
}

void TriggerAlarm(const char* reason) {
    std::cerr << "ТРЕВОГА! Причина: " << reason << std::endl;
}