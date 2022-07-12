#include "Engine.hh"
#include <iostream>
#include "../imgui/imgui.h"
#include <array>

Camera* Engine::GetCameraMain()
{
	const auto GetCam = reinterpret_cast <Camera*(*)()>(Addr::getcamera);
	return GetCam();
}

RemotePlayersController* Engine::GetRemotePlayersController() {
	if (!Addr::RemotePlayersController)
		return nullptr;
	__int64 a2da = *(__int64*)(Addr::RemotePlayersController);
	if (a2da < 0x0000000030008649) // 2000BB39
		return nullptr;
	RemotePlayersController* controller = (RemotePlayersController*)*(__int64*)*(__int64*)(a2da + 0xB8);
	return controller;
}
WeaponSystem* Engine::GetWeaponSystem() {
	if (!Addr::WeaponSystemBase)
		return nullptr;
	__int64 a2da = *(__int64*)(Addr::WeaponSystemBase);
	if (a2da < 0x0000000030008649) // 2000BB39
		return nullptr;
	WeaponSystem* controller = (WeaponSystem*)*(__int64*)*(__int64*)(a2da + 0xB8);
	return controller;
}
__int64* Engine::GetGUIManger() {
	if (!Addr::GUIManager)
		return nullptr;
	__int64 a2da = *(__int64*)(Addr::GUIManager);
	if (a2da < 0x0000000030008649) // 2000BB39
		return nullptr;
	__int64* controller = (__int64*)*(__int64*)(a2da + 0xB8);
	return controller;
}

