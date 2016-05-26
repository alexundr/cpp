#include <iostream>
#include <stdexcept>

#include "PromptModule.h"
#include "ErrorHandlingModule.h"

using namespace std;

// Функция ленты (история операций)
void Tape(const char theOperator, const float theOperand = 0)
{
	static const int myTapeChunk = 3;
	static int myTapeSize = myTapeChunk;
	static char *myOperator = new char[myTapeSize];
	static float *myOperand = new float[myTapeSize];
	static int myNumberOfEntries = 0; // счетчик имеющихся в ленте записей
	
	switch (theOperator)
	{
		// Распечатать ленту
		case '?':
			for (int Index = 0; Index < myNumberOfEntries; Index++)
			{
				cout << myOperator[Index] << ", " << myOperand[Index] << endl;
			}
			break;
		
		// программа завершается - удалить массив
		case '.':
			delete [] myOperator; // без [] удалится не весь массив, а его нулевой эллемент
			delete [] myOperand;
			break;
			
		// Добавить к ленте и, если необходимо - расширить
		default:
			if (myNumberOfEntries == myTapeSize) // нужно расширить ленту
			{
				// создаем переменные для расширения
				char *ExpandedOperator = new char[myTapeSize + myTapeChunk];
				float *ExpandedOperand = new float[myTapeSize + myTapeChunk];
				
				// Создаем дополнительные указатели для копирования массива, не нарушив изначальные адреса нового и строго массива ленты
				char *FromOperator = myOperator;
				float *FromOperand = myOperand;
				
				char *ToOperator = ExpandedOperator;
				float *ToOperand = ExpandedOperand;
				
				// Копировать старые массивы в новые
				// Копирование по указателях быстрее, чем с помощью индексов, потому что 
				// ExpandedOperator[index] равносильно записи (*(ExpandedOperator+(index*sizeof(char))))
				// что при больших массивах может существенно замедлить программу
				for (int index = 0; index < myNumberOfEntries; index++)
				{
					*ToOperator++ = *FromOperator++; // * иммет старшинство перед ++. Поэтму сначала присвоится старое значение, а потом увеличится указатель
					*ToOperand++  = *FromOperand++;
				}
				
				// Удалить старые массивы
				delete [] myOperator;
				delete [] myOperand;
				
				// Заменим старые указатели на новые
				myOperator = ExpandedOperator;
				myOperand  = ExpandedOperand;
				
				// записать новый размер массива
				myTapeSize += myTapeChunk;
			}
			
			// теперь можно добавить новую запись
			myOperator[myNumberOfEntries] = theOperator;
			myOperand[myNumberOfEntries]  = theOperand;
			myNumberOfEntries++;
	}
}

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

// Функция подсчета/аккумулирования
float Accumulator(const char theOperator, const float Operand = 0)
{
	static float myAccumulator = 0;
	
	switch (theOperator)
	{
		case '+':
			myAccumulator += Operand; 
			Tape(theOperator, Operand);
			break;
		case '-':
			myAccumulator -= Operand;
			Tape(theOperator, Operand);
			break;
		case '*':
			myAccumulator *= Operand;
			Tape(theOperator, Operand);
			break;
		case '/':
			myAccumulator /= Operand;
			Tape(theOperator, Operand);
			break;
		case '@':
			myAccumulator = Operand;
			Tape(theOperator, Operand);
			break;
		case '=':
			cout << endl << myAccumulator << endl;
			break;
		case '?':
			Tape(theOperator);
			break;
		default:
			throw runtime_error("Error - Invalid Operator!");
	};
	
	return myAccumulator;
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
