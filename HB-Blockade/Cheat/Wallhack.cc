#include "Wallhack.hh"
#include "../memory/Engine.hh"
#include "../imgui/imgui.h"

void Wallhack::Draw()
{
	if (!Wallhack::enable)
		return;

	Camera* camrt = Engine::GetCameraMain();
	if (camrt == nullptr)
		return;

	RemotePlayersController* PlController = Engine::GetRemotePlayersController();
	if (!PlController) return;
	auto plArray = PlController->RemotePlayersList;
	if (!plArray) return;

	auto BotsGO= PlController->BotsGmObj;
	if (!BotsGO) return;

	auto spawnmanno = PlController->SkinManager;
	if (!spawnmanno) return;


	auto localIndex = spawnmanno->MyIndex;
	if (localIndex > plArray->Count || localIndex  < 0) return;
	auto localplayer = plArray->Item[localIndex];
	if (!localplayer) return;
	for (size_t i = 0; i < plArray->Count; i++)
	{
	auto player = plArray->Item[i];
	if (!player)
		continue;
	if (player->Dead)
		continue;
	if (localplayer->Team == player->Team)
		continue;

		Vec3 scrPos;
		Vec3* entitypos = Engine::GameObject_GetPosition(BotsGO->Gameobject[i]);
		if (Wallhack::testoverload)
		*entitypos = player->position;

		if (entitypos->y == -1000) continue;

		if (Engine::Worldtoscreen(camrt, { entitypos->x,1.65f + entitypos->y ,entitypos->z }, &scrPos))
		{
			ImGui::GetBackgroundDrawList()->AddText({ scrPos.x ,scrPos.y }, ImColor{ 255,100,100,255 }, "EZY");
		}

	}

}