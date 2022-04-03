#include "Wallhack.hh"
#include "../memory/Engine.hh"
#include "../imgui/imgui.h"

void Wallhack::Draw()
{

	Camera* camrt = Engine::GetCameraMain();
	if (camrt == nullptr)
		return;
	Vec3 ScreenPos;
	RemotePlayersController* PlController = Engine::GetRemotePlayersController();
	if (!PlController) return;
	auto plArray = PlController->RemotePlayersList;
	if (!plArray) return;
	auto spawnmanno = PlController->SkinManager;
	if (!spawnmanno) return;


	auto localIndex = spawnmanno->MyIndex;
	if (localIndex > plArray->Count || localIndex  < 0)
		return;
	auto localplayer = plArray->Item[localIndex];
	if (!localplayer)
		return;
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
		// 

		if (Engine::Worldtoscreen(camrt, { player->oldpos.x,player->oldpos.y + 1.5f,player->oldpos.z }, &scrPos))
		{
			ImGui::GetBackgroundDrawList()->AddText({ scrPos.x ,scrPos.y }, ImColor{ 255,100,100,255 }, "EZY");
		}

	}

}