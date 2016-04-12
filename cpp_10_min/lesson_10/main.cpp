#include <iostream>

#include "PromptModule.h"
#include "ErrorHandlingModule.h"

using namespace std;

// Берем делимое
float getDividend(void)
{
	float d = 1;
	cout << "Enter Dividend" << endl;
	cin >> d;
	return d;
}

// Берем делитель
float getDivisor(void)
{
	float d = 1;
	cout << "Enter Divisor" << endl;
	cin >> d;
	return d;
}

// Делим
float Divide(const float dividend, const float divisor)
{
	return (dividend / divisor);
}

int main(int argc, char** argv) 
{
	SAMSErrorHandling::Initialize();
	int returnCode = 0;
	
	do {
		try {
			float dividend = getDividend();
			float divisor  = getDivisor();
			
			cout << Divide(dividend, divisor) << endl;
		}
		catch (...) {
			returnCode = SAMSErrorHandling::HandleNotANumberError();
		}
	} while(SAMSPrompt::AscForContinueYorN("More division?"));
	
	SAMSPrompt::PauseForUser();
	
	return returnCode;
}
