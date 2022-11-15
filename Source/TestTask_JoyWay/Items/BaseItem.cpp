#include "BaseItem.h"

ABaseItem::ABaseItem()
{
	PrimaryActorTick.bCanEverTick = false;

	AttachSocketName = FName(TEXT("ItemSocket"));
}

void ABaseItem::BeginPlay()
{
	Super::BeginPlay();

	InitParams();
}

void ABaseItem::HideAndAttach()
{
	SetActorEnableCollision(false);
	SetActorHiddenInGame(true);

	if (GetOwner())
	{
		AttachToActor(GetOwner(), FAttachmentTransformRules::SnapToTargetIncludingScale);
	}
}

void ABaseItem::ShowAndAttach(USceneComponent* ParentComp)
{
	SetActorHiddenInGame(false);

	if (GetOwner())
	{
		AttachToComponent(ParentComp, FAttachmentTransformRules::SnapToTargetIncludingScale, AttachSocketName);
	}
}