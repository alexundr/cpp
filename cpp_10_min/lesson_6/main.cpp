#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    // ���������� � ������ ���������� � ������ ��������� ������
    cin.exceptions(cin.failbit);
    
    int returnCode = 0;
    
    try 
    {
        float Divd = 0;
        cout << "Enter Dividend: ";
        cin >> Divd;
        
        float Divr = 1;
        cout << "Enter Divisor: ";
        cin >> Divr;
        
        float Res = Divd/Divr;
        cout << Res << endl;
    }
    catch (...) // ��������� ����������
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
