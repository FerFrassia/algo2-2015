cmake_minimum_required(VERSION 3.3)
project(tp3_algo2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    aed2/Arreglo.h
    aed2/Conj.h
    aed2/ConjAcotado.cpp
    aed2/ConjAcotado.h
    aed2/Dicc.h
    aed2/Lista.h
    aed2/TiposBasicos.h
    aed2/Vector.h
    aed2.h
    DiccString.cpp
    DiccString.h
    Driver.cpp
    Driver.h
    hash.h
    mini_test.h
    test.cpp
    Tipos.h)

add_executable(tp3_algo2 ${SOURCE_FILES})