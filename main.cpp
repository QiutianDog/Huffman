#include <iostream>
#include "HuffmanTree.h"
using namespace std;

// ����û�����
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
                cout << "��ʼ����ɣ�" << '\n';
                break;
            case 'E':
                if (!Initialization) {
                    cout << "��δ��ʼ����ɣ�" << '\n';
                } else {
                    hfm.Encoding();
                    EnCoding = true;
                    cout << "������ɣ�" << '\n';
                }
                break;
            case 'D':
                if (!Initialization) {
                    cout << "��δ��ʼ����ɣ�" << '\n';
                } else {
                    hfm.Decoding();
                    DeCoding = true;
                    cout << "������ɣ�" << '\n';
                }
                break;
            case 'P':
                if (!Initialization) {
                    cout << "��δ��ʼ����ɣ�" << '\n';
                } else if (!EnCoding && !DeCoding) {
                    cout << "��δ���б�������������" << '\n';
                } else if (!EnCoding) {
                    cout << "��δ���б��룡" << '\n';
                }else if (!DeCoding) {
                    cout << "��δ�������룡" << '\n';
                } else {
                    hfm.Print();
                }
                break;
            case 'T':
                if (!Initialization) {
                    cout << "��δ��ʼ����ɣ�" << '\n';
                } else {
                    hfm.TreePrint();
                }
                break;
            case 'C':
                if (!Initialization) {
                    cout << "��δ��ʼ����ɣ�" << '\n';
                } else if (!EnCoding) {
                    cout << "��δ���б��룡" << '\n';
                } else {
                    hfm.Compare();
                }
                break;
        }
        UserIndex();
        cin >> key;
    }
    cout << "�������˳���" << endl;
    return 0;
}

void UserIndex() {
    cout << "***********************************************" << endl;
    cout << "I ---- ��ʼ��             E ---- ����"  << endl;
    cout << "D ---- ����               P ---- ��ӡ�����ļ�" << endl;
    cout << "T ---- ��ӡ��������        C ---- �ȽϽ��" << endl;
    cout << "Q ---- ����" << endl;
    cout << "***********************************************" << endl;
    cout << "��ѡ���ܷ�������I��E��D��P��T��C �� Q����";
}