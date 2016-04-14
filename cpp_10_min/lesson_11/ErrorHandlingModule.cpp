#include <iostream>
#include <stdexcept>

#include "ErrorHandlingModule.h"

namespace SAMSErrorHandling 
{
	using namespace std;
	
	// �������������
	void Initialize(void)
	{
		cin.exceptions(cin.failbit);
	}
	
	// ��������� ����������
	int HandleNotANumberError(void)
	{
		cerr << "Error!" << endl;
		cin.clear();
		
		char s[5];
		cin >> s;
		
		return 1;
	}
	
	// ������ ���������
	int HandleRuntimeError(runtime_error theRuntimeError)
	{
		cerr << theRuntimeError.what() << endl;
		
		return 1;
	}
}
