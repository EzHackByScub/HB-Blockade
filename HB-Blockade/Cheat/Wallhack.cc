#include "Wallhack.hh"
#include "../memory/Engine.hh"
#include "../imgui/imgui.h"
#include "misc.hh"
#include <string>
#include <iostream>

typedef struct
{
	int R;
	int G;
	int B;
	int A;
}RGBA;
RGBA espWave = { 255, 0, 0, 255 };
void animate() {
	static int delay = 0;
	if (delay > 0)
		delay -= 1;
	if(delay == 0) {
		if (espWave.B != 255 && espWave.G == 0) {
			espWave.B++;
		}

		if (espWave.B == 255 && espWave.R != 0) {
			espWave.R--;
		}

		if (espWave.B == 255 && espWave.G != 255 && espWave.R == 0) {
			espWave.G++;
		}

		if (espWave.G == 255 && espWave.B != 0) {
			espWave.B--;
		}

		if (espWave.B == 0 && espWave.R != 255) {
			espWave.R++;
		}

		if (espWave.R == 255 && espWave.G != 0) {
			espWave.G--;
		}
		delay = Wallhack::wave_speed;
	}
}

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
		__int64* client = Engine::GetClient();
		if (!client) return;

		Vec3* entitypos = Engine::GameObject_GetPosition(BotsGO->Gameobject[i]);
		if (Wallhack::testoverload)
			*entitypos = player->position;
		Vec3 entytyfix = { entitypos->x,1.65f + entitypos->y ,entitypos->z };
		Vec3 scrposeye;
		Vec3 scrposfood;

		if (entitypos->y == -1000) continue;

		if (!Engine::WorldtoscreenTestWh(camrt, &scrposeye, entytyfix)) continue;
		if (!Engine::WorldtoscreenTestWh(camrt, &scrposfood, *entitypos)) continue;

		float width = (scrposeye.y - scrposfood.y) * 0.3f;

		if (width < 0)
			width = -width;

		auto botposer = player->botPoser;
		if (!botposer) return;
		if (!botposer->isProtected)
		{
			if (misc::rainbowesp)
			{
				animate();
				RGBA ESPColor = { espWave.R ,espWave.G, espWave.B, espWave.A };
				ImGui::GetOverlayDrawList()->AddRect({ scrposeye.x - width,scrposeye.y }, { scrposfood.x + width,scrposfood.y }, ImColor{ ESPColor.R,ESPColor.G,ESPColor.B ,ESPColor.A }, 2, 15, 2);
			}
			else
			{
				ImGui::GetOverlayDrawList()->AddRect({ scrposeye.x - width,scrposeye.y }, { scrposfood.x + width,scrposfood.y }, ImColor{ 255,255,255 ,255 }, 2, 15, 2);
			}

		}		
		else if (botposer->isProtected)
			ImGui::GetOverlayDrawList()->AddRect({ scrposeye.x - width,scrposeye.y }, { scrposfood.x + width,scrposfood.y }, ImColor{ 0,0,255,255 }, 2, 15, 2);		
	}
}
