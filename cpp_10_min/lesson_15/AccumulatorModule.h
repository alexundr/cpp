#ifndef AccumulatorModuleH
#define AccumulatorModuleH

namespace SAMSCalculator
{
	
	// ������������ ���������� ��������
	enum anOperator {add, subtract, multiply, devide, reset, query};
	
	// ��������� ������ � �����
	struct aTapeElement {
		char Operator;
		float Operand;
		aTapeElement *NextElement;
	};
	
	// �������� � ��������� ������
	float Accumulator (const anOperator theOperator, const float theOperand = 0);
	
	// ������� ����� (������� ��������)
	void Tape(const char theOperator, const float theOperand = 0);
}

#endif
