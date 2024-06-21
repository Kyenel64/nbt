cmake_minimum_required(VERSION 3.27)

project ("MultiThreadPractice")

set (SrcFiles
"JoiningThread.h" "JoiningThread.cpp"
"ThreadGuard.h" "ThreadGuard.cpp"
"main.cpp")

add_executable(${PROJECT_NAME} ${SrcFiles})

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)