#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    // Подготовка к вызову исключения в случае ошибочных данных
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
    catch (...) // обработка исключений
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
