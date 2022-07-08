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
	static bool Worldtoscreen(Camera* camera, Vec3 position, Vec3* wtsvec);
	static bool WorldtoscreenTestWh(Camera* came, Vec3* wtsvec, Vec3 position);
	static bool LineCast(Vec3 Startpos, Vec3 endpos, RaycastHit* hitinfo);
	static  void  send_exploid(__int64* client, int uid, Vec3 pos);
	inline static int buf = 185;




};

