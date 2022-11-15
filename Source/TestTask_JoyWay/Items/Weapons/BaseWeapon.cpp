#include "BaseWeapon.h"
#include "TestTask_JoyWay/Interfaces/PlayerWeaponInterface.h"
#include "BaseWeaponProjectile.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/AudioComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"

ABaseWeapon::ABaseWeapon()
{
	AttachSocketName = FName(TEXT("WeaponSocket"));

	Projectile = ABaseWeaponProjectile::StaticClass();

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(SceneComponent);

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->AttachToComponent(SceneComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);

	ReloadAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("ReloadAudio"));
	ReloadAudio->AttachToComponent(SceneComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);

	MuzzleParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MuzzleParticle"));
	MuzzleParticle->AttachToComponent(WeaponMesh, FAttachmentTransformRules::SnapToTargetIncludingScale, FName(TEXT("Muzzle")));
}

void ABaseWeapon::InitParams()
{
	WeaponData = Cast<UWeaponData>(ItemData);

	CurrentAmmo = WeaponData->Ammo;
	Damage = WeaponData->Damage;
	UseRate = WeaponData->UseRate;
	bAutoFire = WeaponData->bAutoFire;
	ReloadRate = WeaponData->ReloadRate;
	bInfinityAmmo = WeaponData->bInfinityAmmo;
}

void ABaseWeapon::UseItem()
{
	Super::UseItem();
	UseWeapon();
}

void ABaseWeapon::StopUseItem()
{
	bFireActive = false;
}

bool ABaseWeapon::AbleToUse()
{
	return CurrentAmmo > 0 && !bUseFreezedByRate || bInfinityAmmo && !bUseFreezedByRate;
}

bool ABaseWeapon::UseWeapon()
{
	if (AbleToUse())
	{
		if (!bInfinityAmmo)
		{
			CurrentAmmo--;
		}

		bUseFreezedByRate = true;

		GetWorld()->GetTimerManager().SetTimer(UseRateTimer, this, &ABaseWeapon::StopRateDelay, UseRate);

		Fire();

		// Cosmetic function
		OnWeaponFired();

		AmmoChangedDelegate.Broadcast(CurrentAmmo);

		if (bAutoFire)
		{
			bFireActive = true;
		}

		return true;
	}

	if (CurrentAmmo == 0 && !bUseFreezedByRate)
	{
		TryReloadWeapon();

		bFireActive = false;
		return false;
	}

	bFireActive = false;
	return false;
}

void ABaseWeapon::Fire()
{
	if (Projectile && GetOwner())
	{
		if (GetOwner()->Implements<UPlayerWeaponInterface>())
		{
			FRotator FireDir = IPlayerWeaponInterface::Execute_GetFireDir(GetOwner()).ToOrientationRotator();
			FVector SpawnLocation;

			// Get Projectile start location
			if (WeaponMeshComp)
			{
				SpawnLocation = WeaponMeshComp->GetSocketLocation(FName(TEXT("Muzzle")));
			}

			// Shoot Projectile
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = GetOwner();
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
			ABaseWeaponProjectile* ActorProjectile = Cast<ABaseWeaponProjectile>(GetWorld()->SpawnActor(Projectile, &SpawnLocation, &FireDir, SpawnParams));

			ActorProjectile->InitParams(Damage);

			return;
		}
	}
}

void ABaseWeapon::StopRateDelay()
{
	bUseFreezedByRate = false;
	GetWorld()->GetTimerManager().ClearTimer(UseRateTimer);

	// Cosmetic function
	OnWeaponReadyToFire();

	// Auto fire logic
	if (bAutoFire && bFireActive)
	{
		UseWeapon();
	}
}

void ABaseWeapon::TryReloadWeapon()
{
	GetWorld()->GetTimerManager().ClearTimer(UseRateTimer);

	bUseFreezedByRate = true;
	GetWorld()->GetTimerManager().SetTimer(UseRateTimer, this, &ABaseWeapon::ReloadAmmo, ReloadRate);

	// Cosmetic function
	OnStartReloading();
}

void ABaseWeapon::ReloadAmmo()
{
	CurrentAmmo = WeaponData->Ammo;
	bUseFreezedByRate = false;

	AmmoChangedDelegate.Broadcast(CurrentAmmo);
}

void ABaseWeapon::OnWeaponFired_Implementation()
{
	MuzzleParticle->Activate(true);

	// Fire sound has long sound tail for better effect, that's why we spawned sound, but not playing by audio component
	UGameplayStatics::SpawnSoundAttached(FireSound, this->GetRootComponent());
}

void ABaseWeapon::OnWeaponReadyToFire_Implementation()
{
}

void ABaseWeapon::OnStartReloading_Implementation()
{
	ReloadAudio->Activate(true);
}

void ABaseWeapon::HideAndAttach()
{
	Super::HideAndAttach();

	// Hide Ammo Counter and clear all binds
	AmmoChangedDelegate.Broadcast(-1);
	AmmoChangedDelegate.Clear();
}