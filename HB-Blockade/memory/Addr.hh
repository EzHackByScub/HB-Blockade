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
	static inline __int64 RemotePlayersController = Utils::refSigscan("7C ? 48 8B ? ? ? ? ? 48 8B ? ? ? ? ? 48 8B ? 48 85 ? 74 ? 83 B9 E0 00 00 00", "GameAssembly.dll",2);
	//static inline __int64 RemotePlayersController = Utils::refSigscan("48 8B ? ? ? ? ? 48 8B ? ? ? ? ? 4C 8B ? 0F 1F", "GameAssembly.dll");

	//static inline __int64 callScreenPointToRay = Utils::sigscan("E8 ? ? ? ? 0F 10 ? 0F 11 ? ? F2 0F ? ? ? F2 0F ? ? ? 41 81 FE", "GameAssembly.dll");
//	static inline __int64 sendEos = Utils::sigscan("48 89 ? ? ? 57 48 83 EC ? 80 3D 52 A9 60 02", "GameAssembly.dll");
	static inline __int64 Linecast = Utils::refSigscan("48 8D 4D B7 44 89 75 BF E8 ? ? ? ? 33 D2 48 8D 4D D7 E8", "GameAssembly.dll",8);

	// void __fastcall sub_18043F0C0(__int64 Client, __int64 IsTeamchant, __int64 message, __int64 a4)
	static inline __int64 client_sendchat = Utils::refSigscan("0F B6 ? ? E8 ? ? ? ? 33 C9 E8", "GameAssembly.dll",4);
	static inline __int64 client_sendattack = Utils::refSigscan("0F B6 ? ? ? ? ? ? E8 ? ? ? ? 48 81 C4 ? ? ? ? C3", "GameAssembly.dll",8);

	static inline __int64 client_sendreload = Utils::refSigscan("8B D7 48 8B ? E8 ? ? ? ? 4C 8B ? ? ? 48 8B ? ? ? 48 8B ? ? ? 48 8B ? ? ? 48 83 C4 ? 5F", "GameAssembly.dll", 5);
	static inline __int64 client_sendprereload = Utils::refSigscan("8B D7 48 8B ? E8 ? ? ? ? B0 ? 48 8B ? ? ? 48 8B ? ? ? 48 83 C4", "GameAssembly.dll", 5);




	static inline __int64 FPweaponreloader_ongui= Utils::refSigscan("81 B8 ? ? 00 00 ? ? ? ? 74 ? 33 D2 E8 ? ? ? ? 33", "GameAssembly.dll",14);



	// Chat.OnGUI  call Client.sendChat   
	static inline __int64 Clinet = Utils::refSigscan("48 8B ? ? ? ? ? 48 8B ? ? ? ? ? 48 8B ? 48 85 ? 0F 84 ? ? ? ? 4C 8B ? ? 45 33 ? 0F B6", "GameAssembly.dll");



	static inline __int64 weapon_raycast = Utils::refSigscan("48 89 ? ? ? E8 ? ? ? ? E9 ? ? ? ? 48 8B ? ? ? ? ? 48 8B", "GameAssembly.dll",5);

	static inline __int64 weapon_raycast_call_unity_raycast = Utils::sigscan("48 8D ? ? E8 ? ? ? ? 84 C0 0F 84 ? ? ? ? 45 33 ? 48 8D ? ? 48 8D ? ? E8", "GameAssembly.dll")+4;
	static inline   __int64 getcamera = Addr::Il2cppResloveCall("UnityEngine.Camera::get_main");/*
	static inline   __int64 ScreenPointToRay = Addr::Il2cppResloveCall("UnityEngine.Camera::ScreenPointToRay");*/
	static inline   __int64 WorldToScreenPoint = Addr::Il2cppResloveCall("UnityEngine.Camera::WorldToScreenPoint_Injected");
	static inline   __int64 ApplicationQuit = Addr::Il2cppResloveCall("UnityEngine.Application::Quit(System.Int32)");
	
	/*RemotePlayersController
		"48 8B ? ? ? ? ? 0F 57 ? 0F 11 ? ? ? 48 8B ? ? ? ? ? 48 8B"
		"48 8B ? ? ? ? ? 33 D2 48 8B ? ? ? ? ? 48 89 ? 48 8B ? ? ? ? ? E8 ? ? ? ? 48 89 ? ? BA"
		"48 8B ? ? ? ? ? 48 8B ? ? ? ? ? 48 8B ? 48 85 ? 0F 84 ? ? ? ? 48 8B ? ? ? ? ? 48 85 ? 0F 84 ? ? ? ? 3B 79"
		"48 8B ? ? ? ? ? 48 8B ? ? ? ? ? 4C 8B ? 0F 1F"
		"48 8B ? ? ? ? ? 48 8B ? ? ? ? ? 48 8B ? 48 85 ? 74 ? 44 0F ? ? ? 8B D7"*/
};

