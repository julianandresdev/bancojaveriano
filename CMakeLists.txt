cmake_minimum_required(VERSION 3.30)
project(BancoDeLaRepublica)

set(CMAKE_CXX_STANDARD 20)

add_executable(BancoDeLaRepublica main.cpp
        Banco.cpp
        Banco.h
        Clientes.cpp
        Clientes.h
        Cuentas.cpp
        Cuentas.h
        Corriente.cpp
        Corriente.h
        Ahorros.cpp
        Ahorros.h)
