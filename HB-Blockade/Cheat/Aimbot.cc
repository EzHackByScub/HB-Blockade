#include "Aimbot.hh"
#include "../memory/Engine.hh"
__int64 Aimbot::SpoofTest(__int64 a1, __int64 a2, unsigned __int64* a3)
{
	if ( 1 > 9)
	{
	outhk:
		return Aimbot::oScreenToRayadr(a1, a2, a3);
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


		if (Engine::Worldtoscreen(camrt, { entitypos.x,entitypos.y + 1.5f,entitypos.z }, &scrPos))
		{
			float x = scrPos.x - (float)Global_vars::ScreenW/ 2;
			float y = scrPos.y - (float)Global_vars::ScreenH/ 2;
			float crosshair_dist = sqrtf((x * x) + (y * y));
				if (crosshair_dist < Aimbot::fov) // FOV)
				{
		         	return Aimbot::oScreenToRayadr(a1, a2, (unsigned __int64*)&scrPos);
		        }
		}
	}
	
	return Aimbot::oScreenToRayadr(a1, a2, a3);
}