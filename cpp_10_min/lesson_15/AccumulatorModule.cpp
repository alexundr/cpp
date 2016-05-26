#include <stdexcept>
#include <iostream>

#include "AccumulatorModule.h"

namespace SAMSCalculator
{
	using namespace std;
	
	// ��������
	float Accumulator (const anOperator theOperator, const float theOperand = 0)
	{
		static float myAccumulator = 0;
		
		switch (theOperator)
		{
			case add:
				myAccumulator += theOperand; 
				break;
			case subtract:
				myAccumulator -= Operand;
				break;
			case multiply:
				myAccumulator *= Operand;
				break;
			case divide:
				myAccumulator /= Operand;
				break;
			case reset:
				myAccumulator = Operand;
				break;
			case query:
				// �� ������ ��������� ��������� - �� ������ ������
				break;
			default:
				throw runtime_error("Error - Invalid Operator!");
		};
		
		return myAccumulator;
	}
	
	// ������� ����� (������� ��������)
	void Tape(const char theOperator, const float theOperand = 0)
	{
		static aTapeElement *TapeRoot = NULL;
		
		if (theOperator == '?') { // ����������� �����
			printTape(TapeRoot);
		}
		else if (theOperator == '.') { //������� �����
			DeleteTape(TapeRoot);
		}
		else { // ���������� ��������: �������� � �����
			aTapeElement NewElement = new aTapeElement;
			NewElement->Operator = theOperator;
			NewElement->Operand = theOperand;
			
			NewElement->NextElement = NULL;
			
			if (TapeRoot == NULL) { // ���� �������� ��������� ������
				TapeRoot = NewElement;
			}
			else { // �������� ������� � ����� ������
				// ������ �������
				aTapeElement *CurrentTapeElement = TapeRoot;
				
				// ... � ���������� �� �����
				while (CurrentTapeElement->NextElement != null) {
					CurrentTapeElement = CurrentTapeElement->NextElement;
				}
				
				// ������ CurrentTapeElement ��������� �� ��������� ������� � ������
				CurrentTapeElement->NextElement = NewElement;
			}
		}
	}
	
	
}
