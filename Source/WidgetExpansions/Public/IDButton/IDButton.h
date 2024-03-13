// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "IDButton.generated.h"

/**
 * 
 */
UCLASS()
class WIDGETEXPANSIONS_API UIDButton : public UButton
{
	GENERATED_BODY()
	
public:

	/** 控件ID */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "IDButton|Variable")
	FString ID;

	/** * 委托宏1个输入 */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnIDButtonClickedEvent, const FString&, ID);

	/** * 委托宏1个输入 */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnIDButtonHoverEvent, const FString&, ID);

	/** * 通讯委托,多播,通讯 */
	UPROPERTY(BlueprintAssignable, Category = "IDButton|On")
	FOnIDButtonClickedEvent OnIDClicked;

	/** * 通讯委托,多播,通讯 */
	UPROPERTY(BlueprintAssignable, Category = "IDButton|On")
	FOnIDButtonHoverEvent OnIDHovered;

protected:
	/** Function called after the underlying SWidget is constructed. */
	virtual void OnWidgetRebuilt() override;

	/**  */
	UFUNCTION(BlueprintCallable, Category = "IDButton|Function")
	virtual void OnIDClicked_Event();

	/**  */
	UFUNCTION(BlueprintCallable, Category = "IDButton|Function")
	virtual void OnIDHovered_Event();

};
