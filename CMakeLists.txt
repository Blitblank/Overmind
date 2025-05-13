
# cmake version
cmake_minimum_required(VERSION 4.0)

# project
project (overmind)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)

if (MSVC)
    add_compile_options(/std:c++20)
endif()

# sources
file(GLOB SOURCES
    "src/*.cpp"
)
set(ALL_SOURCES ${SOURCES} ${EXTRA_SRC})

# executable
add_executable(${PROJECT_NAME} ${ALL_SOURCES})

# include directories
target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/Libraries/include
)
