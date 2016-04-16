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
	bool AscForContinueYorN(const char *s)
	{
		char ch;
		bool failed = false;  // ������ �� ������������ ������
		
		do {
			cout << endl << s << " Press 'y' or 'n' and \"Enter\": ";
			cin >> ch;	
			
			failed = (ch != 'y' && ch != 'n');
			if (failed)
				cout << ". . . Error. Please enter 'y' or 'n'" << endl;
		} while (failed);
		
		return (ch != 'n');
	}
}
