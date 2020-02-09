cmake_minimum_required(VERSION 3.15)
project(Huffman)

set(CMAKE_CXX_STANDARD 11)

add_executable(Huffman main.cpp HuffmanTree.cpp HuffmanTree.h HuffmanNode.cpp HuffmanNode.h)