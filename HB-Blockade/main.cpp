#include "includes.h"
#include "Cheat/Wallhack.hh"
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

bool init = false;
bool show;
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
	if (Wallhack::enable)
		Wallhack::Draw();

	if (GetAsyncKeyState(VK_INSERT) & 1)
		show = !show;

	if (show)
	{


	ImGui::Begin("HB-Blockade");
	ImGui::Checkbox("Wallhack" ,&Wallhack::enable);
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

void HookDX11()
{
	if (!GetModuleHandleA("GameOverlayRenderer64.dll"))
	{
		exit(0);
	}
	AllocConsole();
	FILE* f;
	freopen_s(&f, "CONOUT$", "w", stdout);
	std::cout<<std::hex << Addr::RemotePlayersController << "\n";
	uintptr_t Steam_DXGI_PresentScene = Utils::sigscan("48 89 6C 24 18 48 89 74 24 20 41 56 48 83 EC 20 41 8B E8", "GameOverlayRenderer64.dll");
	if (Steam_DXGI_PresentScene)
		hook(Steam_DXGI_PresentScene, (__int64)hkPresent, (__int64*)&oPresent);
	return;
}






BOOL __fastcall DllMain(HMODULE hm, DWORD  r, LPVOID lpR)
{

	if (r == 1)
		HookDX11();

	return TRUE;
}