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
Vec3  Engine::TransformGetPosition(__int64 cashedptrtransform)
{
    __int64 TransformPropTables = *(__int64*)(cashedptrtransform + 0x40);
    int TransformIndex = *(int*)(cashedptrtransform + 0x48);
    __int64 PositionTable = *(__int64*)(TransformPropTables + 0x8);
    Vec3 TransformPositon = *(Vec3*)(PositionTable + TransformIndex * 48);
	return TransformPositon;
}

int width = 0;
int height= 0;
//  UnityEngine.Camera::WorldToScreenPoint_Injected(UnityEngine.Vector3&,UnityEngine.Camera/MonoOrStereoscopicEye,UnityEngine.Vector3&)

bool Engine::Worldtoscreen(Camera* camera, Vec3 position ,Vec3* wtsvec)
{
	static __int64 addr = 0;
	if (!addr)
		addr = Addr::Il2cppResloveCall("UnityEngine.Camera::WorldToScreenPoint_Injected");
	const auto WorldToScreen = reinterpret_cast <void(*)(Camera* cam,Vec3* targetpos, unsigned int eye,Vec3* ScreenPos)>(addr);
	WorldToScreen(camera,&position, 2,wtsvec);
	if (wtsvec->z <= 1) 
		return false;
	wtsvec->y = ImGui::GetIO().DisplaySize.y - wtsvec->y;
	return  true;
}