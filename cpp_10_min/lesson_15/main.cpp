#include <iostream>
#include <stdexcept>

#include "PromptModule.h"
#include "ErrorHandlingModule.h"

using namespace std;



// ����� ���� ��������
char getOperator(void)
{
	char d;
	cin >> d;
	return d;
}

// ����� �������
float getOperand(void)
{
	float d = 1;
	cin >> d;
	return d;
}

// ��������������� ������� ��� ����������������
bool TestOk(const char theOperator, const float theOperand, const float theExpectedResult)
{
	// ��������� � ��������� ������ = ��������
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

// ������� ����������������
void SelfTest(void)
{
	float oldValue = Accumulator('='); // ��������
	
	try {
		if (TestOk('@', 0, 0) && TestOk('+', 3, 3) && TestOk('-', 2, 1) &&
			TestOk('*', 4, 4) && TestOk('/', 2, 2)) { // ��������� ��������� �������
			cout << "Test completed successfully" << endl;
		}
		else { // �������
			cout << "Test failed" << endl;
		}
	} 
	catch(...) { // �� ����� ��������� ��������� ����������
		cout << "An exception occured during self test" << endl;
	}
	
	Accumulator('@', oldValue);
}

int main(int argc, char** argv) 
{
	
	SAMSErrorHandling::Initialize();
	char Operator; // ������ �������� ������������ � �����
	
	do {
		try {
			char Operator = getOperator();
			
			if (Operator == '+' || 
				Operator == '-' ||
				Operator == '*' ||
				Operator == '/' ||
				Operator == '@')
			{
				float Operand = getOperand(); // �������� � ��������� ������
				Accumulator(Operator, Operand);
			}
			else if (Operator == '!')
			{
				SelfTest(); // ����������������
			}
			else if (Operator == '.')
			{
				// ������ �� ������
			}
			else {	// ��� ���� �����������, ��� ��������
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
	
	Tape('.'); // �������� �����, ��� �� �����������
	
	return 0;
}
