cmake_minimum_required(VERSION 3.29)
project(SuanFaTest)

set(CMAKE_CXX_STANDARD 11)

add_executable(SuanFaTest main.cpp
        HaiDaoChuan.cpp
        alibaba.cpp
        anpaihuiyi.cpp
        "zuiduanlujing(不推荐看，太复杂).cpp"
        zuiduanjuli_base.cpp
        Huffman.cpp
        huffman_chinese.cpp
        prim.cpp
)
