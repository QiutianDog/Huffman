//
// Created by 10196 on 2020/2/5.
//

#ifndef HUFFMAN_HUFFMANTREE_H
#define HUFFMAN_HUFFMANTREE_H

#include "HuffmanNode.h"

class HuffmanTree {
    HuffmanNode *root;
public:
    HuffmanTree();
    ~HuffmanTree();
    void Initialization();
    void Encoding();
    void Decoding();
    void Print();
    void TreePrint();
    void Compare();
private:
    void Release(HuffmanNode* root);
    char* getCode(char x);
    void InOrder(HuffmanNode* root);
    void show(HuffmanNode* root, HuffmanNode* child, char prefix[], int count);
    int Locate(char x, HuffmanNode* data[], int n);
    void BubbleSort(HuffmanNode* data[], int n);
};


#endif //HUFFMAN_HUFFMANTREE_H
