cmake_minimum_required(VERSION 3.16)
project(LogMessages)

set(CMAKE_CXX_STANDARD 17)

# Configure source files.
set(PROJECT_SOURCE_FILES
        "${PROJECT_SOURCE_DIR}/src/messaging/log_message.cpp"
        "${PROJECT_SOURCE_DIR}/src/timing/timestamp.cpp"
        "${PROJECT_SOURCE_DIR}/src/main.cpp"
        )

add_executable(LogMessages ${PROJECT_SOURCE_FILES})

# Public include files.
set(PROJECT_INCLUDE_FILES "${PROJECT_SOURCE_DIR}/include")
target_include_directories(LogMessages PUBLIC ${PROJECT_INCLUDE_FILES})


