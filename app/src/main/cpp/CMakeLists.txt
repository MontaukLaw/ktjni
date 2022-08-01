cmake_minimum_required(VERSION 3.18.1)

project("ktjnidemo")
add_library(
        udprev
        SHARED
        udp-rev.cpp)

find_library(
        log-lib
        log)

target_link_libraries(
        udprev
        ${log-lib})