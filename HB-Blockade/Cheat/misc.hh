#pragma once
#include "../memory/GameClasses.hh"
typedef void(__fastcall* client_send_attack)(__int64 client, char a2, unsigned int a3, unsigned int a4, char a5, char hitboxid, int alter_damage, int ax, int  ay, int az, int vx, int vy, int vz, int x1, int y1, int z1, int x2, int y2  , int z2);
// vp_FPWeaponReloader::GUIDrawReload
typedef void(__fastcall* GUIDrawReload)(__int64 a1);
// vp_FPWeaponReloader::GUIDrawReload
typedef void(__fastcall* Addmessage)(__int64 a1, __int64 a2, __int64 a3, int a4, int a5);
typedef void(__fastcall* ChatMessage)(__int64* Chat, int index, int team, System::String* msg, int teamchat);
typedef void(__fastcall* sendCreateEvent)(__int64* client, Vec3 pos, Vec3 rot, Vec3 force, Vec3 torque, __int8 enttypeid);
typedef void(__fastcall* senddetonateent)(__int64* client, int uid, Vec3 pos);
typedef bool(__fastcall* ABTest_IsActive)();
typedef void(__fastcall* GameController_Update)(__int64* a1);
typedef void(__fastcall* Fire)(__int64* vp_FPWeaponShooter, __int64 a2, __int64* a3);
typedef void(__fastcall* FireSpecEffects)(__int64* vp_FPWeaponShooter);
typedef void(__fastcall* send_currentweapon)(__int64* Client,int weaponid);
typedef __int64(__fastcall* ColiderFinder)(__int64 a1, __int64 a2);
typedef void(__fastcall* weapon_raycast)(WeaponSystem* weaponsys, int wid, float dist, int blockdist, WeaponSystem* WS);

//   public void newweapon_raycast(System.Int32 wid, System.Single dist, System.Int32 blockdist, WeaponSystem WS)
class misc
{
public:
	static inline  bool force_headshot = true;
	static inline  bool killtochat = false;
	static inline  bool GranadeTeleport = false;
	static inline  bool active_spam = false;
	static inline  bool fire = false;
	static inline  bool autoshoot = false;
	static inline  bool noFov = false;

	static inline  bool fast_reload = true;
	static inline  bool auto_reload = true;
	static inline bool MagicAimbot = true;
	static inline bool Aimbot = true;
	static inline bool nofov = false;
	static inline bool bufer = false;
	static inline  bool rainbowesp = false;
	static inline  bool weapongay = false;
	static inline int uidbuf = 0;
	static inline int	rainbowdelay = 0;
	static inline float	bigscale = 1;

	static void Promote();
	static inline client_send_attack o_sendattack;
	static inline GUIDrawReload o_reload;
	static inline Addmessage o_Addmessage;
	static inline ChatMessage o_ChatMessage;
	static inline sendCreateEvent o_send_createevent;
	static inline senddetonateent o_send_detenoteevent;
	static inline ABTest_IsActive o_ABTest_IsActive;
	static inline Fire o_Fire;
	static inline FireSpecEffects o_FireSpecEffects;
	static inline GameController_Update o_GameController_Update;
	static inline send_currentweapon o_send_currentweapon;
	static inline ColiderFinder o_ColiderFinder;
	static inline weapon_raycast o_weapon_raycast;

	static void hk_sendattack(__int64 client, char a2, unsigned int a3, unsigned int a4, char a5, char hitboxid, int alter_damage, int ax, int  ay, int az, int vx, int vy, int vz, int x1, int y1, int z1, int x2, int y2, int z2);
	static void hk_reload( __int64 a1);
	static void hk_adddeathmessage(__int64 a1, __int64 a2, __int64 a3, int a4, int a5);
	static void hk_ChatMessage(__int64* Chat, int index, int team, System::String* msg, int teamchat);
	static void hk_detonatyeev(__int64* client, int uid, Vec3 pos);
	static void  hk_fire(__int64* vp_FPWeaponShooter, __int64 a2, __int64* a3);
	static __int64  hk_ColiderFinder(__int64 a1, __int64 a2);
	static void  hk_weapon_raycast(WeaponSystem* weaponsys, int wid, float dist, int blockdist, WeaponSystem* WS);
	static bool  hk_ABTest_IsActive();
	static void hk_send_currentweapon(__int64* Client, int weaponid);
};

