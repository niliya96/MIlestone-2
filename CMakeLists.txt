cmake_minimum_required(VERSION 3.15)
project(Milestone2)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -pthread)
add_executable(Milestone2 main.cpp server/MyParallelServer.cpp server/Server.h server/MySerialServer.cpp client/ClientHandler.h client/MyTestClientHandler.cpp solver/Solver.h solver/StringReverser.cpp cacheManager/CacheManager.h cacheManager/FileCacheManager.cpp searcher/Searcher.h client/MyClientHandler.cpp searchable/Matrix.cpp searchable/State.h searcher/BestFS.cpp searcher/AStar.cpp)