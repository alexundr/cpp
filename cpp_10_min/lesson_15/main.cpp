#include <iostream>
#include <stdexcept>

#include "PromptModule.h"
#include "ErrorHandlingModule.h"

using namespace std;



// Берем знак операции
char getOperator(void)
{
	char d;
	cin >> d;
	return d;
}

// Берем операнд
float getOperand(void)
{
	float d = 1;
	cin >> d;
	return d;
}

// Вспомогательная функция при самотестировании
bool TestOk(const char theOperator, const float theOperand, const float theExpectedResult)
{
	// Результат с плавающей точкой = сумматор
	float result = Accumulator(theOperator, theOperand);
	
	if (result == theExpectedResult) {
		cout << theOperator << theOperand << " - success" << endl;
		return true;
	}
	else {
		cout << theOperator << theOperand << " - failed. Expected" <<
		theExpectedResult << ", got " << result << endl;
		return false;
	}
}

// Функция самотетсирования
void SelfTest(void)
{
	float oldValue = Accumulator('='); // Сумматор
	
	try {
		if (TestOk('@', 0, 0) && TestOk('+', 3, 3) && TestOk('-', 2, 1) &&
			TestOk('*', 4, 4) && TestOk('/', 2, 2)) { // Испытание закончено успешно
			cout << "Test completed successfully" << endl;
		}
		else { // Неудача
			cout << "Test failed" << endl;
		}
	} 
	catch(...) { // Во время испытания произошло исключение
		cout << "An exception occured during self test" << endl;
	}
	
	Accumulator('@', oldValue);
}

int main(int argc, char** argv) 
{
	
	SAMSErrorHandling::Initialize();
	char Operator; // Символ Оператор используемый в цикле
	
	do {
		try {
			char Operator = getOperator();
			
			if (Operator == '+' || 
				Operator == '-' ||
				Operator == '*' ||
				Operator == '/' ||
				Operator == '@')
			{
				float Operand = getOperand(); // Опперанд с плавающей точкой
				Accumulator(Operator, Operand);
			}
			else if (Operator == '!')
			{
				SelfTest(); // Самотестирование
			}
			else if (Operator == '.')
			{
				// Ничего не делать
			}
			else {	// Еще один аккумулятор, нет операнда
				Accumulator(Operator);
			}
			
		}
		catch (runtime_error RuntimeError)
		{
			SAMSErrorHandling::HandleRuntimeError(RuntimeError);
		}
		catch (...) {
			SAMSErrorHandling::HandleNotANumberError();
		}
	} while(Operator != '.');
	
	Tape('.'); // Сообщить ленте, что мы заканчиваем
	
	return 0;
}
