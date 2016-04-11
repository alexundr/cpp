#include <iostream>

using namespace std; 

// инициализация для исключений
void Initialize(void)
{
	cin.exceptions(cin.failbit);
}

// Взять делимое
float getDividend(void)
{
	float Dividend = 1;
	cout << "Enter Dividend: ";
	cin >> Dividend;
	return Dividend;
}

// Взять делитель
float getDivisor(void)
{
	float Divisor = 1;
	cout << "Enter Divisor: ";
	cin >> Divisor;
	return Divisor;
}

// Выполнить операцию деления
float Divide(const float theDividend, const float theDivisor)
{
	return (theDividend / theDivisor);
}

// Обработка исключения
int HandleNotANumberError(void)
{
	cerr << "Error!" << endl;
	cin.clear();
	char ch[5];
	cin >> ch;
	return 1; // произошла ошибка
}

// Задержка перед выходом
void PauseForUser(void)
{
	char StopChar;
	cout << "Press any key and \"Enter\" :";
	cin >> StopChar;
}

int main(int argc, char *argv[])
{
    Initialize();
	
	int returnCode = 0;
    
    try 
    {
        float Dividend = getDividend();
        float Divisor  = getDivisor();
        cout << Divide(Dividend, Divisor) << endl;
    }
    catch (...) // обработка исключений
    {
        returnCode = HandleNotANumberError();
    }

    PauseForUser();
    
    return returnCode;
}
