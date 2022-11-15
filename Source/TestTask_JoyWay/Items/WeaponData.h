#pragma once

#include "CoreMinimal.h"
#include "ItemData.h"
#include "WeaponData.generated.h"


UCLASS()
class TESTTASK_JOYWAY_API UWeaponData : public UItemData
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere)
	float Damage;

	UPROPERTY(EditAnywhere)
	int32 Ammo;

	UPROPERTY(EditAnywhere)
	float UseRate;

	UPROPERTY(EditAnywhere)
	bool bAutoFire;

	UPROPERTY(EditAnywhere)
	float ReloadRate;

	UPROPERTY(EditAnywhere)
	bool bInfinityAmmo;
};
