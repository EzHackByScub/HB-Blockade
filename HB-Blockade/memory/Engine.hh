#pragma once
#include "Addr.hh"
#include "GameClasses.hh"

class Engine
{
public:
	static Camera* GetCameraMain();
	static  RemotePlayersController* GetRemotePlayersController();
	static Vec3 TransformGetPosition(__int64 transform);
	static bool Worldtoscreen(Camera* camera, Vec3 position, Vec3* wtsvec);
};

