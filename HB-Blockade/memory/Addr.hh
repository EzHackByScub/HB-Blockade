#pragma once
#include "Utils.hh"
#include "Windows.h"
class Global_vars
{
public:
	static inline	float ScreenH, ScreenW;
};

class Addr
{
public:
	static inline  auto Il2cppResloveCall = reinterpret_cast<__int64(__fastcall*)(const char*)>(GetProcAddress(GetModuleHandleA("GameAssembly.dll"), "il2cpp_resolve_icall"));
	static inline __int64 RemotePlayersController = Utils::refSigscan("48 8B ? ? ? ? ? 48 8B ? ? ? ? ? 4C 8B ? 0F 1F", "GameAssembly.dll");
	static inline __int64 callScreenPointToRay = Utils::sigscan("E8 ? ? ? ? 0F 10 ? 0F 11 ? ? F2 0F ? ? ? F2 0F ? ? ? 41 81 FE", "GameAssembly.dll");
//	static inline __int64 sendEos = Utils::sigscan("48 89 ? ? ? 57 48 83 EC ? 80 3D 52 A9 60 02", "GameAssembly.dll");
	static inline __int64 Linecast = Utils::refSigscan("F3 0F ? ? ? E8 ? ? ? ? 33 D2 48 8D ? ? E8 ? ? ? ? 48 8B", "GameAssembly.dll",5);
	static inline __int64 weapon_raycast_call_unity_raycast = Utils::sigscan("48 8D ? ? E8 ? ? ? ? 84 C0 0F 84 ? ? ? ? 45 33 ? 48 8D ? ? 48 8D ? ? E8", "GameAssembly.dll")+4;
	static inline   __int64 getcamera = Addr::Il2cppResloveCall("UnityEngine.Camera::get_main");
	static inline   __int64 ScreenPointToRay = Addr::Il2cppResloveCall("UnityEngine.Camera::ScreenPointToRay");
	static inline   __int64 WorldToScreenPoint = Addr::Il2cppResloveCall("UnityEngine.Camera::WorldToScreenPoint_Injected");
	
	/*RemotePlayersController
		"48 8B ? ? ? ? ? 33 D2 48 8B ? ? ? ? ? 48 89 ? 48 8B ? ? ? ? ? E8 ? ? ? ? 48 89 ? ? BA"
		"48 8B ? ? ? ? ? 0F 57 ? 0F 11 ? ? ? 48 8B ? ? ? ? ? 48 8B"
		"48 8B ? ? ? ? ? 48 8B ? ? ? ? ? 48 8B ? 48 85 ? 0F 84 ? ? ? ? 48 8B ? ? ? ? ? 48 85 ? 0F 84 ? ? ? ? 3B 79"
		"48 8B ? ? ? ? ? 48 8B ? ? ? ? ? 4C 8B ? 0F 1F"
		"48 8B ? ? ? ? ? 48 8B ? ? ? ? ? 48 8B ? 48 85 ? 74 ? 44 0F ? ? ? 8B D7"*/



};

