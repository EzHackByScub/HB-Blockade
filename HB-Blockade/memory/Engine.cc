#include "Engine.hh"
#include <iostream>
#include "../imgui/imgui.h"


Camera* Engine::GetCameraMain()
{
	const auto GetCam = reinterpret_cast <Camera*(*)()>(Addr::getcamera);
	return GetCam();
}

RemotePlayersController* Engine::GetRemotePlayersController() {
	if (!Addr::RemotePlayersController)
		return nullptr;
	__int64 a2da = *(__int64*)(Addr::RemotePlayersController);
	if (a2da < 0x00000000C0008649) // 2000BB39
		return nullptr;
	RemotePlayersController* controller = (RemotePlayersController*)*(__int64*)*(__int64*)(a2da + 0xB8);
	return controller;
}

__int64* Engine::GetClient() {
	if (!Addr::Clinet)
		return nullptr;
	__int64 a2da = *(__int64*)(Addr::Clinet);
	if (a2da < 0x00000000C0008649) //
		return nullptr;
	__int64* client = (__int64*)*(__int64*)*(__int64*)(a2da + 0xB8);
	return client;
}

//void __fastcall sub_18043F0C0(__int64 Client, __int64 IsTeamchant, __int64 message, __int64 a4
void Engine::client_send_msg(const wchar_t* message ) {
	auto Client = Engine::GetClient();
	if (!Client)
		return;
	System::String msg{};
	msg.Length = wcslen(message);
	if (msg.Length >= 256)
		return;
	memcpy((void*)&msg.Value, message, static_cast<size_t>(msg.Length) * 2);
	if (msg.Length < 0 )
		return;
	if (!Addr::client_sendchat)
		return;
	const auto send_msg = reinterpret_cast<void(__fastcall*)(__int64* Client, __int64 IsTeamchant, System::String* message, __int64* a4)>(Addr::client_sendchat);
	send_msg(Client, 0,&msg,nullptr);

}




Vec3*  Engine::InternalTransform_GetPosition(__int64 internal_transform)
{
	__int64 TransformPropTables = *(__int64*)(internal_transform + 0x38);
	int TransformIndex = *(int*)(internal_transform + 0x40);
	__int64 PositionTable = *(__int64*)(TransformPropTables + 0x18);
	Vec3* TransformPositon = (Vec3*)(PositionTable + static_cast<__int64>(TransformIndex) * 48);
	return TransformPositon;
}
__int64  Engine::GO_Get_InternalTransform (__int64 Gameobject)
{
	auto internal_gameObject = *(__int64*)(Gameobject + 0x10);
	if (!internal_gameObject) return 0;
	auto gameObject_components = *(__int64*)(internal_gameObject + 0x30);
	if (!gameObject_components) return 0;
	auto gameObject_internal_transform = *(__int64*)(gameObject_components + 0x8);
		return gameObject_internal_transform;
}

const char*  Engine::GameObject_GetName(__int64 Gameobject)
{
	auto internal_gameObject = *(__int64*)(Gameobject + 0x10);
	if (!internal_gameObject) return "";
	auto name = (const char*)(internal_gameObject + 0x60);
	if (!name) return "";
	return name;
}
Vec3*  Engine::GameObject_GetPosition(__int64 Gameobject)
{
	auto intTransform = Engine::GO_Get_InternalTransform(Gameobject);
	Vec3 nullvec = { 0,-1000,0 };
	if (!intTransform)
		return &nullvec;
	return Engine::InternalTransform_GetPosition(intTransform);
}

//  UnityEngine.Camera::WorldToScreenPoint_Injected(UnityEngine.Vector3&,UnityEngine.Camera/MonoOrStereoscopicEye,UnityEngine.Vector3&)
bool Engine::Worldtoscreen(Camera* camera, Vec3 position ,Vec3* wtsvec)
{
	const auto WorldToScreenPoint_Injected = reinterpret_cast <void(*)(Camera* cam,Vec3* targetpos, unsigned int eye,Vec3* ScreenPos)>(Addr::WorldToScreenPoint);
	WorldToScreenPoint_Injected(camera,&position, 2,wtsvec);
	if (wtsvec->z <= 1) 
		return false;
	wtsvec->y = Global_vars::ScreenH - wtsvec->y;
	return  true;
}

bool Engine::LineCast(Vec3 Startpos, Vec3 endpos, RaycastHit* hitinfo)
{
	const auto line_cast = reinterpret_cast<bool(*)(Vec3* Startpos, Vec3* endpos, RaycastHit * hitinfo)>(Addr::Linecast);
	return line_cast(&Startpos, &endpos, hitinfo);


}	
 void  Engine::send_reload(int wid)
{
	 auto client = Engine::GetClient();
	 if (!client) return;
	const auto sendreload = reinterpret_cast<void(__fastcall*)(__int64* client, int wid,float)>(Addr::client_sendreload);
	return sendreload(client,wid,0);
}
  void  Engine::send_prereload(int wid)
{
	 auto client = Engine::GetClient();
	 if (!client) return;
	const auto sendreload = reinterpret_cast<void(__fastcall*)(__int64* client, int wid,float)>(Addr::client_sendprereload);
	return sendreload(client,wid,0);
}
