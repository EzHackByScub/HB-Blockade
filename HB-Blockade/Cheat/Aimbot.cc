#include "Aimbot.hh"
#include "../memory/Engine.hh"

bool Aimbot::Physics_Raycast_hk(Ray a1, RaycastHit* hitinfo, float distance, int a4)
{
	if ( 1 > 9)
	{
	outhk:
		return oRaycast(a1, hitinfo, 999,a4);
	}
	Camera* camrt = Engine::GetCameraMain();
	if (camrt == nullptr)
		goto outhk;

	RemotePlayersController* PlController = Engine::GetRemotePlayersController();
	if (!PlController) 	goto outhk;

	auto plArray = PlController->RemotePlayersList;
	if (!plArray) 	goto outhk;

	auto BotsGO = PlController->BotsGmObj;
	if (!BotsGO) goto outhk;

	auto spawnmanno = PlController->SkinManager;
	if (!spawnmanno) goto outhk;

	auto localIndex = spawnmanno->MyIndex;
	if (localIndex > plArray->Count || localIndex < 0) goto outhk;
	auto localplayer = plArray->Item[localIndex];
	if (!localplayer) goto outhk;
	for (size_t i = 0; i < plArray->Count; i++)
	{
		auto player = plArray->Item[i];
		if (!player) continue;
		if (player->Dead) continue;
		if (localplayer->Team == player->Team) continue;

		Vec3 scrPos;
		Vec3 entitypos = Engine::GameObject_GetPosition(BotsGO->Gameobject[i]);
		if (entitypos.y == -1000) continue;
		Vec3 entitybody = { entitypos.x,entitypos.y + 1.5f,entitypos.z };
		if (Engine::Worldtoscreen(camrt, entitybody, &scrPos))
		{
			float x = scrPos.x - (float)Global_vars::ScreenW/ 2;
			float y = scrPos.y - (float)Global_vars::ScreenH/ 2;
			float crosshair_dist = sqrtf((x * x) + (y * y));
				if (crosshair_dist < Aimbot::fov) // FOV)
				{
					RaycastHit hit;
					//auto fireRay= (Ray*)a1;
					if (Engine::LineCast(a1.StartPosition, entitybody, &hit))
					{
						float cmpPosx = hit.m_Point.x - entitybody.x;
						float cmpPosy = hit.m_Point.y - entitybody.y;
						float cmpPoz = hit.m_Point.z - entitybody.z;
						if (cmpPosx > -1 && cmpPosx < 1 && cmpPosy > -1 && cmpPosy < 1 && cmpPoz > -1 && cmpPoz < 1) // to do get tag from hit and compare it 
						{
							return Engine::LineCast(a1.StartPosition, entitybody, hitinfo);
					
						}
						else
						{
							goto outhk;
						}
					}
					//TODO
					// vec3 startpos = a1 (ray).Position
	//	Engine::LineCast(startpos,) 
	//  if hit near ->  return 
	// 
	// 
	// 
	// 
	// 
		        //	return Engine::oScreenToRayadr(a1, a2, (unsigned __int64*)&scrPos);
		        }
		}
	}
	
	goto outhk;
}


//__int64 Aimbot::SpoofTest(__int64 a1, __int64 a2, unsigned __int64* a3)
//{
//	if ( 1 > 9)
//	{
//	outhk:
//		return Aimbot::oScreenToRayadr(a1, a2, a3);
//	}
//	Camera* camrt = Engine::GetCameraMain();
//	if (camrt == nullptr)
//		goto outhk;
//
//	RemotePlayersController* PlController = Engine::GetRemotePlayersController();
//	if (!PlController) 	goto outhk;
//
//	auto plArray = PlController->RemotePlayersList;
//	if (!plArray) 	goto outhk;
//
//	auto BotsGO = PlController->BotsGmObj;
//	if (!BotsGO) goto outhk;
//
//	auto spawnmanno = PlController->SkinManager;
//	if (!spawnmanno) goto outhk;
//
//	auto localIndex = spawnmanno->MyIndex;
//	if (localIndex > plArray->Count || localIndex < 0) goto outhk;
//	auto localplayer = plArray->Item[localIndex];
//	if (!localplayer) goto outhk;
//	for (size_t i = 0; i < plArray->Count; i++)
//	{
//		auto player = plArray->Item[i];
//		if (!player) continue;
//		if (player->Dead) continue;
//		if (localplayer->Team == player->Team) continue;
//
//		Vec3 scrPos;
//		Vec3 entitypos = Engine::GameObject_GetPosition(BotsGO->Gameobject[i]);
//		if (entitypos.y == -1000) continue;
//
//
//		if (Engine::Worldtoscreen(camrt, { entitypos.x,entitypos.y + 1.5f,entitypos.z }, &scrPos))
//		{
//			float x = scrPos.x - (float)Global_vars::ScreenW/ 2;
//			float y = scrPos.y - (float)Global_vars::ScreenH/ 2;
//			float crosshair_dist = sqrtf((x * x) + (y * y));
//				if (crosshair_dist < Aimbot::fov) // FOV)
//				{
//		         	return Aimbot::oScreenToRayadr(a1, a2, (unsigned __int64*)&scrPos);
//		        }
//		}
//	}
//	
//	return Aimbot::oScreenToRayadr(a1, a2, a3);
//}