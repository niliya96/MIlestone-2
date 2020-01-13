cmake_minimum_required(VERSION 3.15)
project(Milestone2)

set(CMAKE_CXX_STANDARD 14)

add_executable(Milestone2 main.cpp server/Server.h server/MySerialServer.cpp client/ClientHandler.h client/MyTestClientHandler.cpp solver/Solver.cpp solver/Solver.h cacheManager/CacheManager.h)