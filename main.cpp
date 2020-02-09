#include <iostream>
#include "HuffmanTree.h"
using namespace std;

// 输出用户界面
void UserIndex();

int main() {
    UserIndex();
    char key;
    cin >> key;

    HuffmanTree hfm;
    bool Initialization = false;
    bool EnCoding = false;
    bool DeCoding = false;
    while (key != 'Q') {
        switch (key) {
            case 'I':
                hfm.Initialization();
                Initialization = true;
                cout << "初始化完成！" << '\n';
                break;
            case 'E':
                if (!Initialization) {
                    cout << "尚未初始化完成！" << '\n';
                } else {
                    hfm.Encoding();
                    EnCoding = true;
                    cout << "编码完成！" << '\n';
                }
                break;
            case 'D':
                if (!Initialization) {
                    cout << "尚未初始化完成！" << '\n';
                } else {
                    hfm.Decoding();
                    DeCoding = true;
                    cout << "译码完成！" << '\n';
                }
                break;
            case 'P':
                if (!Initialization) {
                    cout << "尚未初始化完成！" << '\n';
                } else if (!EnCoding && !DeCoding) {
                    cout << "尚未进行编码和译码操作！" << '\n';
                } else if (!EnCoding) {
                    cout << "尚未进行编码！" << '\n';
                }else if (!DeCoding) {
                    cout << "尚未进行译码！" << '\n';
                } else {
                    hfm.Print();
                }
                break;
            case 'T':
                if (!Initialization) {
                    cout << "尚未初始化完成！" << '\n';
                } else {
                    hfm.TreePrint();
                }
                break;
            case 'C':
                if (!Initialization) {
                    cout << "尚未初始化完成！" << '\n';
                } else if (!EnCoding) {
                    cout << "尚未进行编码！" << '\n';
                } else {
                    hfm.Compare();
                }
                break;
        }
        UserIndex();
        cin >> key;
    }
    cout << "程序已退出！" << endl;
    return 0;
}

void UserIndex() {
    cout << "***********************************************" << endl;
    cout << "I ---- 初始化             E ---- 编码"  << endl;
    cout << "D ---- 译码               P ---- 打印代码文件" << endl;
    cout << "T ---- 打印哈夫曼树        C ---- 比较结果" << endl;
    cout << "Q ---- 结束" << endl;
    cout << "***********************************************" << endl;
    cout << "请选择功能符（输入I、E、D、P、T、C 和 Q）：";
}