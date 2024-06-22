cmake_minimum_required(VERSION 3.27)

project ("NBT")

set (SrcFiles
"threads/JoiningThread.h"
        "threads/ScopedThread.h"
        "main.cpp"
        "threads/ThreadSafeStack.h"
        "threads/ThreadSafeQueue.h"
        "threads/ThreadPool.cpp"
        "threads/ThreadPool.h")

add_executable(${PROJECT_NAME} ${SrcFiles})

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)