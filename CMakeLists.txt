cmake_minimum_required(VERSION 3.23)
project(DAnota20-grafo_feito)

set(CMAKE_CXX_STANDARD 14)

add_executable(DAv2 main.cpp VertexEdge.cpp VertexEdge.h Graph.cpp Graph.h network.cpp network.h stations.cpp stations.h MutablePrioityQueue.h readFiles.cpp readFiles.h)
