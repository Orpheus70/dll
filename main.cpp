#include <iostream>

#ifdef _WIN32
#define IMPORT __declspec(dllimport)
#else
#define IMPORT
#endif

extern "C" {
    IMPORT void OpenDoor();
    IMPORT void CloseDoor();
}

int main() {
    OpenDoor();
    CloseDoor();
       
    return 0;
}