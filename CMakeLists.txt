cmake_minimum_required(VERSION 3.26)
project(Matrix)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Matrix
        Line.h
        Manager.h
        Matrix.cpp
        Symbol.h
        Symbol.cpp
        Line.cpp
        Manager.cpp
        Figure.h
        Figure.cpp
        Explosion.h
        Explosion.cpp
        MyVector.h
        PermissiveMatrix.h
        List.h
        LinkedList.h
)
