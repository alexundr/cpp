#include <iostream>
#include <stdexcept>

#include "PromptModule.h"
#include "ErrorHandlingModule.h"

using namespace std;

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
float Accumulate(const char theOperand, const float Operand)
{
	static float myAccumulator = 0;
	
	switch (theOperand)
	{
		case '+':
			myAccumulator += Operand; break;
		case '-':
			myAccumulator -= Operand; break;
		case '*':
			myAccumulator *= Operand; break;
		case '/':
			myAccumulator /= Operand; break;
		default:
			throw runtime_error("Error - Invalid Operator!");
	};
	
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
