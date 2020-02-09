//
// Created by 10196 on 2020/2/5.
//

#include "HuffmanTree.h"
#include <cstring>
#include <iostream>

HuffmanTree::HuffmanTree() {
    root = NULL;
}

HuffmanTree::~HuffmanTree() {
    Release(root);
}

void HuffmanTree::Initialization() {
    // "r" 只读打开 file
    FILE *file = fopen("../File/TextFile1.txt", "r");

    int count = 0;
    char text[40][51] = {0};
    while (fgets(text[count], 51, file)){
        count++;
    }

    // 关闭 file
    fclose(file);

    //统计各个字符的权值
    HuffmanNode* nodeList[128];
    count = 0;
    for (int i = 0; text[i][0] ; ++i) {
        for (int j = 0; text[i][j]; ++j) {
            if (Locate(text[i][j], nodeList, count) == -1) {
                HuffmanNode* temp = new HuffmanNode();
                temp->data = text[i][j];
                temp->index = 1;
                nodeList[count] = temp;
                count++;
            } else {
                int sign = Locate(text[i][j], nodeList, count);
                nodeList[sign]->index++;
            }
        }
    }

    //构造哈夫曼树 新增结点为'@'
    HuffmanNode *temp;
    while (count > 1) {
        //排序
        BubbleSort(nodeList, count);
        //添加新结点
        temp = new HuffmanNode();
        temp->data = '@';
        temp->index = nodeList[0]->index + nodeList[1]->index;
        temp->lchild = nodeList[0];
        temp->rchild = nodeList[1];
        nodeList[0] = temp;
        nodeList[1] = nodeList[count - 1];
        count--;
    }
    root = temp;

    //将树储存在HuffmanTree.txt文件中
    InOrder(root);

    //将树进行编码
    char code[128] = {0};
    count = 0;

    HuffmanNode* stack[128];
    int top = -1;
    stack[++top] = root;

    while (top != -1) {
        while (temp) {
            //编码
            char *msg = new char[count + 1];
            for (int i = 0; i < count; ++i) {
                msg[i] = code[i];
            }
            msg[count] = '\0';
            temp->code = msg;
            //进入左子树
            if (temp->lchild) {
                temp = temp->lchild;
                stack[++top] = temp;
                code[count++] = '0';
            } else break;
        }
        //退回到上一个能进入不同右子树的结点
        HuffmanNode* p = stack[top];
        while (!temp->rchild || temp->rchild == p) {
            if (top == 0) {
                return;
            } //top == 0 时说明全部遍历完毕
            p = stack[top--];
            temp = stack[top];
            code[--count] = '\0';
        }
        if (temp->rchild) {
            temp = temp->rchild;
            stack[++top] = temp;
            code[count++] = '1';
        }
    }
}

void HuffmanTree::Encoding() {
    //从TextFile1.txt文件中导入文本
    FILE *file = fopen("../File/TextFile1.txt", "r");

    int count = 0;
    char text[40][51] = {0};

    while (fgets(text[count], 51, file)) {
        count++;
    }

    fclose(file);

    //往CodeFile.txt文件写入数据
    file = fopen("../File/CodeFile.txt", "w");

    //开始编码
    for (int i = 0; text[i][0]; ++i) {
        for (int j = 0; text[i][j]; ++j) {
            char *code = getCode(text[i][j]);
            fwrite(code, strlen(code), 1, file);
        }
    }

    fclose(file);
}

void HuffmanTree::Decoding() {
    //从CodeFile.txt读取编码
    FILE *file = fopen("../File/CodeFile.txt", "r");

    int count = 0;
    char code[40 * 4][51] = {0};

    while (fgets(code[count], 51, file)) {
        count++;
    }

    fclose(file);

    //打开TextFile2.txt来写入译码
    file = fopen("../File/TextFile2.txt", "w");

    //通过编码来填字符
    HuffmanNode *temp = root;
    for (int i = 0; code[i][0]; ++i) {
        for (int j = 0; code[i][j]; ++j) {
            if (code[i][j] == '0' && temp->lchild) {
                temp = temp->lchild;
            } else if (code[i][j] == '1' && temp->rchild) {
                temp = temp->rchild;
            } else {
                char msg[2] = {temp->data, '\0'};
                fwrite(msg, strlen(msg), 1, file);
                temp = root;//重置
                j--;
            }
        }
    }
    char msg[2] = {temp->data, '\0'};
    fwrite(msg, strlen(msg), 1, file);

    fclose(file);
}

void HuffmanTree::Print() {
    //从TextFile1.txt文件中导入文本
    FILE *file = fopen("../File/TextFile1.txt", "r");

    int count = 0;
    char text[40][51] = {0};

    while (fgets(text[count], 51, file)) {
        count++;
    }

    fclose(file);

    //打印原来字符串
    std::cout << "原字符串为：" << std::endl;
    count = 0;
    for (int i = 0; text[i][0]; ++i) {
        for (int j = 0; text[i][j]; ++j) {
            std::cout << text[i][j];
            count++;
            if (count % 50 == 0) {
                std::cout << '\n';
            }
        }
    }
    std::cout << std::endl;

    //从HuffmanTree.txt文件中导入文本
    file = fopen("../File/HuffmanTree.txt", "r");

    count = 0;
    char tree[40][51] = {0};

    while (fgets(tree[count], 51, file)) {
        count++;
    }

    fclose(file);

    //打印哈夫曼树
    std::cout << "层序遍历结果为：" << std::endl;
    count = 0;
    for (int i = 0; tree[i][0]; ++i) {
        for (int j = 0; tree[i][j]; ++j) {
            if (tree[i][j] == '\n') {
                std::cout << "\\n";
            } else {
                std::cout << tree[i][j];
            }
            count++;
            if (count % 50 == 0) {
                std::cout << '\n';
            }
        }
    }
    std::cout << std::endl;

    //从TextFile2.txt文件中导入文本
    file = fopen("../File/TextFile2.txt", "r");

    count = 0;
    char out[40][51] = {0};

    while (fgets(out[count], 51, file)) {
        count++;
    }

    fclose(file);

    //打印译码
    std::cout << "译码结果为：" << std::endl;
    count = 0;
    for (int i = 0; out[i][0]; ++i) {
        for (int j = 0; out[i][j]; ++j) {
            std::cout << out[i][j];
            count++;
            if (count % 50 == 0) {
                std::cout << '\n';
            }
        }
    }
    std::cout << std::endl;
}

