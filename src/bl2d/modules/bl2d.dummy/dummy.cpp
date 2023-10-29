#include "Dummy.h"

#ifdef BL2D_CONSOLE_APP
#include <iostream>
#endif
#ifdef BL2D_WINDOWED_APP
#include <Windows.h>
#endif

void bl2d::dummy::Dummy::SayHello()
{
#ifdef BL2D_CONSOLE_APP
    std::cout << "Hello World!" << std::endl;
#endif
#ifdef BL2D_WINDOWED_APP
    MessageBoxA(nullptr, "Hello World!", "Hello World!", MB_OK);
#endif
}
