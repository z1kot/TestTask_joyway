#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemData.h"
#include "BaseItem.generated.h"


UCLASS()
class TESTTASK_JOYWAY_API ABaseItem : public AActor
{
	GENERATED_BODY()
	
public:	

	ABaseItem();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UItemData* ItemData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName AttachSocketName;

public:

	UFUNCTION(BlueprintCallable)
	virtual void HideAndAttach();

	UFUNCTION(BlueprintCallable)
	virtual void ShowAndAttach(USceneComponent* ParentComp);

	UFUNCTION(BlueprintCallable)
	virtual void UseItem() {};

	UFUNCTION(BlueprintCallable)
	virtual void StopUseItem() {};

	UFUNCTION(BlueprintCallable)
	virtual void InitParams() {};

protected:

	virtual void BeginPlay() override;
};