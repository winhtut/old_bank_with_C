cmake_minimum_required(VERSION 3.24)
project(xBankV1 C)

set(CMAKE_C_STANDARD 11)

add_executable(xBankV1 tcpServer/tcp_serve_toupper.c)
