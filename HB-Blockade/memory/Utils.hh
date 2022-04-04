#pragma once

class Utils
{
public:
	static __int64 sigscan( const char* pattern , const char* module = nullptr);
	static __int64 refSigscan(const char* pattern, const char* module = nullptr,  int sigoffset=0);
	static __int64 GetAbsoluteAddress(__int64 address, int offset, int size);

	/// <summary>
	/// replace:  call game+0x123
	/// to 
	/// call nearbuffer
	/// nearbuffer:
	/// jmp dst
	/// </summary>
	/// <param name="src">poiter to Original call</param>
	/// <param name="dst">pointer to replaced call</param>
	/// <param name="poriginal">original call</param>
	/// <returns>Original call address</returns>
	static  bool SpoofCall(void* src, void* dst, __int64* poriginal);
	static bool wcsicmp(const wchar_t* a, const wchar_t* b);
	static char* strstr(char* input, const char* find);
	static bool strcmp(char* a, char* b);
};


