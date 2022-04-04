#include "Engine.hh"
#include <iostream>
#include "../imgui/imgui.h"


Camera* Engine::GetCameraMain()
{
	static __int64 addr = 0;
	if (!addr)
		addr = Addr::Il2cppResloveCall("UnityEngine.Camera::get_main");
	const auto GetCam = reinterpret_cast <Camera*(*)()>(addr);
	return GetCam();
}

RemotePlayersController* Engine::GetRemotePlayersController() {
	if (!Addr::RemotePlayersController)
		return nullptr;
	__int64 a2da = *(__int64*)(Addr::RemotePlayersController);
	if (a2da < 0x00000000C0008649) // 2000BB39 MagicNumer
		return nullptr;

	if (!a2da)
		return nullptr;

	RemotePlayersController* controller = (RemotePlayersController*)*(__int64*)*(__int64*)(a2da + 0xB8);
	return controller;
}


Vec3  Engine::InternalTransform_GetPosition(__int64 internal_transform)
{
	__int64 TransformPropTables = *(__int64*)(internal_transform + 0x38);
	int TransformIndex = *(int*)(internal_transform + 0x40);
	__int64 PositionTable = *(__int64*)(TransformPropTables + 0x18);
	Vec3 TransformPositon = *(Vec3*)(PositionTable + TransformIndex * 48);
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
Vec3  Engine::GameObject_GetPosition(__int64 Gameobject)
{
	auto intTransform = Engine::GO_Get_InternalTransform(Gameobject);
	if (!intTransform)
		return { 0,-1000,0 };
	return Engine::InternalTransform_GetPosition(intTransform);
}
int width = 0;
int height= 0;
//  UnityEngine.Camera::WorldToScreenPoint_Injected(UnityEngine.Vector3&,UnityEngine.Camera/MonoOrStereoscopicEye,UnityEngine.Vector3&)

bool Engine::Worldtoscreen(Camera* camera, Vec3 position ,Vec3* wtsvec)
{
	const auto WorldToScreen = reinterpret_cast <void(*)(Camera* cam,Vec3* targetpos, unsigned int eye,Vec3* ScreenPos)>(Addr::WorldToScreenPoint);
	WorldToScreen(camera,&position, 2,wtsvec);
	if (wtsvec->z <= 1) 
		return false;
	wtsvec->y = ImGui::GetIO().DisplaySize.y - wtsvec->y;
	return  true;
}

bool Engine::LineCast(Vec3 Startpos, Vec3 endpos, RaycastHit* hitinfo)
{
	return reinterpret_cast <bool(*)(Vec3 Startpos, Vec3 endpos, RaycastHit * hitinfo)>(Addr::Linecast)(Startpos, endpos, hitinfo);
}