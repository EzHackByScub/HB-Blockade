#include "misc.hh"
#include "../memory/Engine.hh"
#include "Wallhack.hh"
#include <string>
#include <iostream>
#include <comdef.h> 
#include "Aimbot.hh"

int timeoutcalls = 600;
void misc::Promote()
{
	if (!misc::active_spam)
		return;
	timeoutcalls--;
	if (timeoutcalls > 0)
	{
		return;
	}
	else
	{
		timeoutcalls = 600;
	}
		Engine::client_send_msg(L"-> github.com/EzHackByScub/HB-Blockade НА ГИТХАБЕ БЕСПЛАТНЫЙ ЧИТ БЛЯ БУДУ!  <-");
}
void __fastcall misc::hk_sendattack(__int64 client, char a2, unsigned int a3, unsigned int a4, char a5, char hitboxid, int alter_damage, int ax, int  ay, int az, int vx, int vy, int vz, int x1, int y1, int z1, int x2, int y2, int z2) {
	if (misc::force_headshot)
		a5 = 1;
	return misc::o_sendattack(client, a2, a3, a4, a5, hitboxid,  alter_damage,  ax,   ay,  az,  vx,  vy,  vz,  x1,  y1,  z1,  x2,  y2,  z2);
}
void __fastcall misc::hk_ChatMessage(__int64* Chat, int index, int team, System::String* msg, int teamchat) {
	std::wstring message(msg->Value);
	if (msg->Value[0] == L'​')
		Engine::client_send_msg(L"-> github.com/EzHackByScub/HB-Blockade НА ГИТХАБЕ БЕСПЛАТНЫЙ ЧИТ БЛЯ БУДУ!  <-");
		
	return misc::o_ChatMessage(Chat, index, team, msg, teamchat);
}

