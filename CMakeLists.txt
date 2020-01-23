cmake_minimum_required(VERSION 3.15)
project(MIlestone_2)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -pthread)

include_directories(cacheManager)
include_directories(client)
include_directories(searchable)
include_directories(searcher)
include_directories(server)
include_directories(solver)

add_executable(MIlestone_2
        cacheManager/CacheManager.h
        cacheManager/FileCacheManager.cpp
        client/ClientHandler.h
        client/MyClientHandler.cpp
        client/MyTestClientHandler.cpp
        searchable/Matrix.cpp
        searchable/Searchable.h
        searchable/State.h
        searcher/AStar.cpp
        searcher/BestFS.cpp
        searcher/Searcher.h
        server/MyParallelServer.cpp
        server/MySerialServer.cpp
        server/Server.h
        solver/Solver.h
        solver/StringReverser.cpp
        main.cpp)
