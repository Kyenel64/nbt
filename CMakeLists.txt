cmake_minimum_required(VERSION 3.27)

project ("MultiThreadPractice")

set (SrcFiles
"threads/joining_thread.h"
        "threads/scoped_thread.h"
        "main.cpp"
        threads/threadsafe_stack.h
        threads/threadsafe_queue.h)

add_executable(${PROJECT_NAME} ${SrcFiles})

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)