cmake_minimum_required(VERSION 3.0.0)
project(GLS_ENGINE VERSION 0.1.0)

include(CTest)
enable_testing()

file(GLOB SRC src/*.c src/*.cpp)

add_executable(GLS_ENGINE ${SRC})

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

include_directories(include)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

include(CPack)

include_directories( ${OPENGL_INCLUDE_DIRS} include)
target_link_libraries(GLS_ENGINE ${OPENGL_LIBRARIES} glfw)