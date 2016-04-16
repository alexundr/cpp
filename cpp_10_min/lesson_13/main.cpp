#include <iostream>
#include <stdexcept>

#include "PromptModule.h"
#include "ErrorHandlingModule.h"

using namespace std;

// ������� ����� (������� ��������)
void Tape(const char theOperator, const float theOperand)
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
	cout << "Enter Operator: " << endl;
	cin >> d;
	return d;
}

// ����� �������
float getOperand(void)
{
	float d = 1;
	cout << "Enter Operand: " << endl;
	cin >> d;
	return d;
}

// ������� ��������/���������������
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
