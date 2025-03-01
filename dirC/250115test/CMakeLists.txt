cmake_minimum_required(VERSION 3.10)

# Project name
project(MainProject)

# Set the C standard (optional)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Specify the source files
set(SOURCES
    main.c
)

# Add the executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Optional: If you want to use target_sources for clarity, you can still do this:
# target_sources(${PROJECT_NAME} PRIVATE ${SOURCES})