__int64* Engine::GetClient() {
	if (!Addr::Clinet)
		return nullptr;
	__int64 a2da = *(__int64*)(Addr::Clinet);
	if (a2da < 0x0000000030008649) //
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
__int64  Engine::InterGO_Get_InternalTransform(__int64 Gameobject)
{
	auto gameObject_components = *(__int64*)(Gameobject + 0x30);
	if (!gameObject_components) return 0;
	auto gameObject_internal_transform = *(__int64*)(gameObject_components + 0x8);
	return gameObject_internal_transform;
}
__int64  Engine::GO_Get_InternalTransform (__int64 Gameobject)
{
	auto internal_gameObject = *(__int64*)(Gameobject + 0x10);
	if (!internal_gameObject) return 0;
		return InterGO_Get_InternalTransform(internal_gameObject);
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
bool Engine::WorldtoscreenTestWh(Camera* came, Vec3* wtsvec, Vec3 position)  // string to find in IDA    UnityEngine.Camera::get_main() __int64 Camerauncashed, Vector3 inScreenPos, float* positionTarget, unsigned __int8 eye, BYTE* a5
{
	auto camecashe = came->m_cashedptr;
	if (!camecashe) return false;
	Vec3 tvec{ came->m_cashedptr->matrix._14, came->m_cashedptr->matrix._24, came->m_cashedptr->matrix._34 };
	Vec3 rvec{ came->m_cashedptr->matrix._11, came->m_cashedptr->matrix._21, came->m_cashedptr->matrix._31 };
	Vec3 upvec{ came->m_cashedptr->matrix._12, came->m_cashedptr->matrix._22, came->m_cashedptr->matrix._32 };
	float w = tvec.Dot(position) + came->m_cashedptr->matrix._44;
	if (w < 0.098f)
		return false;
	float y = upvec.Dot(position) + came->m_cashedptr->matrix._42;
	float x = rvec.Dot(position) + came->m_cashedptr->matrix._41;
	wtsvec->x = (ImGui::GetIO().DisplaySize.x / 2) * (1.f + x / w);
	wtsvec->y = (ImGui::GetIO().DisplaySize.y / 2) * (1.f - y / w);
	return true;
}

Vec2 ReturnAngle(Vec2 angle)
{
	if (angle.x + 360 > 360)
		return { angle.x,angle.y + 90 };
	return { angle.x + 360,angle.y + 90 };
}
Vec2 Engine::CalcAngle(Vec3 startPOS, Vec3 endPOS)
{
	float deltaX = endPOS.x - startPOS.x;
	float deltaY = endPOS.y - startPOS.y;
	float deltaZ = endPOS.z - startPOS.z;
	float dist = sqrt(pow((endPOS.x - startPOS.x), 2.0) + pow((endPOS.y - startPOS.y), 2.0) + pow((endPOS.z - startPOS.z), 2.0));

	if (dist < 0)
	{
		dist = dist * -1;
	}

	float xzlength = sqrt((deltaX * deltaX) + (deltaZ * deltaZ));
	float angleX = atan2(deltaY, xzlength) * (-57.2957795);
	float angleY = atan2(deltaX, deltaZ) * (57.2957795);
	Vec2 angle = { angleY,angleX };
	//Vec2 angleRet = ReturnAngle(angle);
	return  angle;
}

bool Engine::LineCast(Vec3 Startpos, Vec3 endpos, RaycastHit* hitinfo)
{
	const auto line_cast = reinterpret_cast<bool(*)(Vec3* Startpos, Vec3* endpos, RaycastHit * hitinfo)>(Addr::Linecast);
	return line_cast(&Startpos, &endpos, hitinfo);
}	
__int64 Engine::GetBoneTransforminternal(__int64 Animatorinternal, __int8 boneid)
{
	const auto line_cast = reinterpret_cast<__int64(*)(__int64 Animatorinternal, __int8 boneid)>(Addr::GetBoneTransforminternal);
	return line_cast(Animatorinternal, boneid);
}
__int64 Engine::AppDomain_getCurDomain()
{
	const auto line_cast = reinterpret_cast<__int64(*)()>(Addr::AppDomain_getCurDomain);
	return line_cast();
}
Assemblies_Array Engine::AppDomain_GetAssemblies(__int64 AppDomain, bool refOnly)
{
	const auto line_cast = reinterpret_cast<Assemblies_Array(*)(__int64 AppDomain, bool refOnly)>(Addr::AppDomain_GetAssemblies);
	return line_cast(AppDomain, refOnly);
}
__int64* Engine::Assembly_GetType(__int64* Assembly, System::String* name, bool throwOnError)
{
	const auto line_cast = reinterpret_cast<__int64*(*)(__int64* Assembly, System::String * name, bool throwOnError)>(Addr::Assembly_GetType);
	return line_cast(Assembly, name, throwOnError);
}
void Engine::transform_set_local_scale(__int64 Transform,Vec3* scale)
{
	const auto line_cast = reinterpret_cast<void(*)(__int64 Transform, Vec3*  scale)>(Addr::transform_set_local_scale);
	return line_cast(Transform, scale);
}
__int64* Engine::get_skybox()
{
	const auto line_cast = reinterpret_cast<__int64*(*)()>(Addr::get_skybox);
	return line_cast();
}
__int64* Engine::material_set_color(__int64* Material, Color color)
{
	const auto line_cast = reinterpret_cast<__int64*(*)(__int64* Material, Color color)>(Addr::material_set_color);
	return line_cast(Material,color);
}
Color Engine::material_get_color(__int64* Material)
{
	const auto line_cast = reinterpret_cast<Color(*)(__int64* Material)>(Addr::material_get_color);
	return line_cast(Material);
}
void Engine::material_set_shader(__int64* Material,__int64* Shader)
{
	const auto line_cast = reinterpret_cast<void(*)(__int64* Material, __int64* Shader)>(Addr::material_set_shader);
	return line_cast(Material,Shader);
}
void Engine::material_set_texture(__int64* Material,__int64* Texture)
{
	const auto line_cast = reinterpret_cast<void(*)(__int64* Material, __int64* Texture)>(Addr::material_set_texture);
	return line_cast(Material, Texture);
}
void Engine::SetAnimalWeapon(RemotePlayersController* pc,__int8 weaponid)
{
	const auto line_cast = reinterpret_cast<void(*)(RemotePlayersController * pc, __int8 weaponid)>(Addr::SetAnimal);
	return line_cast(pc, weaponid);
}
__int64* Engine::material_get_main_texture(__int64* Material)
{
	const auto line_cast = reinterpret_cast<__int64* (*)(__int64* Material)>(Addr::material_get_main_texture);
	return line_cast(Material);
}
bool Engine::ImageConversion_LoadImage(__int64* Texure2d,byte data[] )
{
	const auto line_cast = reinterpret_cast<bool(*)(__int64* Texure2d, byte data[])>(Addr::ImageConversion_LoadImage);
	return line_cast(Texure2d,data);
}
__int64* Engine::ShaderFind(System::String* name)
{
	const auto line_cast = reinterpret_cast<__int64* (*)(System::String * name)>(Addr::ShaderFind);
	return line_cast(name);
}
__int64* Engine::Material_get_shader(__int64* Material)
{
	const auto line_cast = reinterpret_cast<__int64* (*)(__int64* Material)>(Addr::Material_get_shader);
	return line_cast(Material);
}
__int64* Engine::rendersettings_set_skybox(__int64* Material)
{
	const auto line_cast = reinterpret_cast<__int64*(*)(__int64* Material)>(Addr::rendersettings_set_skybox);
	return line_cast(Material);
}
__int64* Engine::Component_1_GetComponent(__int64* Component, __int64* Type)
{
	const auto line_cast = reinterpret_cast<__int64*(*)(__int64* Component, __int64* Type)>(Addr::Component_1_GetComponent);
	return line_cast(Component, Type);
}
__int64* Engine::GameObjectFind(System::String* name)
{
	const auto GetCam = reinterpret_cast <__int64* (*)(System::String * name)>(Addr::GameObjectFind);
	return GetCam(name);
}
 void  Engine::send_reload(int wid)
{
	 auto client = Engine::GetClient();
	 if (!client) return;
	const auto sendreload = reinterpret_cast<void(__fastcall*)(__int64* client, int wid,float)>(Addr::client_sendreload);
	return sendreload(client,wid,0);
} 
 void  Engine::send_exploid(__int64* client, int uid, Vec3 pos)
{
	const auto sendreload = reinterpret_cast<void(__fastcall*)(__int64* client, int uid, Vec3 pos)>(Addr::send_detonateent);
	return sendreload(client, uid, pos);
} 
 void  Engine::Fire(__int64* vp_FPWeaponShooter)
{
	const auto sendreload = reinterpret_cast<void(__fastcall*)(__int64* vp_FPWeaponShooter)>(Addr::TryFire);
	return sendreload(vp_FPWeaponShooter);
} 
 __int64*  Engine::TransformFind(__int64* transform,System::String* name, bool xz)
{
	const auto sendreload = reinterpret_cast<__int64* (__fastcall*)(__int64* transform, System::String * name, bool xz)>(Addr::TransformFind);
	return sendreload(transform,name, xz);
}
  void  Engine::send_prereload(int wid)
{
	 auto client = Engine::GetClient();
	 if (!client) return;
	const auto sendreload = reinterpret_cast<void(__fastcall*)(__int64* client, int wid,float)>(Addr::client_sendprereload);
	return sendreload(client,wid,0);
}
