#pragma once
#include "Addr.hh"
#include "GameClasses.hh"

class Engine
{
public:
	static Camera* GetCameraMain();
	static  RemotePlayersController* GetRemotePlayersController();
	static Vec3 InternalTransform_GetPosition(__int64 transform);
	static Vec3 GameObject_GetPosition(__int64 Gameobject);
	static const char* GameObject_GetName(__int64 Gameobject);

	static __int64  GO_Get_InternalTransform(__int64 Gameobject);
	static bool Worldtoscreen(Camera* camera, Vec3 position, Vec3* wtsvec);
	static bool LineCast(Vec3 Startpos, Vec3 endpos, RaycastHit* hitinfo);

};

