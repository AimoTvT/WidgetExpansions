// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SizeBox.h"
#include "Components/Button.h"

#include "SizeBoxIDButton.generated.h"

/**
 * 
 */
UCLASS()
class WIDGETEXPANSIONS_API USizeBoxIDButton : public USizeBox
{
	GENERATED_BODY()
	
public:

	/** 按钮 */
	UPROPERTY(BlueprintReadOnly, Category = "SizeBoxIDButton|Variable")
	TObjectPtr<UButton> Button;

	/** 识别的ID */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SelectHorizontalBox|Variable")
	FString ID;

	/** 默认样式 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SelectHorizontalBox|Appearance")
	FButtonStyle DefaultStyle;

	/** 选择样式 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SelectHorizontalBox|Appearance")
	FButtonStyle SelectStyle;

	/** 文字样式 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SelectHorizontalBox|Appearance")
	FSlateFontInfo SlateFontInfo;


	/** * 委托宏2个输入 */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnIDClickedEvent, const FString&, OnID);

	/** * 委托宏2个输入 */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnIDHoverEvent, const FString&, OnID);

	/** * 触发的委托变量 */
	UPROPERTY(BlueprintAssignable, Category = "SizeBoxIDButton|On")
	FOnIDClickedEvent OnIDClicked;

	/** * 触发的委托变量 */
	UPROPERTY(BlueprintAssignable, Category = "SizeBoxIDButton|On")
	FOnIDHoverEvent OnIDHover;

protected:
	/** Function called after the underlying SWidget is constructed. */
	virtual void OnWidgetRebuilt() override;

	//virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

	virtual void NativePreConstruct();

public:


	/* * 最大支持的按钮数量 */
	UFUNCTION(BlueprintCallable, Category = "SizeBoxIDButton|Function")
	void OnIDClicked_Event();

	/* * 最大支持的按钮数量 */
	UFUNCTION(BlueprintCallable, Category = "SizeBoxIDButton|Function")
	void OnIDHovered_Event();

};
