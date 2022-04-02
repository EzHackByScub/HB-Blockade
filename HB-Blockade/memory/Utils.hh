#pragma once

class Utils
{
public:
	static __int64 sigscan( const char* pattern , const char* module = nullptr);
	static __int64 refSigscan(const char* pattern, const char* module = nullptr);
	static __int64 GetAbsoluteAddress(__int64 address, int offset, int size);
	static bool wcsicmp(const wchar_t* a, const wchar_t* b);
	static char* strstr(char* input, const char* find);
	static bool strcmp(char* a, char* b);
};


