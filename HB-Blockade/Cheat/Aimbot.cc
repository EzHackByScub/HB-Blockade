#include "Aimbot.hh"
#include "../memory/Engine.hh"
#include <iostream>
#include "misc.hh"
bool checknofovda = 0;
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

		if (!player->Active || player->Dead) continue;
		if (!player->botPoser)
			continue;
		if (player->botPoser->isProtected)
			continue;
		if (localplayer->Team == player->Team) continue;

		Vec3 scrPos;
		Vec3* entitypos = Engine::GameObject_GetPosition(BotsGO->Gameobject[i]);

		if (entitypos->y == -1000) continue;
		Vec3 entitybody = { entitypos->x, 1.65f * misc::bigscale + entitypos->y ,entitypos->z };

		auto playeranim = player->botPoser->anim;
		if (!playeranim) continue;
		auto playeraniminternal = *(__int64*)(playeranim + 0x10);
		if (!playeraniminternal) continue;

		if (!misc::nofov)
		{
			if (Engine::WorldtoscreenTestWh(camrt, &scrPos, entitybody))
			{
				float x = scrPos.x - (float)Global_vars::ScreenW / 2;
				float y = scrPos.y - (float)Global_vars::ScreenH / 2;
				float crosshair_dist = sqrtf((x * x) + (y * y));
				if (crosshair_dist < Aimbot::fov) // FOV)
				{
					checknofovda = 1;
				}
				else
				{
					checknofovda = 0;
				}
			}
		}

		if (!misc::noFov)
			if (!checknofovda) continue;
				RaycastHit hit;

				if (Engine::LineCast(a1.StartPosition, entitybody, &hit))
				{
					for (int d = 0; d < 17; d++)
					{
						if (!playeraniminternal) break;
						auto bonetransf = Engine::GetBoneTransforminternal(playeraniminternal, d);
						if (!bonetransf)continue;
						auto indexs = *(int*)(bonetransf + 0x8);
						if (hit.m_Collider + 2 == indexs)
						{
							return Engine::LineCast(a1.StartPosition, entitybody, hitinfo);
						}
					}			
				}
				 entitybody = { entitypos->x, 1.65f + entitypos->y ,entitypos->z };
				 if (Engine::LineCast(a1.StartPosition, entitybody, &hit))
				 {
					 for (int d = 0; d < 17; d++)
					 {
						 if (!playeraniminternal) break;
						 auto bonetransf = Engine::GetBoneTransforminternal(playeraniminternal, d);
						 if (!bonetransf)continue;
						 auto indexs = *(int*)(bonetransf + 0x8);
						 if (hit.m_Collider + 2 == indexs)
						 {
							 return Engine::LineCast(a1.StartPosition, entitybody, hitinfo);
						 }
					 }
				 }

				entitybody = { entitypos->x, 1.f  * misc::bigscale + entitypos->y ,entitypos->z };
				if (Engine::LineCast(a1.StartPosition, entitybody, &hit))
				{
					for (int d = 0; d < 17; d++)
					{
						if (!playeraniminternal) break;
						auto bonetransf = Engine::GetBoneTransforminternal(playeraniminternal, d);
						if (!bonetransf)continue;
						auto indexs = *(int*)(bonetransf + 0x8);
						if (hit.m_Collider + 2 == indexs)
						{
							return Engine::LineCast(a1.StartPosition, entitybody, hitinfo);
						}
					}
				}

				entitybody = { entitypos->x,0.5f * misc::bigscale + entitypos->y  ,entitypos->z };
				if (Engine::LineCast(a1.StartPosition, entitybody, &hit))
				{
					for (int d = 0; d < 17; d++)
					{
						if (!playeraniminternal) break;
						auto bonetransf = Engine::GetBoneTransforminternal(playeraniminternal, d);
						if (!bonetransf)continue;
						auto indexs = *(int*)(bonetransf + 0x8);
						if (hit.m_Collider + 2 == indexs)
						{
							return Engine::LineCast(a1.StartPosition, entitybody, hitinfo);
						}
					}
				}

				entitybody = { entitypos->x, 1.f + entitypos->y ,entitypos->z };
				if (Engine::LineCast(a1.StartPosition, entitybody, &hit))
				{
					for (int d = 0; d < 17; d++)
					{
						if (!playeraniminternal) break;
						auto bonetransf = Engine::GetBoneTransforminternal(playeraniminternal, d);
						if (!bonetransf)continue;
						auto indexs = *(int*)(bonetransf + 0x8);
						if (hit.m_Collider + 2 == indexs)
						{
							return Engine::LineCast(a1.StartPosition, entitybody, hitinfo);
						}
					}
				}

				entitybody = { entitypos->x,0.5f + entitypos->y  ,entitypos->z };
				if (Engine::LineCast(a1.StartPosition, entitybody, &hit))
				{
					for (int d = 0; d < 17; d++)
					{
						if (!playeraniminternal) break;
						auto bonetransf = Engine::GetBoneTransforminternal(playeraniminternal, d);
						if (!bonetransf)continue;
						auto indexs = *(int*)(bonetransf + 0x8);
						if (hit.m_Collider + 2 == indexs)
						{
							return Engine::LineCast(a1.StartPosition, entitybody, hitinfo);
						}
					}
				}

			}
		
	goto outhk;
}




