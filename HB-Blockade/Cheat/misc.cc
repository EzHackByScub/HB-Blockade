#include "misc.hh"
#include "../memory/Engine.hh"
#include "Wallhack.hh"
#include <string>
#include <iostream>
#include <comdef.h> 
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


}void misc::hk_weapon_raycast(__int64 WeaponSystem, unsigned int wid, float* dist, unsigned int blockdist, __int64 WS) 
{
	//	static void hk_weapon_raycast(__int64 WeaponSystem, unsigned int wid, float* dist, unsigned int blockdist, __int64 WS);
	if (misc::auto_reload)
	{
	
		if (WeaponSystem)
		{

		int mwid = *(int*)(WeaponSystem + 0x94); // mwid
		if (mwid != wid)
		{
			Engine::send_prereload(wid);
			Engine::send_reload(wid);
		int pwid = *(int*)(WeaponSystem + 0x98);
		int swid = *(int*)(WeaponSystem + 0x9c);

		int currentwid = *(int*)(WeaponSystem + 0x120);
		if (pwid == wid)
		{
			if (*(int*)(WeaponSystem + 0xC8) >0)
			{
			*(int*)(WeaponSystem + 0xC0) += 1; // clip
			*(int*)(WeaponSystem + 0xC8) -= 1; //backpack	
			}
		}
		else if (swid == wid)
		{
			if (*(int*)(WeaponSystem + 0xD4) > 0)
			{
				*(int*)(WeaponSystem + 0xCC) += 1;
				*(int*)(WeaponSystem + 0xD4) -= 1;
			}
		}


		}
		}
	//	const auto sendreload = reinterpret_cast<void(__fastcall*)(__int64* WS, int wid, float)>(Addr::OnWeaponReloadend);

	}

	return misc::o_weapon_raycast(WeaponSystem, wid, dist, blockdist, WS);
}