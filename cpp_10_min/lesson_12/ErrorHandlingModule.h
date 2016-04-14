#ifndef ErrorHandlingH
#define ErrorHandlingH
	
	namespace SAMSErrorHandling
	{
		void Initialize(void);
		int HandleNotANumberError(void);
		int HandleRuntimeError(std::runtime_error);
	}

#endif
