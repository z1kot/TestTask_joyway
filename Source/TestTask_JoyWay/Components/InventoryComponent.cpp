#include "InventoryComponent.h"
#include "TestTask_JoyWay/Items/BaseItem.h"

UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UInventoryComponent::AddToInventory(AActor* AddItem)
{
	if (AddItem)
	{
		ABaseItem* NewItem = Cast<ABaseItem>(AddItem);
		if (NewItem && Items.Contains(NewItem) == false)
		{
			Items.Add(NewItem);
			NewItem->SetOwner(GetOwner());

			NewItem->HideAndAttach();

			if (!ActiveItem)
			{
				SetActiveItem(NewItem);
			}
		}
	}
}

void UInventoryComponent::SetActiveItem(ABaseItem* NewItem)
{
	// Hide previous active item
	if (ActiveItem)
	{
		ActiveItem->HideAndAttach();
	}

	ActiveItem = NewItem;

	// Show new active item
	if (ParentAttachComp)
	{
		ActiveItem->ShowAndAttach(ParentAttachComp);

		ActiveItemDelegate.Broadcast(ActiveItem);
	}
}

void UInventoryComponent::UseActiveItem()
{
	if (ActiveItem)
	{
		ActiveItem->UseItem();
	}
}

void UInventoryComponent::StopUseActiveItem()
{
	if (ActiveItem)
	{
		ActiveItem->StopUseItem();
	}
}