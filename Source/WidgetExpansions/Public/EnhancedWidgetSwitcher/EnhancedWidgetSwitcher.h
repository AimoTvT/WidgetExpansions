// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetSwitcher.h"
#include "EnhancedWidgetSwitcher.generated.h"

/**
 * 
 */
UCLASS()
class WIDGETEXPANSIONS_API UEnhancedWidgetSwitcher : public UWidgetSwitcher
{
	GENERATED_BODY()

public:

	/** * 持有设备空间索引 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "EnhancedWidgetSwitcher|Variable")
	uint8 RemoveModeIndex = 0;

	/** * * 委托宏1个输入 */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRemoveChild,const UPanelSlot*, InSlot);

	/** * * 通讯委托,多播,通讯 */
	UPROPERTY(BlueprintAssignable, Category = "EnhancedWidgetSwitcher|On")
	FOnRemoveChild OnRemoveChild;

public:
	virtual void OnSlotRemoved(UPanelSlot* InSlot) override;
	
};
