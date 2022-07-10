#pragma once
#include "Vectors.hh"
 enum HumanBodyBones : __int8
 {
	 Bip001_Pelvis,
	 Bip001_L_Thigh,
	 Bip001_R_Thigh,
	 Bip001_L_Calf,
	 Bip001_R_Calf,
	 Bip001_L_Foot,
	 Bip001_R_Foot,
	 Bip001_Spine,
	 Bip001_Neck,
	 Bip001_Head,
	 Bip001_L_Clavicle,
	 Bip001_R_Clavicle,
	 Bip001_L_UpperArm,
	 Bip001_R_UpperArm,
	 Bip001_L_Forearm,
	 Bip001_R_Forearm,
	 Bip001_L_Hand,
	 Bip001_R_Hand,
};
 class Assemblies_Array
 {
 public:
	 char pad_0568[0x20]; //740
	 __int64* Assembly[72];
 };
class GameObject
{
public:
	char pad_0568[0x60]; //740
	char* name;
};
class pCamera {
public:
	char pad_0568[0x2E4]; //740
	Matrix4x4 matrix; //740
};
class Camera
{
	
public:
	char pad10[0x10];
	pCamera* m_cashedptr;
};
struct  Ray {
	Vec3 StartPosition;
	Vec3 Rotation;
};

struct  RaycastHit {
	 Vec3 m_Point;
	 Vec3 m_Normal;
	int m_FaceID;
	float m_Distance;
	 Vec2 m_UV;
	 int m_Collider;
};
namespace System
{
	class String
	{
	public:
		char pad10[0x10];
		int Length;
		const wchar_t Value[256];
	};

}
class vp_FPCamera
{
public:
	char pad_0000[0x144]; //0x0000
	Vec2 rotation;
};
class WeaponSystem
{
public:
	char pad_0000[0x28]; //0x0000
	vp_FPCamera* camera;
};
class BotEquipment {
public:
	char pad_0000[8]; //0x0000
	__int8 myshitforvischeck;
	char pad_0010[104]; //0x0010
	__int64 GameObject_m_top; //0x78
	__int64 GameObject_m_face;
};
class AnimatorList
{
public:
	char pad_0000[0x18]; //0x0000
	int Count;
	__int64 Animator[];
};
class BotPoser {
public:
	char pad_0000[0x68]; //0x0000
	AnimatorList* AnimatorList; //0x0068
	char pad_0070[8]; //0x0070
	__int64 anim; //0x0078
	char pad_0080[24]; //0x0080
	bool isProtected; //0x98
};
class RemotePlayerData
{
public:
	char pad_0000[8]; //0x0000
	bool isVisible;
	char pad_0001[7]; //0x0000
	int Item; //0x0010
	char pad_0014[4]; //0x0014
	Vec3 position; //0x0018
	Vec3 rotation; //0x0024
	bool Dead; //0x0030
	char pad_0031[3]; //0x0031
	int Helmet; //0x0034
	int HelmetHealth; //0x0038
	int Skin; //0x003C
	int Ha1; //0x0040
	int Ha2; //0x0044
	int Ha3; //0x0048
	int Znak; //0x004C
	int CountryID; //0x0050
	int WeaponID; //0x0054
	Vec3 oldpos; //0x0058
	char pad_0064[4]; //0x0064
	BotEquipment* botEquipment; //0x0068
	int Stats_Kills; //0x0070
	int Stats_Deads; //0x0074
	void* uidStirng; //0x0078
	int pwID; //0x0080
	int swID; //0x0084
	int mwID; //0x0088
	Vec3 targetPosition; //0x008C
	int InVehicle; //0x0098
	int InVehiclePos; //0x009C
	System::String* ClanName; //0x00A0
	int ClanId; //0x00A8
	int AnimState; //0x00AC
	int Team; //0x00B0
	char pad_00B4[4]; //0x00B4
	System::String* Name; //0x00B8
	int Active; //0x00C0
	int State; //0x00C4
	float flash_time; //0x00C8
	char pad_00CC[4]; //0x00CC
	void* mySound; //0x00D0
	void* goHelmets; //0x00D8
	void* goSkinMask; //0x00E0
	void* goMasks; //0x00E8
	void* goHats; //0x00F0
	void* goAttaches; //0x00F8
	int isZombie; //0x0100
	int blockFlag; //0x0104
	int currBlockType; //0x0108
	char pad_010C[4]; //0x010C
	void* _block; //0x0110
	void* _blockUp; //0x0118
	BotPoser* botPoser; //0x0120
	int TeamColor; //0x0128
	char pad_012C[84]; //0x012C
}; //Size: 0x0180
class RemotePlayersDataArray
{
public:
	char pad_0000[0x18]; //0x0000
	int Count;
	RemotePlayerData* Item[];
};

class SpawnManager
{
public:
	char pad_0000[76]; //0x0000
	int MyIndex; //0x004C
}; //Size: 0x0050

class BotsGmObjArray
{
public:
	char pad_0000[0x18]; //0x0000
	int Count;
	__int64 Gameobject[];
};

class RemotePlayersController
{
public:
	char pad_0000[24]; //0x0000
	Vec3 myLookPoint; //0x0018
	char pad_0024[4]; //0x0024
	BotsGmObjArray* BotsGmObj; //0x0028
	void* pgoPlayerCreated; //0x0030
	void* Gui; //0x0038
	void* teamblock_BlockArray; //0x0040
	int PlayersLoaded; //0x0048
	char pad_004C[4]; //0x004C
	void* csws; //0x0050
	SpawnManager* SkinManager; //0x0058
	void* pgoPlayer; //0x0060
	void* csrm; //0x0068
	void* pgoLocalPlayer; //0x0070
	void* csig; //0x0078
	uintptr_t* goCurrentPlayer; //0x0080
	void* mg; //0x0088
	class RemotePlayersDataArray* RemotePlayersList; //0x0090
	float zmupdate; //0x0098
	float lastupdate; //0x009C
}; //Size: 0x00A0
