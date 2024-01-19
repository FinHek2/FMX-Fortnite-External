#pragma once
#include <Windows.h>
#include <iostream>
#include <cstdint>
#include <array>
#include <future>
#include <winternl.h>

uintptr_t GameBase = 0;

namespace Offsets
{
	int GWorld = 0x10AEC0B8;

	// Functions
	int StaticFindObject = 0x1216928;
	int GetBoneMatrix = 0x11F2D70;
	int GetWeaponStats = 0x39CD268;
	int WeaponFireSingle = 0xA44CFF0;
	int Malloc = 0x10584D8;
	int Free = 0x38D53D0;

	// Virtual Tables
	int PlayerVtable = 0x6F0;

	// Virtual Indexs
	int IsAllowedToRender = 110;
	int PostRender = 0x380 / 0x8;
	int InputKey = 0xDA8 / 0x8;
	int ProcessEvent = 0x268 / 0x8;
	int GetMaterial = 0x2B8 / 0x8;
	int GetPlayerViewPoint = 0x7F0 / 0x8;
	int GetCameraViewPoint = 0x7F8 / 0x8;
	int GetTargetingTransform = 0x10 / 0x8;
	int FireSingle = 0xB20 / 0x8;
	int GetRange = 0x9A0 / 0x8;
	int GetReloadTime = 0x980 / 0x8;
	int GetFiringRate = 0x9D0 / 0x8;
	int GetReloadProgress = 0x988 / 0x8;
	int GetProjectileSpeed = 0x9C0 / 0x8;
	int GetDamageStartLocation = 0x7C0 / 0x8;
	int TryToFire = 0x7E8 / 0x8;
	int CheckPendingFire = 0x828 / 0x8;
	int PlayDelayedRecoil = 0xCF8 / 0x8;
}

#define SpoofCode 0x13041052

#include <Helper/Safety/SKCrypter.h>
#include <Helper/Custom/NoCRT.h>

#include <Helper/Custom/Map.h>
#include <Helper/Custom/Vector.h>
#include <Helper/PEB.h>
#include <Helper/SysCall.h>
#include <Helper/SpoofCall.h>

#include <Helper/Custom/Module.h>
#include <Helper/VTableHook.h>

#include <Fortnite/SDK/Structs.h>
#include <Fortnite/SDK/Classes.h>
#include <Fortnite/Settings.h>

namespace Variables
{
	UCanvas* DebugCanvasObject = nullptr;
	APlayerController* PlayerController = nullptr;
	APlayerPawn_Athena_C* AcknowledgedPawn = nullptr;
	FName MaterialParameter = FName(0);
	FName MaterialParameter2 = FName(0);
	FName MaterialParameter3 = FName(0);
	FName MaterialParameter4 = FName(0);
	FName MaterialParameter5 = FName(0);
	FName MaterialParameter6 = FName(0);

	const wchar_t* BuildTime = nullptr;

	//Variables
	static FVector2D ScreenCenter = FVector2D();
	static FVector2D ScreenSize = FVector2D();

	//Bullet teleport
	static FVector BulletTeleportHead = FVector();

	//Camera
	static FVector CameraLocation = FVector();
	static FRotator CameraRotation = FRotator();
	static float FieldOfView = 0.f;

	//Bullet tracer
	static int LastBulletIndexPushed = 0;
	static FVector Last5BulletImpacts[5];
	static FVector Last5BulletImpactsMuzzle[5];

	namespace GetPlayerViewPoint
	{
		static bool bShouldStartAtLocationTarget = false;
		static FVector SilentLocationTarget = FVector();
		static FRotator LastTargetRotation = FRotator();
		static FVector OriginalLocation = FVector();
		static FRotator OriginalRotation = FRotator();
	}

	namespace GetCameraViewPoint
	{
		static FRotator LastStickyRotation = FRotator();
		static FVector StickyLocation = FVector();
	}

	namespace GetTargetingTransform
	{
		static bool bPickaxeRangeActive = false;
		static bool bShouldStartAtLocationTarget = false;
		static FVector LocationTarget = FVector();
	}

	namespace GetDamageStartLocation
	{
		static bool bSilentAimActive = false;
		static FVector SilentLocationTarget = FVector();
		static FRotator LastTargetRotation = FRotator();
	}
	
	// MISC
	static bool DrawMenu = true;
	static bool SetBackToMessage = true;
}

namespace Keys
{
	FKey LeftMouseButton;
	FKey RightMouseButton;
	FKey Insert;
	FKey F2;
	FKey F8;
	FKey W;
	FKey A;
	FKey S;
	FKey D;
	FKey SpaceBar;
	FKey LeftShift;
}

enum Bones : int {
	Root = 0,
	pelvis = 2,
	spine_01 = 3,
	spine_02 = 4,
	spine_03 = 5,
	spine_04 = 6,
	spine_05 = 7,
	clavicle_l = 8,
	upperarm_l = 9,
	lowerarm_l = 10,
	hand_l = 33,
	clavicle_r = 37,
	upperarm_r = 38,
	lowerarm_r = 65,
	hand_r = 62,
	neck_01 = 66,
	neck_02 = 67,
	head = 68,
	thigh_l = 71,
	calf_l = 72,
	calf_twist_01_l = 73,
	calf_twist_02_l = 74,
	foot_l = 76,
	thigh_r = 78,
	calf_r = 79,
	calf_twist_01_r = 80,
	calf_twist_02_r = 81,
	foot_r = 83,
	camera_root = 92,
	Camera = 93,
	attach_fp = 94,
};

const wchar_t* GetBuildTime()
{
	const char* BuildTimeA = __TIME__;
	const int BuildTimeALength = __strlen(BuildTimeA);
	wchar_t* WideArray = new wchar_t[BuildTimeALength + 1];

	for (int i = 0; i < BuildTimeALength; i++)
	{
		WideArray[i] = static_cast<wchar_t>(BuildTimeA[i]);
	}

	WideArray[BuildTimeALength] = L'\0';

	return WideArray;
}

#include <Fortnite/Hooks/GetPlayerViewPoint.h>
#include <Fortnite/Hooks/GetCameraViewPoint.h>
#include <Fortnite/Hooks/GetTargetingTransform.h>
#include <Fortnite/Hooks/FireSingle.h>
#include <Fortnite/Hooks/GetReloadTime.h>
#include <Fortnite/Hooks/GetFiringRate.h>
#include <Fortnite/Hooks/GetProjectileSpeed.h>
#include <Fortnite/Hooks/GetDamageStartLocation.h>
#include <Fortnite/Hooks/TryToFire.h>
#include <Fortnite/Hooks/GetRange.h>
#include <Fortnite/Hooks/CheckPendingFire.h>

#include <Fortnite/Hooks.h>
#include <Fortnite/Hooks/PostRender.h>