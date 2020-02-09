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
    // "r" ֻ���� file
    FILE *file = fopen("../File/TextFile1.txt", "r");

    int count = 0;
    char text[40][51] = {0};
    while (fgets(text[count], 51, file)){
        count++;
    }

    // �ر� file
    fclose(file);

    //ͳ�Ƹ����ַ���Ȩֵ
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

    //����������� �������Ϊ'@'
    HuffmanNode *temp;
    while (count > 1) {
        //����
        BubbleSort(nodeList, count);
        //����½��
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

    //����������HuffmanTree.txt�ļ���
    InOrder(root);

    //�������б���
    char code[128] = {0};
    count = 0;

    HuffmanNode* stack[128];
    int top = -1;
    stack[++top] = root;

    while (top != -1) {
        while (temp) {
            //����
            char *msg = new char[count + 1];
            for (int i = 0; i < count; ++i) {
                msg[i] = code[i];
            }
            msg[count] = '\0';
            temp->code = msg;
            //����������
            if (temp->lchild) {
                temp = temp->lchild;
                stack[++top] = temp;
                code[count++] = '0';
            } else break;
        }
        //�˻ص���һ���ܽ��벻ͬ�������Ľ��
        HuffmanNode* p = stack[top];
        while (!temp->rchild || temp->rchild == p) {
            if (top == 0) {
                return;
            } //top == 0 ʱ˵��ȫ���������
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
    //��TextFile1.txt�ļ��е����ı�
    FILE *file = fopen("../File/TextFile1.txt", "r");

    int count = 0;
    char text[40][51] = {0};

    while (fgets(text[count], 51, file)) {
        count++;
    }

    fclose(file);

    //��CodeFile.txt�ļ�д������
    file = fopen("../File/CodeFile.txt", "w");

    //��ʼ����
    for (int i = 0; text[i][0]; ++i) {
        for (int j = 0; text[i][j]; ++j) {
            char *code = getCode(text[i][j]);
            fwrite(code, strlen(code), 1, file);
        }
    }

    fclose(file);
}

void HuffmanTree::Decoding() {
    //��CodeFile.txt��ȡ����
    FILE *file = fopen("../File/CodeFile.txt", "r");

    int count = 0;
    char code[40 * 4][51] = {0};

    while (fgets(code[count], 51, file)) {
        count++;
    }

    fclose(file);

    //��TextFile2.txt��д������
    file = fopen("../File/TextFile2.txt", "w");

    //ͨ�����������ַ�
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
                temp = root;//����
                j--;
            }
        }
    }
    char msg[2] = {temp->data, '\0'};
    fwrite(msg, strlen(msg), 1, file);

    fclose(file);
}

void HuffmanTree::Print() {
    //��TextFile1.txt�ļ��е����ı�
    FILE *file = fopen("../File/TextFile1.txt", "r");

    int count = 0;
    char text[40][51] = {0};

    while (fgets(text[count], 51, file)) {
        count++;
    }

    fclose(file);

    //��ӡԭ���ַ���
    std::cout << "ԭ�ַ���Ϊ��" << std::endl;
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

    //��HuffmanTree.txt�ļ��е����ı�
    file = fopen("../File/HuffmanTree.txt", "r");

    count = 0;
    char tree[40][51] = {0};

    while (fgets(tree[count], 51, file)) {
        count++;
    }

    fclose(file);

    //��ӡ��������
    std::cout << "����������Ϊ��" << std::endl;
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

    //��TextFile2.txt�ļ��е����ı�
    file = fopen("../File/TextFile2.txt", "r");

    count = 0;
    char out[40][51] = {0};

    while (fgets(out[count], 51, file)) {
        count++;
    }

    fclose(file);

    //��ӡ����
    std::cout << "������Ϊ��" << std::endl;
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
    //TODO ֱ�۴��������
    char prefix[128] = {0};
    int count = 0;
    show(root, root, prefix, count);
}

void HuffmanTree::Compare() {
    //��ȡTextFile1.txt������ ͳ������
    FILE *file = fopen("../File/TextFile1.txt", "r");

    int count = 0;
    char text[40][51] = {0};
    while (fgets(text[count], 51, file)) {
        count++;
    }

    fclose(file);
    //ͳ������
    int textNum = 0;
    for (int i = 0; text[i][0]; ++i) {
        for (int j = 0; text[i][j]; ++j) {
            textNum++;
        }
    }

    //��ȡCodeFile.txt������ ͳ������
    file = fopen("../File/CodeFile.txt", "r");

    count = 0;
    char code[40 * 4][51] = {0};
    while (fgets(code[count], 51, file)) {
        count++;
    }

    fclose(file);
    //ͳ������
    int codeNum = 0;
    for (int i = 0; code[i][0]; ++i) {
        for (int j = 0; code[i][j]; ++j) {
            codeNum++;
        }
    }

    //������
    std::cout << "ԭ�����ַ�������" << textNum << '\n';
    std::cout << "ASCII���������" << textNum * 7 << '\n';
    std::cout << "���������������" << codeNum << '\n';
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
    //��ʼ����
    while (top != -1) {
        if (Stack[top]->data == x) {
            return Stack[top]->code;
        } else if (Stack[top]->lchild != NULL){
            //���޽���������
            Stack[top + 1] = Stack[top]->lchild;
            top++;
        } else if (Stack[top]->rchild != NULL){
            //ֱ��û������������һ��������
            Stack[top + 1] = Stack[top]->rchild;
            top++;
        } else {
            //�����˻ص���һ���ܽ��벻ͬ�������Ľ��
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
    //��HuffmanTree.txtд��������
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
        //��һ���Լ�������������Ͱ�'|'ȥ��
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