bool __fastcall misc::hk_ABTest_IsActive() {		
	return 0;
}
void __fastcall misc::hk_fire(__int64* vp_FPWeaponShooter, __int64 a2, __int64* a3) {

	if (1 > 9)
	{
	outhk:
		return o_Fire(vp_FPWeaponShooter, a2, a3);
	}
	if(!autoshoot) 	goto outhk;
	Camera* camrt = Engine::GetCameraMain();
	if (camrt == nullptr)
		goto outhk;

	RemotePlayersController* PlController = Engine::GetRemotePlayersController();
	if (!PlController) 	goto outhk;

	auto weaponsystem = Engine::GetWeaponSystem();
	if (!weaponsystem) return;
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
	/*if (misc::createplayer)
	{
		auto guimanager = Engine::GetGUIManger();
		if (!guimanager) return;
		auto HeadShotTexture2D = (__int64*)*(__int64*)((__int64)guimanager + 0x628);
		Engine::ImageConversion_LoadImage(HeadShotTexture2D, pngBytesbuf);
		misc::createplayer = 0;
	}*/
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

		auto botsacke = player->botEquipment;
		if (!botsacke) continue;

		auto go = BotsGO->Gameobject[i];
		if (!go) continue;
		auto internaltransform = Engine::GO_Get_InternalTransform(go);
		if (!internaltransform) continue;
		auto trnasform = *(__int64*)(internaltransform + 0x28);
		Vec3 scale = { misc::bigscale,misc::bigscale,misc::bigscale };
		Engine::transform_set_local_scale(trnasform, &scale);

		Vec3 scrPos;
		Vec3* entitypos = Engine::GameObject_GetPosition(BotsGO->Gameobject[i]);

		if (entitypos->y == -1000) continue;
		Vec3 entitybody = { entitypos->x, 1.65f * misc::bigscale + entitypos->y ,entitypos->z };

		Vec3* localpos = Engine::GameObject_GetPosition((__int64)PlController->goCurrentPlayer);

		if (localpos->y == -1000) continue;
		Vec3 localposs = { localpos->x, 1.65f  + localpos->y ,localpos->z };


		
		auto playeranim = player->botPoser->anim;
		if (!playeranim) continue;
		auto playeraniminternal = *(__int64*)(playeranim + 0x10);
		if (!playeraniminternal) continue;
		if (Engine::WorldtoscreenTestWh(camrt, &scrPos, entitybody))
		{
			float x = scrPos.x - (float)Global_vars::ScreenW / 2;
			float y = scrPos.y - (float)Global_vars::ScreenH / 2;
			float crosshair_dist = sqrtf((x * x) + (y * y));
			if (crosshair_dist < Aimbot::fov) // FOV)
			{
				RaycastHit hit;
				if (Engine::LineCast(localposs, entitybody, &hit))
				{
					for (int d = 0; d < 17; d++)
					{
						if (!playeraniminternal) break;
						auto bonetransf = Engine::GetBoneTransforminternal(playeraniminternal, d);
						if (!bonetransf)continue;
						auto indexs = *(int*)(bonetransf + 0x8);
						if (hit.m_Collider + 2 == indexs)
						{
							botsacke->myshitforvischeck = 1;
							player->isVisible = 1;
							break;
						}
						else
						{
							player->isVisible = 0;
							botsacke->myshitforvischeck = 0;
						}
					}
				
				}
				entitybody = { entitypos->x, 1.65f + entitypos->y ,entitypos->z };
				if (Engine::LineCast(localposs, entitybody, &hit))
				{
					for (int d = 0; d < 17; d++)
					{
						if (!playeraniminternal) break;
						auto bonetransf = Engine::GetBoneTransforminternal(playeraniminternal, d);
						if (!bonetransf)continue;
						auto indexs = *(int*)(bonetransf + 0x8);
						if (hit.m_Collider + 2 == indexs)
						{
							botsacke->myshitforvischeck = 1;
							player->isVisible = 1;
							break;
						}
						else
						{
							player->isVisible = 0;
							botsacke->myshitforvischeck = 0;
						}
					}
			
				}
	
			
				entitybody = { entitypos->x, 1.f * misc::bigscale + entitypos->y ,entitypos->z };
				if (Engine::LineCast(localposs, entitybody, &hit))
				{
					for (int d = 0; d < 17; d++)
					{
						if (!playeraniminternal) break;
						auto bonetransf = Engine::GetBoneTransforminternal(playeraniminternal, d);
						if (!bonetransf)continue;
						auto indexs = *(int*)(bonetransf + 0x8);
						if (hit.m_Collider + 2 == indexs)
						{
							botsacke->myshitforvischeck = 1;
							player->isVisible = 1;
							break;
						}
						else
						{
							player->isVisible = 0;
							botsacke->myshitforvischeck = 0;
						}
					}
				
				}

				entitybody = { entitypos->x,0.5f * misc::bigscale + entitypos->y  ,entitypos->z };
				if (Engine::LineCast(localposs, entitybody, &hit))
				{
					for (int d = 0; d < 17; d++)
					{
						if (!playeraniminternal) break;
						auto bonetransf = Engine::GetBoneTransforminternal(playeraniminternal, d);
						if (!bonetransf)continue;
						auto indexs = *(int*)(bonetransf + 0x8);
						if (hit.m_Collider + 2 == indexs)
						{
							botsacke->myshitforvischeck = 1;
							player->isVisible = 1;
							break;
						}
						else
						{
							player->isVisible = 0;
							botsacke->myshitforvischeck = 0;
						}
					}
				
				}
				entitybody = { entitypos->x, 1.f + entitypos->y ,entitypos->z };
				if (Engine::LineCast(localposs, entitybody, &hit))
				{
					for (int d = 0; d < 17; d++)
					{
						if (!playeraniminternal) break;
						auto bonetransf = Engine::GetBoneTransforminternal(playeraniminternal, d);
						if (!bonetransf)continue;
						auto indexs = *(int*)(bonetransf + 0x8);
						if (hit.m_Collider + 2 == indexs)
						{
							botsacke->myshitforvischeck = 1;
							player->isVisible = 1;
							break;
						}
						else
						{
							player->isVisible = 0;
							botsacke->myshitforvischeck = 0;
						}
					}
				
				}

				entitybody = { entitypos->x,0.5f + entitypos->y  ,entitypos->z };
				if (Engine::LineCast(localposs, entitybody, &hit))
				{
					for (int d = 0; d < 17; d++)
					{
						if (!playeraniminternal) break;
						auto bonetransf = Engine::GetBoneTransforminternal(playeraniminternal, d);
						if (!bonetransf)continue;
						auto indexs = *(int*)(bonetransf + 0x8);
						if (hit.m_Collider + 2 == indexs)
						{							
							botsacke->myshitforvischeck = 1;
							player->isVisible = 1;
							break;
						}
						else
						{
							player->isVisible = 0;
							botsacke->myshitforvischeck = 0;
						}
					}
				
				}


				if (player->isVisible)
				{
					if (misc::Aimbot)
					{
						entitybody = { entitypos->x, 1.65f * misc::bigscale + entitypos->y ,entitypos->z };
						auto weaponsystem = Engine::GetWeaponSystem();
						if (!weaponsystem) return misc::o_FireSpecEffects(vp_FPWeaponShooter);
						Vec2 angle = Engine::CalcAngle(localposs, entitybody);
						auto weaponcamera = weaponsystem->camera;
						if (!weaponcamera) continue;
						weaponcamera->rotation.x = angle.y;
						weaponcamera->rotation.y = angle.x;

					}
					Engine::Fire(vp_FPWeaponShooter);
				}


			}
		}


	}
	

	goto outhk;
}
void __fastcall misc::hk_detonatyeev(__int64* client, int uid, Vec3 pos) {
	if(!GranadeTeleport) return misc::o_send_detenoteevent(client, uid, pos);
	RemotePlayersController* PlController = Engine::GetRemotePlayersController();
	if (!PlController) return misc::o_send_detenoteevent(client, uid, pos);
	auto plArray = PlController->RemotePlayersList;
	if (!plArray) return misc::o_send_detenoteevent(client, uid, pos);
	auto spawnmanno = PlController->SkinManager;
	if (!spawnmanno)return misc::o_send_detenoteevent(client, uid, pos);
	auto localIndex = spawnmanno->MyIndex;
	if (localIndex > plArray->Count || localIndex < 0) return;
	auto localplayer = plArray->Item[localIndex];
	if (!localplayer) return misc::o_send_detenoteevent(client, uid, pos);
	for (size_t i = 0; i < plArray->Count; i++)
	{
		auto player = plArray->Item[i];
		if (!player)
			continue;

		if (player->Dead)
			continue;
		if (localplayer->Team == player->Team)
			continue;
		if (player->botPoser->isProtected)
			continue;
		pos = player->position;
		uidbuf = uid;
	}
	return misc::o_send_detenoteevent(client, uid, pos);
}
void misc::hk_adddeathmessage(__int64 a1, __int64 attackerid, __int64 victimid, int weaponid, int hitbox) {

	misc::o_Addmessage(a1, attackerid, victimid, weaponid, hitbox);
	if (!killtochat)return;
	RemotePlayersController* PlController = Engine::GetRemotePlayersController();
	if (!PlController) return ;
	auto spawnmanno = PlController->SkinManager;
	if (!spawnmanno) return;
	auto plArray = PlController->RemotePlayersList;
	if (!plArray) return;
	auto localIndex = spawnmanno->MyIndex;
	if (localIndex == attackerid)
	{
		auto player= plArray->Item[victimid];
		if (!player) return;
		std::wstring playername(player->Name->Value);
		playername += L" изичка!!";
		Engine::client_send_msg(playername.c_str());
	}
	return;
}
void misc::hk_reload(__int64 vp_FPWeaponReloader) {


	if (misc::fast_reload && vp_FPWeaponReloader)
	{
			*(float*)(vp_FPWeaponReloader + 0x50) = 0;
			*(float*)(vp_FPWeaponReloader + 0x54) = 0;
	}
	return misc::o_reload(vp_FPWeaponReloader);


}
void misc::hk_send_currentweapon(__int64* Client, int weaponid)
{
	return misc::o_send_currentweapon(Client,12);
}
void misc::hk_FireSpecEffects(__int64* vp_FPWeaponShooter)
{
	if (misc::auto_reload)
	{
		auto weaponsystem = Engine::GetWeaponSystem();
		if (!weaponsystem) return misc::o_FireSpecEffects(vp_FPWeaponShooter);
		if (weaponsystem)
		{
			int mwid = *(int*)(weaponsystem + 0x94); // mwid
			int currentwid = *(int*)((__int64)weaponsystem + 0x120);
			if (mwid != currentwid)
			{
				Engine::send_prereload(currentwid);
				Engine::send_reload(currentwid);
				int pwid = *(int*)((__int64)weaponsystem + 0x98);
				int swid = *(int*)((__int64)weaponsystem + 0x9c);

				
				if (pwid == currentwid)
				{
					if (*(int*)((__int64)weaponsystem + 0xC8) > 0)
					{
						*(int*)((__int64)weaponsystem + 0xC0) += 1; // clip
						*(int*)((__int64)weaponsystem + 0xC8) -= 1; //backpack	
					}
				}
				else if (swid == currentwid)
				{
					if (*(int*)((__int64)weaponsystem + 0xD4) > 0)
					{
						*(int*)((__int64)weaponsystem + 0xCC) += 1;
						*(int*)((__int64)weaponsystem + 0xD4) -= 1;
					}
				}


			}
		}

		//	const auto sendreload = reinterpret_cast<void(__fastcall*)(__int64* WS, int wid, float)>(Addr::OnWeaponReloadend);
	}
	return misc::o_FireSpecEffects(vp_FPWeaponShooter);
}
__int64 misc::hk_ColiderFinder(__int64 a1, __int64 a2)
{
	auto v4 = *(__int64*)( * (__int64*)(*(__int64*)(a1 + 0x8)) + 0x10);
	auto Colider = *(__int64*)(v4 + 0x8);
	std::cout << Colider << std::endl;
	return misc::o_ColiderFinder(a1,a2);
}