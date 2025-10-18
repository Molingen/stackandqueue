cmake_minimum_required(VERSION 3.16)
project(SQSMM LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (MSVC)
  add_compile_options(/W4 /permissive-)
else()
  add_compile_options(-Wall -Wextra -Wpedantic -Werror=return-type)
endif()

# чисто инклюды, создает библиотеку из хедеров / интерфейс для доступа
add_library(ds INTERFACE)
target_include_directories(ds INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# демка
add_executable(sample_app samples/main.cpp)
target_link_libraries(sample_app PRIVATE ds)

# GoogleTest через FetchContent (все скачает и соберет во время сборки)
include(FetchContent)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
)
FetchContent_MakeAvailable(googletest)

# поддержка ctest
enable_testing()

# ну и три тестовых бинарника
add_executable(test_stack    test/test_stack.cpp)
add_executable(test_queue    test/test_queue.cpp)
add_executable(test_minmax   test/test_minmax_stack.cpp)

# залинковывем каждый тест с нашей библиотекой хедеров ds с gtest_main
foreach(tgt IN ITEMS test_stack test_queue test_minmax)
  target_link_libraries(${tgt} PRIVATE ds GTest::gtest_main)
  add_test(NAME ${tgt} COMMAND ${tgt})
endforeach()
