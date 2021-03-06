#pragma once
#include <Windows.h>
#include "Mono.h"
#include "IL2CPP.h"
#include <vector>

typedef HMODULE(__stdcall* LoadLibraryW_t) (LPCWSTR lpLibFileName);

class HookManager_Hook;

class HookManager
{
public:
	static std::vector<HookManager_Hook*>HookTbl;
	static HookManager_Hook* FindHook(void** target, void* detour);

	static LoadLibraryW_t Original_LoadLibraryW;
	static void LoadLibraryW_Hook();
	static void LoadLibraryW_Unhook();

	static void Hook(Il2CppMethod* target, void* detour) { INTERNAL_Hook(&(LPVOID&)target->targetMethod, detour); };
	static void Hook(void** target, void* detour);
	static void INTERNAL_Hook(void** target, void* detour);

	static void Unhook(Il2CppMethod* target, void* detour) { INTERNAL_Unhook(&(LPVOID&)target->targetMethod, detour); };
	static void Unhook(void** target, void* detour);
	static void UnhookAll();
	static void INTERNAL_Unhook(void** target, void* detour);

	static HMODULE __stdcall Hooked_LoadLibraryW(LPCWSTR lpLibFileName);
	static Il2CppDomain* Hooked_il2cpp_init(const char* name);
	static MonoDomain* Hooked_mono_jit_init_version(const char* name, const char* version);
	static void Hooked_il2cpp_add_internal_call(const char* name, void* method);
	static void* Hooked_mono_lookup_internal_call_full(MonoMethod* method, int* uses_handles);
	static Il2CppClass* Hooked_il2cpp_class_from_system_type(Il2CppReflectionType* type);
	static Il2CppGlobalMetadataHeader* Hooked_MetadataLoader_LoadMetadataFile(const char* fileName);
	static bool Hooked_SingleAppInstance_FindOtherInstance(LPARAM lParam);
	static bool Hooked_PlayerCleanup(bool dopostquitmsg);
	static void* Hooked_PlayerLoadFirstScene(bool unknown);
	static __int64 Hooked_BaseBehaviourManager_Update(void* behaviour_manager);
	static __int64 Hooked_BaseBehaviourManager_FixedUpdate(void* behaviour_manager);
	static __int64 Hooked_BaseBehaviourManager_LateUpdate(void* behaviour_manager);
	static void Hooked_GUIManager_DoGUIEvent(void* __0, void* __1, bool __2);
	static void Hooked_EndOfFrameCallbacks_DequeAll();
};

class HookManager_Hook
{
public:
	HookManager_Hook(void** target, void* detour) { Target = target; Detour = detour; }
	void** Target;
	void* Detour;
};