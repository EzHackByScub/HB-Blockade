#pragma once
typedef void(__fastcall* client_send_attack)(__int64 client, char a2, unsigned int a3, unsigned int a4, char a5, char hitboxid, int alter_damage, int ax, int  ay, int az, int vx, int vy, int vz, int x1, int y1, int z1, int x2, int y2  , int z2);
// vp_FPWeaponReloader::GUIDrawReload
typedef void(__fastcall* GUIDrawReload)(__int64 a1);
// vp_FPWeaponReloader::GUIDrawReload
typedef void(__fastcall* Weapon_raycast)(__int64 WeaponSystem, unsigned int wid, float* dist, unsigned int blockdist, __int64 WS);

//   public void newweapon_raycast(System.Int32 wid, System.Single dist, System.Int32 blockdist, WeaponSystem WS)
class misc
{
public:
	static inline  bool force_headshot = true;
	static inline  bool active_spam = false;

	static inline  bool fast_reload = true;
	static inline  bool auto_reload = true;

	static void Promote();
	static inline client_send_attack o_sendattack;
	static inline GUIDrawReload o_reload;
	static inline Weapon_raycast o_weapon_raycast;

	static void hk_sendattack(__int64 client, char a2, unsigned int a3, unsigned int a4, char a5, char hitboxid, int alter_damage, int ax, int  ay, int az, int vx, int vy, int vz, int x1, int y1, int z1, int x2, int y2, int z2);
	static void hk_reload( __int64 a1);
	static void hk_weapon_raycast(__int64 WeaponSystem, unsigned int wid, float* dist, unsigned int blockdist, __int64 WS);
};

