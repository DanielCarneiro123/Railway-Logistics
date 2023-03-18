cmake_minimum_required(VERSION 3.23)
project(DAv1)

set(CMAKE_CXX_STANDARD 14)

add_executable(DAv1 main.cpp network.cpp network.h graph.cpp graph.h trip.cpp trip.h stations.cpp stations.h)
