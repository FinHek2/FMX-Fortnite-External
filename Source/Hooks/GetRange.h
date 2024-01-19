#pragma once

float (*GetRangeOriginal)(AFortWeapon*);
float GetRange(AFortWeapon* FortWeapon)
{
	return reinterpret_cast<float(__cdecl*)(AFortWeapon*, uintptr_t, void*)>(DoSpoofCall)(FortWeapon, SpoofCode, GetRangeOriginal);
}