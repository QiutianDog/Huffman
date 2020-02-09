//
// Created by 10196 on 2020/2/5.
//

#ifndef HUFFMAN_HUFFMANNODE_H
#define HUFFMAN_HUFFMANNODE_H

class HuffmanNode {
public:
    char data;
    int index;
    char* code;
    HuffmanNode *lchild, *rchild;

    HuffmanNode();
};


#endif //HUFFMAN_HUFFMANNODE_H
