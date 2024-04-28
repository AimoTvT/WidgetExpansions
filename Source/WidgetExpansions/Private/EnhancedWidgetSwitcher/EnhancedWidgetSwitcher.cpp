// Fill out your copyright notice in the Description page of Project Settings.


#include "EnhancedWidgetSwitcher/EnhancedWidgetSwitcher.h"

void UEnhancedWidgetSwitcher::OnSlotRemoved(UPanelSlot* InSlot)
{
	Super::OnSlotRemoved(InSlot);
	if (RemoveModeIndex == 0)
	{
		if (Slots.Num() == 0)
		{
			OnRemoveChild.Broadcast(InSlot);
		}
	}
	else
	{
		OnRemoveChild.Broadcast(InSlot);
	}
}
