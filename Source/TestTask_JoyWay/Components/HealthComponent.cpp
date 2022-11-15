#include "HealthComponent.h"


UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	Health = 1.0f;
	bDead = false;
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	MaxHealth = Health;
}

void UHealthComponent::ReceiveDamage(float Damage, AActor* Causer)
{
	if (bDead)
	{
		return;
	}

	Health -= Damage;

	HealthChangedDelegate.Broadcast(Health);

	if (Health <= 0.0f)
	{
		bDead = true;

		DeadDelegate.Broadcast();
	}
}

// For player respawn logic
void UHealthComponent::ResetStats()
{
	Health = MaxHealth;
	bDead = false;

	HealthChangedDelegate.Broadcast(Health);
}