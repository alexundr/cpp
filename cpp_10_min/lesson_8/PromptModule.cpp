#include <iostream>

#include "PromptModule.h"

namespace SAMSPrompt 
{
	using namespace std;
	
	// пауза вконце
	void PauseForUser(void)
	{
		char ch;
		cout << "Press any key and \"Enter\" : ";
		cin >> ch;
	}
}
