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
	static inline __int64 WeaponSystemBase = Utils::GetAbsoluteAddress(Utils::sigscan("48 8B 05 ? ? ? ? 48 8B 88 ? ? ? ? 48 8B 01 48 85 C0 0F 84 ? ? ? ? 8B 80 ? ? ? ? 39 82 ? ? ? ? 0F 85 ? ? ? ? 48 8B 05", "GameAssembly.dll"),3,7);
	static inline __int64 GUIManager = Utils::GetAbsoluteAddress(Utils::sigscan("48 8B 05 ? ? ? ? 48 8B 80 ? ? ? ? 48 8B B0 ? ? ? ? 48 8B 05", "GameAssembly.dll"),3,7);
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
	static inline __int64 AddDeathMsg = Utils::GetAbsoluteAddress(Utils::sigscan("E8 ? ? ? ? 44 3B 73 18 0F 85", "GameAssembly.dll"),1,5);
	static inline __int64 AddMessageChat = Utils::GetAbsoluteAddress(Utils::sigscan("E8 ? ? ? ? 80 7B 21 00 0F 29 74 24", "GameAssembly.dll"),1,5);
	static inline __int64 send_detonateent = Utils::GetAbsoluteAddress(Utils::sigscan("E8 ? ? ? ? 48 8B 47 50 48 85 C0 0F 84 ? ? ? ? 8B 40 18", "GameAssembly.dll"),1,5);
	static inline __int64 GetBoneTransform = Utils::GetAbsoluteAddress(Utils::sigscan("E8 ? ? ? ? 48 8B 33 48 8B E8", "GameAssembly.dll"),1,5);
	static inline __int64 AppDomain_getCurDomain = Utils::GetAbsoluteAddress(Utils::sigscan("E8 ? ? ? ? 48 8D 4B 08 48 85 C0", "GameAssembly.dll"),1,5);
	static inline __int64 Component_1_GetComponent = Utils::GetAbsoluteAddress(Utils::sigscan("E8 ? ? ? ? 49 8B 4E 38 48 8B D8 48 8B 71 08", "GameAssembly.dll"),1,5);
	static inline __int64 material_set_color = Utils::GetAbsoluteAddress(Utils::sigscan("E8 ? ? ? ? 48 8B 4B 20 48 85 C9 74 67", "GameAssembly.dll"),1,5);
	static inline __int64 material_get_color = Utils::GetAbsoluteAddress(Utils::sigscan("E8 ? ? ? ? 0F 57 C0 0F 2F 40 0C", "GameAssembly.dll"),1,5);
	static inline __int64 material_set_shader = Utils::GetAbsoluteAddress(Utils::sigscan("E8 ? ? ? ? 48 8B 5C 24 ? 48 83 C4 20 5F C3 E8 ? ? ? ? CC CC 48 89 5C 24 ? 57 48 83 EC 20 80 3D ? ? ? ? ? 48 8B D9 75 1F 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? C6 05 ? ? ? ? ? 48 8B 15", "GameAssembly.dll"),1,5);
	static inline __int64 material_set_texture = Utils::GetAbsoluteAddress(Utils::sigscan("E8 ? ? ? ? 41 83 FE 20", "GameAssembly.dll"),1,5);
	static inline __int64 ShaderFind = Utils::GetAbsoluteAddress(Utils::sigscan("E8 ? ? ? ? 48 8B F8 48 8B 0D ? ? ? ? E8 ? ? ? ? 48 8B D8 48 85 C0 74 75", "GameAssembly.dll"),1,5);
	static inline __int64 material_get_main_texture = Utils::GetAbsoluteAddress(Utils::sigscan("E8 ? ? ? ? 48 89 43 60 48 8B 4B 18", "GameAssembly.dll"),1,5);
	static inline __int64 rendersettings_set_skybox = Utils::GetAbsoluteAddress(Utils::sigscan("E8 ? ? ? ? 33 D2 48 8B CB E8 ? ? ? ? 48 8B 4B 18 4C 8B 73 28", "GameAssembly.dll"),1,5);
	static inline __int64 ImageConversion_LoadImage = Utils::GetAbsoluteAddress(Utils::sigscan("E8 ? ? ? ? F3 0F 10 1D ? ? ? ? 48 8D 4C 24 ? 48 8B 7E 20", "GameAssembly.dll"),1,5);
	static inline __int64 GetBoneTransforminternal = Utils::sigscan("48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC 20 48 8B D9 8B EA 48 8B 49 30 ", "UnityPlayer.dll");
	static inline __int64 TryFire = Utils::sigscan("48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 40 80 3D ? ? ? ? ? 48 8B F9 75 5B ", "GameAssembly.dll");
	static inline __int64 UpdateFire = Utils::sigscan("48 89 5C 24 ? 57 48 83 EC 50 80 3D ? ? ? ? ? 48 8B F9 75 67", "GameAssembly.dll");
	static inline __int64 ABTest_IsActive = Utils::sigscan("48 89 5C 24 ? 57 48 83 EC 70 80 3D ? ? ? ? ? 75 2B", "GameAssembly.dll");
	static inline __int64 AppDomain_GetAssemblies = Utils::sigscan("48 89 5C 24 ? 48 89 6C 24 ? 41 56 48 83 EC 20 E8", "GameAssembly.dll");
	static inline __int64 Assembly_GetType = Utils::sigscan("48 83 EC 38 48 8B 01 45 33 C9 4C 8B 90 ? ? ? ? 48 8B 80 ? ? ? ? 48 89 44 24 ? 41 FF D2 48 83 C4 38 C3 CC CC CC CC CC CC CC CC CC CC CC 40 53 48 83 EC 20 33 C9", "GameAssembly.dll");
	static inline __int64 FireSpecEffects = Utils::sigscan("48 89 5C 24 ? 57 48 83 EC 30 80 3D ? ? ? ? ? 48 8B D9 75 37 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? C6 05 ? ? ? ? ? 33 C9", "GameAssembly.dll");
	static inline __int64 get_skybox = Addr::Il2cppResloveCall("UnityEngine.RenderSettings::get_skybox()");

	static inline __int64 weapon_raycast_call_unity_raycast = Utils::sigscan("48 8D ? ? E8 ? ? ? ? 84 C0 0F 84 ? ? ? ? 45 33 ? 48 8D ? ? 48 8D ? ? E8", "GameAssembly.dll")+4;
	static inline   __int64 getcamera = Addr::Il2cppResloveCall("UnityEngine.Camera::get_main");/*
	static inline   __int64 ScreenPointToRay = Addr::Il2cppResloveCall("UnityEngine.Camera::ScreenPointToRay");*/
	static inline   __int64 WorldToScreenPoint = Addr::Il2cppResloveCall("UnityEngine.Camera::WorldToScreenPoint_Injected");
	static inline   __int64 ApplicationQuit = Addr::Il2cppResloveCall("UnityEngine.Application::Quit(System.Int32)");
	static inline   __int64 GameObjectFind = Addr::Il2cppResloveCall("UnityEngine.GameObject::Find(System.String)");
	static inline   __int64 TransformFind = Addr::Il2cppResloveCall("UnityEngine.Transform::FindRelativeTransformWithPath");
	static inline   __int64 Material_get_shader = Addr::Il2cppResloveCall("UnityEngine.Material::get_shader()");
	static inline   __int64 transform_set_local_scale = Addr::Il2cppResloveCall("UnityEngine.Transform::set_localScale_Injected(UnityEngine.Vector3&)");
	
	/*RemotePlayersController
		"48 8B ? ? ? ? ? 0F 57 ? 0F 11 ? ? ? 48 8B ? ? ? ? ? 48 8B"
		"48 8B ? ? ? ? ? 33 D2 48 8B ? ? ? ? ? 48 89 ? 48 8B ? ? ? ? ? E8 ? ? ? ? 48 89 ? ? BA"
		"48 8B ? ? ? ? ? 48 8B ? ? ? ? ? 48 8B ? 48 85 ? 0F 84 ? ? ? ? 48 8B ? ? ? ? ? 48 85 ? 0F 84 ? ? ? ? 3B 79"
		"48 8B ? ? ? ? ? 48 8B ? ? ? ? ? 4C 8B ? 0F 1F"
		"48 8B ? ? ? ? ? 48 8B ? ? ? ? ? 48 8B ? 48 85 ? 74 ? 44 0F ? ? ? 8B D7"*/
};

