#include "misc.hh"
#include "../memory/Engine.hh"
int timeoutcalls = 1000;
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
		timeoutcalls = 1000;
	}
		Engine::client_send_msg(L"-> hyperbone.cc <-");
}


void __fastcall misc::hk_sendattack(__int64 client, char a2, unsigned int a3, unsigned int a4, char a5, char hitboxid, int alter_damage, int ax, int  ay, int az, int vx, int vy, int vz, int x1, int y1, int z1, int x2, int y2, int z2) {
	if (misc::force_headshot)
		a5 = 1;
	return misc::o_sendattack(client, a2, a3, a4, a5, hitboxid,  alter_damage,  ax,   ay,  az,  vx,  vy,  vz,  x1,  y1,  z1,  x2,  y2,  z2);
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
		Engine::send_prereload(wid);
		Engine::send_reload(wid);
	}

	return misc::o_weapon_raycast(WeaponSystem, wid, dist, blockdist, WS);
}