cmake_minimum_required(VERSION 3.5.0)

set(CMAKE_PREFIX_PATH C:/Users/amess/vcpkg)
set(VCPKG_TARGET_TRIPLET x64-windows)




project(OrpheusCPP VERSION 0.1.0 LANGUAGES C CXX)

include_directories(C:/Users/amess/vcpkg/installed/x64-windows/include)
link_directories(C:/Users/amess/vcpkg/installed/x64-windows/lib)
include(C:/Users/amess/vcpkg/scripts/buildsystems/vcpkg.cmake)

include_directories(include)

find_package(fmt CONFIG REQUIRED)
find_package(dpp CONFIG REQUIRED) 

file(GLOB SOURCES "src/*.cpp")

add_executable(OrpheusCPP ${SOURCES}) 

#include(CTest)
#enable_testing()

#set(CPACK_PROJECT_NAME ${PROJECT_NAME})
#set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
#include(CPack)


target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt)
target_link_libraries(${PROJECT_NAME} PRIVATE dpp::dpp)
