#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UObject/ScriptDelegates.h"
#include "HealthComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDeadDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHealthChangedDelegate, float, NewHealth);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TESTTASK_JOYWAY_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UHealthComponent();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float Health;

	UPROPERTY(BlueprintReadWrite)
	float MaxHealth;

	UPROPERTY(BlueprintReadWrite)
	bool bDead;

	UPROPERTY(BlueprintAssignable)
	FDeadDelegate DeadDelegate;

	UPROPERTY(BlueprintAssignable)
	FHealthChangedDelegate HealthChangedDelegate;

public:

	UFUNCTION(BlueprintCallable)
	void ReceiveDamage(float Damage, AActor* Causer);

	UFUNCTION(BlueprintCallable)
	void ResetStats();

protected:

	virtual void BeginPlay() override;

		
};
