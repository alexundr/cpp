#include <iostream>

#include "ErrorHandlingModule.h"

namespace SAMSErrorHandling 
{
	using namespace std;
	
	// Инициализация
	void Initialize(void)
	{
		cin.exceptions(cin.failbit);
	}
	
	// Обработка исключения
	int HandleNotANumberError(void)
	{
		cerr << "Error!" << endl;
		cin.clear();
		
		char s[5];
		cin >> s;
		
		return 1;
	}
}
