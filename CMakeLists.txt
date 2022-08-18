cmake_minimum_required(VERSION 3.17)
project(apple_arbitrage)

set(CMAKE_CXX_STANDARD 20)

add_executable(apple_arbitrage main.cpp arbitrage.cpp arbitrage.h products/apple.h market_data/market_data_engine.h)