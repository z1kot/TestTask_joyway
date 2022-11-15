#pragma once

#include "CoreMinimal.h"
#include "TestTask_JoyWay/Items/BaseItem.h"
#include "TestTask_JoyWay/Items/WeaponData.h"
#include "BaseWeapon.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAmmoChangedDelegate, int32, CurrentAmmo);

class ABaseWeaponProjectile;
class USceneComponent;
class UStaticMeshComponent;
class UAudioComponent;
class UParticleSystemComponent;

UCLASS()
class TESTTASK_JOYWAY_API ABaseWeapon : public ABaseItem
{
	GENERATED_BODY()

public:

	ABaseWeapon();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USceneComponent* SceneComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* WeaponMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UAudioComponent* ReloadAudio;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UParticleSystemComponent* MuzzleParticle;

	UPROPERTY(BlueprintReadWrite)
	UWeaponData* WeaponData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<ABaseWeaponProjectile> Projectile;

	UPROPERTY(BlueprintReadWrite)
	int32 CurrentAmmo;

	UPROPERTY(BlueprintReadWrite)
	bool bUseFreezedByRate;

	UPROPERTY(BlueprintReadWrite)
	bool bFireActive;

	UPROPERTY(BlueprintReadOnly)
	bool bAutoFire;

	UPROPERTY(BlueprintReadWrite)
	FTimerHandle UseRateTimer;

	UPROPERTY(BlueprintReadWrite)
	float UseRate;

	UPROPERTY(BlueprintReadWrite)
	float Damage;

	UPROPERTY(BlueprintReadWrite)
	float ReloadRate;

	UPROPERTY(BlueprintReadOnly)
	bool bInfinityAmmo;

	UPROPERTY(BlueprintReadWrite)
	UPrimitiveComponent* WeaponMeshComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	USoundBase* FireSound;

	UPROPERTY(BlueprintAssignable)
	FAmmoChangedDelegate AmmoChangedDelegate;

public:

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool AbleToUse();

	UFUNCTION(BlueprintCallable)
	bool UseWeapon();

	UFUNCTION(BlueprintCallable)
	void Fire();

	UFUNCTION(BlueprintCallable)
	void StopRateDelay();

	UFUNCTION(BlueprintCallable)
	void TryReloadWeapon();

	UFUNCTION(BlueprintCallable)
	void ReloadAmmo();

	UFUNCTION(BlueprintNativeEvent)
	void OnWeaponFired();

	UFUNCTION(BlueprintNativeEvent)
	void OnWeaponReadyToFire();

	UFUNCTION(BlueprintNativeEvent)
	void OnStartReloading();

public:

	virtual void UseItem() override;

	virtual void StopUseItem() override;

	virtual void InitParams() override;

	virtual void HideAndAttach() override;
};
