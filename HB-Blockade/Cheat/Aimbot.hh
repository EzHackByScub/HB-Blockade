#pragma once
#include "../memory/GameClasses.hh"
//typedef __int64(__stdcall* ScreenToRay) (__int64 a1, __int64 a2, unsigned __int64* a3);
typedef bool(__stdcall* PhysicsRaycast)(Ray a1, RaycastHit* hitinfo, float a3, int a4);
// char __fastcall Physics_Raycast_m9F5CAD8DA7923E897C5DCAF913BD411AD1A87950(__int64 a1, __int64 a2, float a3, int a4)
class Aimbot
{
public:
	//static __int64 SpoofTest(__int64 a1, __int64 a2, unsigned __int64* a3);
//	static inline ScreenToRay oScreenToRayadr;
	static inline PhysicsRaycast oRaycast;
	static bool  Physics_Raycast_hk(Ray a1, RaycastHit* hitinfo, float a3, int a4);
	
	static inline float fov = 150;


};

