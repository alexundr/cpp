#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    int returnCode = 0;
    
    float Divd = 0;
    cout << "Enter Dividend: ";
    cin >> Divd;
    
    if (!cin.fail()) // ������� - �� �����
    {
        float Divr = 1;
        cout << "Enter Divisor: ";
        cin >> Divr;
        
        if (!cin.fail()) // �������� - �������
        {
            float Res = Divd/Divr;
            cout << Res << endl;
        }
        else
        {
            cerr << "Input error" << endl;
            cin.clear();    // �������� ���� ������ �������� ������
            char badInp[5]; // ������ �������� � 5 ����
            cin >> badInp;  // ������� ��������� �������, ����� ��� �� ��������
            returnCode = 1;
        }
    }
    else 
    {
        cerr << "Input error" << endl;
        cin.clear();    // �������� ���� ������ �������� ������
        char badInp[5]; // ������ �������� � 5 ����
        cin >> badInp;  // ������� ��������� �������, ����� ��� �� ��������
        returnCode = 1;
    }

    char stopChar;
    cout << "Press any key and \"Enter\" to continue" << endl;
    cin >> stopChar;
    
    return returnCode;
}
