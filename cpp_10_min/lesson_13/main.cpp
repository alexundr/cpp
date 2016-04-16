#include <iostream>
#include <stdexcept>

#include "PromptModule.h"
#include "ErrorHandlingModule.h"

using namespace std;

// Функция ленты (история операций)
void Tape(const char theOperator, const float theOperand)
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
	cout << "Enter Operator: " << endl;
	cin >> d;
	return d;
}

// Берем операнд
float getOperand(void)
{
	float d = 1;
	cout << "Enter Operand: " << endl;
	cin >> d;
	return d;
}

// Функция подсчета/аккумулирования
float Accumulate(const char theOperator, const float Operand)
{
	static float myAccumulator = 0;
	
	switch (theOperator)
	{
		case '+':
			myAccumulator += Operand; break;
		case '-':
			myAccumulator -= Operand; break;
		case '*':
			myAccumulator *= Operand; break;
		case '/':
			myAccumulator /= Operand; break;
		case '?':
			break;
		default:
			throw runtime_error("Error - Invalid Operator!");
	};
	
	Tape(theOperator, Operand);
	
	return myAccumulator;
}

int main(int argc, char** argv) 
{
	SAMSErrorHandling::Initialize();
	int returnCode = 0;
	
	do {
		try {
			char Operator = getOperator();
			float Operand = getOperand();
			
			cout << Accumulate(Operator, Operand) << endl;
		}
		catch (runtime_error RuntimeError)
		{
			SAMSErrorHandling::HandleRuntimeError(RuntimeError);
		}
		catch (...) {
			returnCode = SAMSErrorHandling::HandleNotANumberError();
		}
	} while(SAMSPrompt::AscForContinueYorN("More division?"));
	
	SAMSPrompt::PauseForUser();
	
	return returnCode;
}
