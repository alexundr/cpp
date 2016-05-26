#ifndef AccumulatorModuleH
#define AccumulatorModuleH

namespace SAMSCalculator
{
	
	// Перечисление допустимых операций
	enum anOperator {add, subtract, multiply, devide, reset, query};
	
	// Структура Записи в ленте
	struct aTapeElement {
		char Operator;
		float Operand;
		aTapeElement *NextElement;
	};
	
	// Сумматор с плавающей точкой
	float Accumulator (const anOperator theOperator, const float theOperand = 0);
	
	// Функция ленты (история операций)
	void Tape(const char theOperator, const float theOperand = 0);
}

#endif
