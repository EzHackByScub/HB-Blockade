#include "Aimbot.hh"
#include "../memory/Engine.hh"
#include <iostream>
#include "misc.hh"
void Aimbot::DefoltAimbot()
{
	if (!misc::Aimbot) return;
	Camera* camrt = Engine::GetCameraMain();
	if (camrt == nullptr)
		return;

	RemotePlayersController* PlController = Engine::GetRemotePlayersController();
	if (!PlController) 	return;

	auto weaponsystem = Engine::GetWeaponSystem();
	if (!weaponsystem) return;

	auto plArray = PlController->RemotePlayersList;
	if (!plArray) 	return;

	auto BotsGO = PlController->BotsGmObj;
	if (!BotsGO) 	return;

	auto spawnmanno = PlController->SkinManager;
	if (!spawnmanno) 	return;

	auto localIndex = spawnmanno->MyIndex;
	if (localIndex > plArray->Count || localIndex < 0) 	return;
	auto localplayer = plArray->Item[localIndex];
	if (!localplayer)	return;
	for (size_t i = 0; i < plArray->Count; i++)
	{
		auto player = plArray->Item[i];
		if (!player) continue;

		if (!player->Active || player->Dead) continue;
		if (!player->botPoser)
			continue;
		if (player->botPoser->isProtected)
			continue;
		if (localplayer->Team == player->Team) continue;

		Vec3 scrPos;
		Vec3* entitypos = Engine::GameObject_GetPosition(BotsGO->Gameobject[i]);

		if (entitypos->y == -1000) continue;
		Vec3 entitybody = { entitypos->x, 1.65f + entitypos->y ,entitypos->z };


		Vec3* localpos = Engine::GameObject_GetPosition((__int64)PlController->goCurrentPlayer);

		if (localpos->y == -1000) continue;
		Vec3 localposs = { localpos->x, 1.65f + localpos->y ,localpos->z };

		auto botsacke = player->botEquipment;
		if (!botsacke) continue;

		if (!player->isVisible) continue;
		if (Engine::WorldtoscreenTestWh(camrt, &scrPos, entitybody))
		{
			float x = scrPos.x - (float)Global_vars::ScreenW / 2;
			float y = scrPos.y - (float)Global_vars::ScreenH / 2;
			float crosshair_dist = sqrtf((x * x) + (y * y));
			if (crosshair_dist < Aimbot::fov) // FOV)
			{
				Vec2 angle = Engine::CalcAngle(localposs,entitybody);
				auto weaponcamera = weaponsystem->camera;
				if (!weaponcamera) continue;
				weaponcamera->rotation.x = angle.y;
				weaponcamera->rotation.y = angle.x;
			}
		}
	}
}
bool Aimbot::Physics_Raycast_hk(Ray a1, RaycastHit* hitinfo, float distance, int a4)
{

	if ( 1 > 9)
	{
	outhk:
		return oRaycast(a1, hitinfo, distance,a4);
	}
	if (!misc::MagicAimbot) 	goto outhk;
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

		if (!player->Active ||  player->Dead ) continue;
		if (!player->botPoser)
			continue;
		if (player->botPoser->isProtected)
			continue;
		if (localplayer->Team == player->Team) continue;

		Vec3 scrPos;
		Vec3* entitypos = Engine::GameObject_GetPosition(BotsGO->Gameobject[i]);

		if (entitypos->y == -1000) continue;
		Vec3 entitybody = { entitypos->x, 1.65f + entitypos->y ,entitypos->z };
		if (Engine::WorldtoscreenTestWh(camrt,  &scrPos, entitybody))
		{
			float x = scrPos.x - (float)Global_vars::ScreenW/ 2;
			float y = scrPos.y - (float)Global_vars::ScreenH/ 2;
			float crosshair_dist = sqrtf((x * x) + (y * y));
				if (crosshair_dist < Aimbot::fov) // FOV)
				{
					RaycastHit hit;
					if (Engine::LineCast(a1.StartPosition, entitybody, &hit))
					{
						//if (hit.m_Distance > Aimbot::weapondistance) continue;
						float cmpPosx = hit.m_Point.x - entitybody.x;
						float cmpPosy = hit.m_Point.y - entitybody.y;
						float cmpPoz = hit.m_Point.z - entitybody.z;
						if (cmpPosx > -0.5f && cmpPosx < 0.5f && cmpPosy > -0.5f && cmpPosy < 0.5f && cmpPoz > -0.5f && cmpPoz < 0.5f) // to do get tag from hit and compare it 
						{
								return Engine::LineCast(a1.StartPosition, entitybody, hitinfo);
					    }
	               	}

					entitybody = { entitypos->x, 1.f + entitypos->y ,entitypos->z };
					if (Engine::LineCast(a1.StartPosition, entitybody, &hit))
					{
						//if (hit.m_Distance > Aimbot::weapondistance) continue;
						float cmpPosx = hit.m_Point.x - entitybody.x;
						float cmpPosy = hit.m_Point.y - entitybody.y;
						float cmpPoz = hit.m_Point.z - entitybody.z;
						if (cmpPosx > -0.5f && cmpPosx < 0.5f && cmpPosy > -0.5f && cmpPosy < 0.5f && cmpPoz > -0.5f && cmpPoz < 0.5f) // to do get tag from hit and compare it 
						{
							return Engine::LineCast(a1.StartPosition, entitybody, hitinfo);
						}
					}

					entitybody = { entitypos->x,0.5f + entitypos->y  ,entitypos->z };
					if (Engine::LineCast(a1.StartPosition, entitybody, &hit))
					{
						//if (hit.m_Distance > Aimbot::weapondistance) continue;
						float cmpPosx = hit.m_Point.x - entitybody.x;
						float cmpPosy = hit.m_Point.y - entitybody.y;
						//48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC 40 80 3D ? ? ? ? ? 41 8B F1 41 8B E8 0F B6 DA 
						float cmpPoz = hit.m_Point.z - entitybody.z;
						if (cmpPosx > -0.5f && cmpPosx < 0.5f && cmpPosy > -0.5f && cmpPosy < 0.5f && cmpPoz > -0.5f && cmpPoz < 0.5f) // to do get tag from hit and compare it 
						{
							return Engine::LineCast(a1.StartPosition, entitybody, hitinfo);
						}
					}

             	}
       }
	}

	goto outhk;
}