void HuffmanTree::TreePrint() {
    //TODO 直观打出二叉树
    char prefix[128] = {0};
    int count = 0;
    show(root, root, prefix, count);
}

void HuffmanTree::Compare() {
    //读取TextFile1.txt的内容 统计字数
    FILE *file = fopen("../File/TextFile1.txt", "r");

    int count = 0;
    char text[40][51] = {0};
    while (fgets(text[count], 51, file)) {
        count++;
    }

    fclose(file);
    //统计字数
    int textNum = 0;
    for (int i = 0; text[i][0]; ++i) {
        for (int j = 0; text[i][j]; ++j) {
            textNum++;
        }
    }

    //读取CodeFile.txt的内容 统计字数
    file = fopen("../File/CodeFile.txt", "r");

    count = 0;
    char code[40 * 4][51] = {0};
    while (fgets(code[count], 51, file)) {
        count++;
    }

    fclose(file);
    //统计字数
    int codeNum = 0;
    for (int i = 0; code[i][0]; ++i) {
        for (int j = 0; code[i][j]; ++j) {
            codeNum++;
        }
    }

    //输出结果
    std::cout << "原文章字符个数：" << textNum << '\n';
    std::cout << "ASCII编码个数：" << textNum * 7 << '\n';
    std::cout << "哈夫曼编码个数：" << codeNum << '\n';
}

///private:

void HuffmanTree::Release(HuffmanNode *root) {
    if (root) {
        Release(root->lchild);
        Release(root->rchild);
        if (root->code) {
            delete []root->code;
        }
        delete root;
    }
}

char* HuffmanTree::getCode(char x) {
    HuffmanNode* Stack[128] = {0};
    int top = -1;

    Stack[++top] = root;
    //开始遍历
    while (top != -1) {
        if (Stack[top]->data == x) {
            return Stack[top]->code;
        } else if (Stack[top]->lchild != NULL){
            //无限进入左子树
            Stack[top + 1] = Stack[top]->lchild;
            top++;
        } else if (Stack[top]->rchild != NULL){
            //直到没有左子树，进一次右子树
            Stack[top + 1] = Stack[top]->rchild;
            top++;
        } else {
            //否则退回到上一个能进入不同右子树的结点
            HuffmanNode* temp = Stack[top];
            while (Stack[top]->rchild == NULL || Stack[top]->rchild == temp) {
                temp = Stack[top--];
            }
            Stack[top + 1] = Stack[top]->rchild;
            top++;
        }
    }
}

void HuffmanTree::InOrder(HuffmanNode *root) {
    //打开HuffmanTree.txt写入层序遍历
    FILE *file = fopen("../File/HuffmanTree.txt", "w");

    HuffmanNode* Q[128 * 2];
    int front = 0, rear = 0;

    Q[++rear] = root;
    while (front != rear) {
        HuffmanNode* temp = Q[++front];

        char msg[3] = {temp->data, ' ', '\0'};
        fwrite(msg, strlen(msg), 1, file);

        if (temp->lchild) {
            Q[++rear] = temp->lchild;
        }
        if (temp->rchild) {
            Q[++rear] = temp->rchild;
        }
    }

    fclose(file);
}

void HuffmanTree::show(HuffmanNode *root, HuffmanNode *child, char *prefix, int count) {
    prefix[count++] = '|';
    prefix[count] = '\0';

    if (child) {
        if (child->data == '\n') {
            std::cout << prefix << "--" << "\\n" << '(' << child->code << ')' << child->index << '\n';
        } else {
            std::cout << prefix << "--" << child->data << '(' << child->code << ')' << child->index<< '\n';
        }
        //第一次以及输出完右子树就把'|'去掉
        if (root == child || root->rchild == child){
            count--;
            prefix[count++] = ' ';
            prefix[count] = '\0';
        }
        prefix[count++] = ' ';
        prefix[count++] = ' ';
        prefix[count] = '\0';
        show(child, child->lchild, prefix, count);
        show(child, child->rchild, prefix, count);
    }
}

int HuffmanTree::Locate(char x, HuffmanNode* data[], int n) {
    for (int i = 0; i < n; ++i) {
        if (x == data[i]->data) {
            return i;
        }
    }
    return -1;
}

void HuffmanTree::BubbleSort(HuffmanNode* *data, int n) {
    int exchange = n;
    while (exchange){
        int bound = exchange;
        exchange = 0;
        for (int i = 1; i < bound; ++i) {
            if (data[i - 1]->index > data[i]->index) {
                HuffmanNode* temp = data[i];
                data[i] = data[i - 1];
                data[i - 1] = temp;
                exchange = i;
            }
        }
    }
}