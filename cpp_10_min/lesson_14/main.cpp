#include <iostream>
#include <stdexcept>

#include "PromptModule.h"
#include "ErrorHandlingModule.h"

using namespace std;

// ������� ����� (������� ��������)
void Tape(const char theOperator, const float theOperand = 0)
{
	static const int myTapeChunk = 3;
	static int myTapeSize = myTapeChunk;
	static char *myOperator = new char[myTapeSize];
	static float *myOperand = new float[myTapeSize];
	static int myNumberOfEntries = 0; // ������� ��������� � ����� �������
	
	switch (theOperator)
	{
		// ����������� �����
		case '?':
			for (int Index = 0; Index < myNumberOfEntries; Index++)
			{
				cout << myOperator[Index] << ", " << myOperand[Index] << endl;
			}
			break;
		
		// ��������� ����������� - ������� ������
		case '.':
			delete [] myOperator; // ��� [] �������� �� ���� ������, � ��� ������� ��������
			delete [] myOperand;
			break;
			
		// �������� � ����� �, ���� ���������� - ���������
		default:
			if (myNumberOfEntries == myTapeSize) // ����� ��������� �����
			{
				// ������� ���������� ��� ����������
				char *ExpandedOperator = new char[myTapeSize + myTapeChunk];
				float *ExpandedOperand = new float[myTapeSize + myTapeChunk];
				
				// ������� �������������� ��������� ��� ����������� �������, �� ������� ����������� ������ ������ � ������ ������� �����
				char *FromOperator = myOperator;
				float *FromOperand = myOperand;
				
				char *ToOperator = ExpandedOperator;
				float *ToOperand = ExpandedOperand;
				
				// ���������� ������ ������� � �����
				// ����������� �� ���������� �������, ��� � ������� ��������, ������ ��� 
				// ExpandedOperator[index] ����������� ������ (*(ExpandedOperator+(index*sizeof(char))))
				// ��� ��� ������� �������� ����� ����������� ��������� ���������
				for (int index = 0; index < myNumberOfEntries; index++)
				{
					*ToOperator++ = *FromOperator++; // * ����� ����������� ����� ++. ������ ������� ���������� ������ ��������, � ����� ���������� ���������
					*ToOperand++  = *FromOperand++;
				}
				
				// ������� ������ �������
				delete [] myOperator;
				delete [] myOperand;
				
				// ������� ������ ��������� �� �����
				myOperator = ExpandedOperator;
				myOperand  = ExpandedOperand;
				
				// �������� ����� ������ �������
				myTapeSize += myTapeChunk;
			}
			
			// ������ ����� �������� ����� ������
			myOperator[myNumberOfEntries] = theOperator;
			myOperand[myNumberOfEntries]  = theOperand;
			myNumberOfEntries++;
	}
}

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

// ������� ��������/���������������
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
