#include "Logger.h"
#include <iostream>

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"

void logDebugInfo(std::string logInfo)
{
    std::cout << YELLOW << "[DEBUG]:" << RESET << logInfo << RESET << std::endl;
}

void logErrorInfo(std::string logInfo)
{
    std::cout << RED << "[ERROR]:" << RESET << logInfo << RESET << std::endl;
}