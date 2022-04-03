#include "includes.h"
#include "Cheat/Wallhack.hh"
#include "Cheat/Aimbot.hh"

#include <cstdio>
#include <iostream>

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

Present oPresent;
HWND window = NULL;
WNDPROC oWndProc;
ID3D11Device* pDevice = NULL;
ID3D11DeviceContext* pContext = NULL;
ID3D11RenderTargetView* mainRenderTargetView;

void InitImGui()
{
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX11_Init(pDevice, pContext);
}

LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}
bool show;
bool init = false;



HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
	if (!init)
	{
		if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&pDevice)))
		{
			pDevice->GetImmediateContext(&pContext);
			DXGI_SWAP_CHAIN_DESC sd;
			pSwapChain->GetDesc(&sd);
			window = sd.OutputWindow;
			ID3D11Texture2D* pBackBuffer;
			pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
			pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView);
			pBackBuffer->Release();
			oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);
			InitImGui();
			init = true;


		}

		else
			return oPresent(pSwapChain, SyncInterval, Flags);
	}

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	ImGuiIO IMIO = ImGui::GetIO();
	Global_vars::ScreenW = IMIO.DisplaySize.x;
	Global_vars::ScreenH = IMIO.DisplaySize.y;


	if (Wallhack::enable)
		Wallhack::Draw();
		ImGui::GetOverlayDrawList()->AddCircle({Global_vars::ScreenW / 2 ,Global_vars::ScreenH / 2},Aimbot::fov,ImColor(255,255,255,255),64,1);

	if (GetAsyncKeyState(VK_INSERT) & 1)
		show = !show;

	if (show)
	{


	ImGui::Begin("HB-Blockade");
	ImGui::Checkbox("W4ll-h4ck" ,&Wallhack::enable);
	ImGui::SliderFloat("A1m F0v" ,&Aimbot::fov,5,600);


	ImGui::End();

	}

	ImGui::Render();

	pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	return oPresent(pSwapChain, SyncInterval, Flags);
}

void hook(__int64 addr, __int64 func, __int64* orig)
{
	static uintptr_t hook_addr;
	if (!hook_addr)
		hook_addr = Utils::sigscan("48 ? ? ? ? 57 48 83 EC 30 33 C0","GameOverlayRenderer64.dll" );
	auto hook = ((__int64(__fastcall*)(__int64 addr, __int64 func, __int64* orig, __int64 smthng))(hook_addr));
	hook((__int64)addr, (__int64)func, orig, (__int64)1);
}
// __int64 __fastcall sub_1813EA4F0(__int64 a1, __int64 a2, unsigned __int64 *a3)

void HookDX11()
{
	if (!GetModuleHandleA("GameOverlayRenderer64.dll"))
	{
		exit(0);
	}
	AllocConsole();
	FILE* f;
	freopen_s(&f, "CONOUT$", "w", stdout);

	uintptr_t Steam_DXGI_PresentScene = Utils::sigscan("48 89 6C 24 18 48 89 74 24 20 41 56 48 83 EC 20 41 8B E8", "GameOverlayRenderer64.dll");
	if (Steam_DXGI_PresentScene)
		hook(Steam_DXGI_PresentScene, (__int64)hkPresent, (__int64*)&oPresent);

	Utils::SpoofCall((void*)Addr::callScreenPointToRay, &Aimbot::SpoofTest, (__int64*)&Aimbot::oScreenToRayadr);
	return;
}






BOOL __fastcall DllMain(HMODULE hm, DWORD  r, LPVOID lpR)
{

	if (r == 1)
		HookDX11();

	return TRUE;
}