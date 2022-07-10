#pragma once
#include "Addr.hh"
#include "GameClasses.hh"

class Engine
{
public:
	static Camera* GetCameraMain();
	static __int64* GetClient();
	static void  send_reload(int wid);
	static void  send_prereload(int wid);



	static  RemotePlayersController* GetRemotePlayersController();
	static Vec3* InternalTransform_GetPosition(__int64 transform);
	static Vec3* GameObject_GetPosition(__int64 Gameobject);
	static const char* GameObject_GetName(__int64 Gameobject);
	static void client_send_msg(const wchar_t* message);

	static __int64  GO_Get_InternalTransform(__int64 Gameobject);
	static bool WorldtoscreenTestWh(Camera* came, Vec3* wtsvec, Vec3 position);
	static bool LineCast(Vec3 Startpos, Vec3 endpos, RaycastHit* hitinfo);
	static  void  send_exploid(__int64* client, int uid, Vec3 pos);
	static  void  Fire(__int64* vp_FPWeaponShooter);
	static __int64 GetBoneTransforminternal(__int64 Animatorinternal, __int8 boneid);
	static __int64 ComponentGetTransform(__int64 Component);
	static void TransformGetPosition(__int64* Transform, Vec3* vector_out);
	static __int64  InterGO_Get_InternalTransform(__int64 Gameobject);
	static  __int64* GameObjectFind(System::String* name);
	static  __int64* TransformFind(__int64* transform, System::String* name, bool xz);
	static __int64 AppDomain_getCurDomain();
	static Assemblies_Array AppDomain_GetAssemblies(__int64 AppDomain, bool refOnly);
	static __int64* Assembly_GetType(__int64* Assembly, System::String* name, bool throwOnError);
	static void CreatePlayer(RemotePlayersController* playercontroller, int playerindex);
	static void RestorePlayer(RemotePlayersController* playercontroller, int playerindex);
	static void  SetCurrentWeapon(RemotePlayersController* playercontroller, int playerindex, int weaponid);
	static __int64* get_skybox();
	static __int64* material_set_color(__int64* Material, Color color);
	static WeaponSystem* GetWeaponSystem();
	static __int64* Component_1_GetComponent(__int64* Component, __int64* Type);
	static __int64* rendersettings_set_skybox(__int64* Material);
	static Color material_get_color(__int64* Material);
	static void material_set_shader(__int64* Material, __int64* Shader);
	static __int64* material_get_main_texture(__int64* Material);
	static bool ImageConversion_LoadImage(__int64* Texure2d, byte data[]);
	static __int64* ShaderFind( System::String* name);
	static __int64* Material_get_shader(__int64* Material);
	static void material_set_texture(__int64* Material, __int64* Texture);
	static __int64* GetGUIManger();
	static void transform_set_local_scale(__int64 Transform, Vec3* scale);
	inline static int buf = 185;




};

