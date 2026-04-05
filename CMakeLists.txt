# Минимальная версия CMake
cmake_minimum_required(VERSION 3.10)

# Название проекта
project(HeapProject LANGUAGES C)

# Указываем использование Clang
set(CMAKE_C_COMPILER clang)

# Явно указываем стандарт C (опционально, например C11 или C99)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Добавляем исполняемый файл из исходников
add_executable(test_program heap.c test_program.c)

# Если нужно включить дополнительные флаги компиляции (опционально)
target_compile_options(test_program PRIVATE 
    -Wall      # Все предупреждения
    -Wextra    # Дополнительные предупреждения
    -g         # Отладочная информация
)