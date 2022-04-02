#include "Utils.hh"
#include <Windows.h>
#include <vector>
#include"minhook/src/hde/hde64.h"

bool Utils::wcsicmp(const wchar_t* a, const wchar_t* b) {
	if (!a)
		return false;
	int ret = 0;
	wchar_t* p1 = (wchar_t*)a;
	wchar_t* p2 = (wchar_t*)b;
	while (!(ret = *p1 - *p2) && *p2)
		++p1, ++p2;
	return ret == 0;
}


__int64 Utils::sigscan(const char* pattern, const char* mod)
{
	uintptr_t moduleAdressmm = 0;
	moduleAdressmm = (__int64)GetModuleHandleA(mod);

	static auto patternToByteZmm = [](const char* pattern)
	{
		auto       bytesmm = std::vector<int>{};
		const auto startmm = const_cast<char*>(pattern);
		const auto endmm = const_cast<char*>(pattern) + strlen(pattern);

		for (auto currentmm = startmm; currentmm < endmm; ++currentmm)
		{
			if (*currentmm == '?')
			{
				++currentmm;
				if (*currentmm == '?')
					++currentmm;
				bytesmm.push_back(-1);
			}
			else { bytesmm.push_back(strtoul(currentmm, &currentmm, 16)); }
		}
		return bytesmm;
	};

	const auto dosHeadermm = (PIMAGE_DOS_HEADER)moduleAdressmm;
	const auto ntHeadersmm = (PIMAGE_NT_HEADERS)((std::uint8_t*)moduleAdressmm + dosHeadermm->e_lfanew);

	const auto sizeOfImage = ntHeadersmm->OptionalHeader.SizeOfImage;
	auto       patternBytesmm = patternToByteZmm(pattern);
	const auto scanBytesmm = reinterpret_cast<std::uint8_t*>(moduleAdressmm);

	const auto smm = patternBytesmm.size();
	const auto dmm = patternBytesmm.data();

	for (auto imm = 0ul; imm < sizeOfImage - smm; ++imm)
	{
		bool foundmm = true;
		for (auto jmm = 0ul; jmm < smm; ++jmm)
		{
			if (scanBytesmm[imm + jmm] != dmm[jmm] && dmm[jmm] != -1)
			{
				foundmm = false;
				break;
			}
		}
		if (foundmm) { return reinterpret_cast<uintptr_t>(&scanBytesmm[imm]); }
	}
	return NULL;
}
__int64 Utils::GetAbsoluteAddress(__int64 address, int offset, int size) {
		auto addrs = address + size + *(int*)(address + offset);
		return addrs;
}
__int64 Utils::refSigscan(const char* signature , const char* mod) {
	__int64 address = Utils::sigscan(signature , mod);
	if (!address)
		return NULL;
	hde64s instr;
	int len = hde64_disasm((void*)address, &instr);
	if (len > 7) // cmp [],value
		return (address + len + *(int*)(address + 3)); 
	return (address + len + *(int*)(address + len - 4));
}


char* Utils::strstr(char* input, const char* find)
{
	do {
		const char* p, * q;
		for (p = input, q = find; *q != '\0' && *p == *q; p++, q++) {}
		if (*q == '\0') {
			return input;
		}
		
	} while (*(input++) != '\0');
	return 0;
}

 bool Utils::strcmp(char* a, char* b) {
	if ((uintptr_t)a == 0x00000000ffffffff || (uintptr_t)b == 0x00000000ffffffff)
		return false;
	if ((uintptr_t)a == 0x000000000000007d || (uintptr_t)b == 0x000000000000007d)
		return false;
	if (!a || !b) return !a && !b;
	int ret = 0;
	unsigned char* p1 = (unsigned char*)a;
	unsigned char* p2 = (unsigned char*)b;
	while (!(ret = *p1 - *p2) && *p2)
		++p1, ++p2;
	return ret == 0;
}
