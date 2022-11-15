#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FActiveItemDelegate, AActor*, ActiveItem);

class ABaseItem;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TESTTASK_JOYWAY_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UInventoryComponent();

	UPROPERTY(BlueprintReadWrite)
	TArray<ABaseItem*> Items;

	UPROPERTY(BlueprintReadWrite)
	ABaseItem* ActiveItem;

	UPROPERTY(BlueprintReadWrite)
	UPrimitiveComponent* ParentAttachComp;

	UPROPERTY(BlueprintAssignable)
	FActiveItemDelegate ActiveItemDelegate;

public:

	UFUNCTION(BlueprintCallable)
	void AddToInventory(AActor* AddItem);

	UFUNCTION(BlueprintCallable)
	void SetActiveItem(ABaseItem* NewItem);

	UFUNCTION(BlueprintCallable)
	void UseActiveItem();

	UFUNCTION(BlueprintCallable)
	void StopUseActiveItem();
};
