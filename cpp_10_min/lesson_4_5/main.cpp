#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    int returnCode = 0;
    
    float Divd = 0;
    cout << "Enter Dividend: ";
    cin >> Divd;
    
    if (!cin.fail()) // Делимое - не число
    {
        float Divr = 1;
        cout << "Enter Divisor: ";
        cin >> Divr;
        
        if (!cin.fail()) // Делитель - нечисло
        {
            float Res = Divd/Divr;
            cout << Res << endl;
        }
        else
        {
            cerr << "Input error" << endl;
            cin.clear();    // Очистить биты ошибки входного потока
            char badInp[5]; // массив символов в 5 штук
            cin >> badInp;  // Сожрать ошибочные символы, иначе они не исчезнут
            returnCode = 1;
        }
    }
    else 
    {
        cerr << "Input error" << endl;
        cin.clear();    // Очистить биты ошибки входного потока
        char badInp[5]; // массив символов в 5 штук
        cin >> badInp;  // Сожрать ошибочные символы, иначе они не исчезнут
        returnCode = 1;
    }

    char stopChar;
    cout << "Press any key and \"Enter\" to continue" << endl;
    cin >> stopChar;
    
    return returnCode;
}
