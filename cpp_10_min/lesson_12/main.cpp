#include <iostream>
#include <stdexcept>

#include "PromptModule.h"
#include "ErrorHandlingModule.h"

using namespace std;

// Функция ленты (история операций)
void Tape(const char theOperator, const float theOperand)
{
	static const int myTapeSize = 3;
	static char myOperator[myTapeSize];
	static float myOperand[myTapeSize];
	static int myNumberOfEntries = 0; // счетчик имеющихся в ленте записей
	
	if (theOperator != '?') // Если нужно добавить запись
	{
		if (myNumberOfEntries < myTapeSize) // место есть
		{
			myOperator[myNumberOfEntries] = theOperator;
			myOperand[myNumberOfEntries]  = theOperand;
			myNumberOfEntries++;
		}
		else // массив полностью забит
		{
			throw runtime_error("Error - out of room on the tape.");
		}
	}
	else // Распечатать ленту
	{
		for (int Index = 0; Index < myNumberOfEntries; Index++)
		{
			cout << myOperator[Index] << ", " << myOperand[Index] << endl;
		}
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
