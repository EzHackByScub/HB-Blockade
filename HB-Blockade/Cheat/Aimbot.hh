#pragma once
typedef __int64(__stdcall* ScreenToRay) (__int64 a1, __int64 a2, unsigned __int64* a3);
class Aimbot
{
public:
	static __int64 SpoofTest(__int64 a1, __int64 a2, unsigned __int64* a3);
	static inline ScreenToRay oScreenToRayadr;
	static inline float fov = 150;


};

