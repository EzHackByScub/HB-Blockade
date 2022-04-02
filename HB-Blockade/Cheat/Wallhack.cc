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


	for (size_t i = 0; i < plArray->Count; i++)
	{
	auto player = plArray->Item[i];
	if (!player)
		continue;

		Vec3 scrPos;
		// 
		if (Engine::Worldtoscreen(camrt, player->position,&scrPos))
		{
			ImGui::GetBackgroundDrawList()->AddText({ scrPos.x ,scrPos.y }, ImColor{ 255,100,100,255 }, "EZY");
		}

	}

}