#define _CRT_SECURE_NO_WARNINGS
#include "Net.h"
using namespace std;

int main()
{
    Graph graph;

    cout << "==================================================" << endl;
    cout << "**\t\t �������ģ��ϵͳ\t\t**" << endl;
    cout << "==================================================" << endl;
    cout << "**\t\tA --- ������������\t\t**" << endl;
    cout << "**\t\tB --- ��ӵ����ı�\t\t**" << endl;
    cout << "**\t\tC --- ������С������\t\t**" << endl;
    cout << "**\t\tD --- ��ʾ��С������\t\t**" << endl;
    cout << "**\t\tE --- �˳�   ����\t\t**" << endl;
    cout << "==================================================" << endl;

    //�˳������ʶ
    bool quit = false;
    char option;
    while (!quit)
    {
        cout << endl
            << "��ѡ�������";
        cin >> option;
        switch (option)
        {
        case 'a':
        case 'A':
            graph.CreateVertex();
            break;
        case 'b':
        case 'B':
            graph.AddEdge();
            break;
        case 'c':
        case 'C':
            graph.BuildMST();
            break;
        case 'd':
        case 'D':
            graph.PrintMST();
            break;
        case 'e':
        case 'E':
            quit = true;
            cout << "Press any key to continue... " << endl;
            break;

        default:
            cout << "�����������������룡" << endl;
            cin.clear();
            cin.ignore(1024, '\n');
            break;
        }
    }
    return 0;
}
