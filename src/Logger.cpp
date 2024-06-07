#include "Logger.h"
#include <iostream>
#include <stdlib.h>

void logDebugInfo(std::string logInfo)
{
    std::cout << "\033[31m" << logInfo << std::endl;
}