// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ScrollBox.h"
#include "Components/SizeBox.h"

#include "SelectScrollBox.generated.h"

/** *
 * 
 */
UCLASS()
class WIDGETEXPANSIONS_API USelectScrollBox : public UScrollBox
{
	GENERATED_BODY()
	
public:

	/** * 识别的ID */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SelectScrollBox|Variable")
	FString ID;

	/** * 识别的UID */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SelectScrollBox|Variable")
	TArray<FString> IDs;

	/** * 识别的UID */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SelectScrollBox|Variable")
	TArray<FText> Texts;

	/** * 选择索引 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SelectScrollBox|Variable")
	int SelectIndex;

	/** * 按键高度 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SelectScrollBox|Variable")
	float ButttonSize = 60;

	/** * 默认样式 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SelectScrollBox|Appearance")
	FButtonStyle DefaultStyle;

	/** * 选择样式 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SelectScrollBox|Appearance")
	FButtonStyle SelectStyle;

	/** * 文字样式 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SelectScrollBox|Appearance")
	FSlateFontInfo SlateFontInfo;

	/** * 资源图片组 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SelectScrollBox|Variable")
	TArray<TObjectPtr<USizeBox>> SizeBoxWidgets;

	/** * * 委托宏2个输入 */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnIDClickedEvent, const FString&, OnID, const FString&, SelectID);

	/** * * 委托宏2个输入 */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnIDHoverEvent, const FString&, OnID, const FString&, SelectID);

	/** * * 触发的委托变量 */
	UPROPERTY(BlueprintAssignable, Category = "SelectScrollBox|On")
	FOnIDClickedEvent OnClickedSelect;

	/** * * 触发的委托变量 */
	UPROPERTY(BlueprintAssignable, Category = "SelectScrollBox|On")
	FOnIDHoverEvent OnHoverSelect;

protected:
	/** * Function called after the underlying SWidget is constructed. */
	virtual void OnWidgetRebuilt() override;

	//virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

	virtual void NativeConstruct();

public:

	/* * 按下的委托 */
	UFUNCTION(BlueprintCallable, Category = "SelectScrollBox|Function")
	void OnClickedID_Event(const FString& OnID);

	/* * 触摸的委托 */
	UFUNCTION(BlueprintCallable, Category = "SelectScrollBox|Function")
	void OnHoveredID_Event(const FString& OnID);

	/* * 设置索引显示,是否委托 */
	UFUNCTION(BlueprintCallable, Category = "SelectScrollBox|Function")
	void SetSelectIndex(int Index, bool bDelegate = false);

	/* * 初始化按钮 */
	UFUNCTION(BlueprintCallable, Category = "SelectScrollBox|Function")
	void InitButton();

	/* * 初始化数据 */
	UFUNCTION(BlueprintCallable, Category = "SelectScrollBox|Function")
	void InitData(TArray<FString> InIDs, TArray<FText> InTexts);

	/* * 设置选择ID */
	UFUNCTION(BlueprintCallable, Category = "SelectScrollBox|Function")
	void SetSelectID(const FString& OnID, bool bDelegate = false);

};
