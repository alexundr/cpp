#include <iostream>

#include "PromptModule.h"

namespace SAMSPrompt 
{
	using namespace std;
	
	// ����� ������
	void PauseForUser(void)
	{
		char ch;
		cout << "Press any key and \"Enter\" : ";
		cin >> ch;
	}
}
