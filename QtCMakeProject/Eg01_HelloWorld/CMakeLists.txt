cmake_minimum_required(VERSION 3.2)
project(Eg01_HelloWorld)
set(CMAKE_CXX_STANDARD 17)

# cmake modules
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)


# Qt setting
# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)
# Create code from a list of Qt designer ui files
set(CMAKE_AUTOUIC ON)

# project build setting
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Qt libraries
set(Qt5Widgets_DIR $ENV{HOME}/Qt5.11.1/5.11.1/gcc_64/lib/cmake/Qt5Widgets)
find_package(Qt5 COMPONENTS Core Widgets REQUIRED)
message("Qt5Widgets Dir: " ${Qt5Widgets_DIR})
message("Qt5 Includes: " ${Qt5Widgets_INCLUDE_DIRS})
message("Qt5 Library: " ${Qt5Widgets_LIBRARIES})
set(THIRD_LIBS ${THIRD_LIBS}
        gflags glog Qt5::Widgets)


# include directories
include_directories(./include)


# headers and sources files
file(GLOB_RECURSE FILE_INCLUDES "./include/*.*")
file(GLOB_RECURSE FILE_SRCS "./src/*.*")

# target
add_executable(QtProject ${FILE_SRCS})
target_link_libraries(${PROJECT_NAME} ${THIRD_LIBS})
