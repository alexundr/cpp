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
	
	// ��������� ��
	bool AscForContinue(const char *s)
	{
		char ch;
		
		cout << endl << s << " Press 'n' and \"Enter\" to stop: ";
		cin >> ch;
		return (ch != 'n');
	}
}
