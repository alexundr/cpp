#include <stdexcept>
#include <iostream>

#include "AccumulatorModule.h"

namespace SAMSCalculator
{
	using namespace std;
	
	// Сумматор
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
				// Мы всегда возвращае результат - не делать ничего
				break;
			default:
				throw runtime_error("Error - Invalid Operator!");
		};
		
		return myAccumulator;
	}
	
	// Функция ленты (история операций)
	void Tape(const char theOperator, const float theOperand = 0)
	{
		static aTapeElement *TapeRoot = NULL;
		
		if (theOperator == '?') { // Распечатать ленту
			printTape(TapeRoot);
		}
		else if (theOperator == '.') { //Удалить ленту
			DeleteTape(TapeRoot);
		}
		else { // Нормальное действие: добавить к ленте
			aTapeElement NewElement = new aTapeElement;
			NewElement->Operator = theOperator;
			NewElement->Operand = theOperand;
			
			NewElement->NextElement = NULL;
			
			if (TapeRoot == NULL) { // Если корневой указатель пустой
				TapeRoot = NewElement;
			}
			else { // Добавить елемент в конец списка
				// Начать сначала
				aTapeElement *CurrentTapeElement = TapeRoot;
				
				// ... и пропустить до конца
				while (CurrentTapeElement->NextElement != null) {
					CurrentTapeElement = CurrentTapeElement->NextElement;
				}
				
				// Сейчас CurrentTapeElement указывает на последний елемент в списке
				CurrentTapeElement->NextElement = NewElement;
			}
		}
	}
	
	
}
