// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "IDButton.generated.h"

/** *
 * 
 */
UCLASS()
class WIDGETEXPANSIONS_API UIDButton : public UButton
{
	GENERATED_BODY()
	
public:

	/** * 控件ID */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "IDButton|Variable")
	FString ID;

	/** * * 委托宏1个输入 */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnButtonClickedIDEvent, const FString&, ID);

	/** * * 委托宏1个输入 */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnButtonHoverIDEvent, const FString&, ID);

	/** * * 点击委托ID */
	UPROPERTY(BlueprintAssignable, Category = "IDButton|On")
	FOnButtonClickedIDEvent OnClickedID;

	/** * * 悬浮委托ID */
	UPROPERTY(BlueprintAssignable, Category = "IDButton|On")
	FOnButtonHoverIDEvent OnHoveredID;

protected:
	/** * 构造底层widget后调用的函数. */
	virtual void OnWidgetRebuilt() override;

	/** * 按钮点击后的委托 */
	UFUNCTION(BlueprintCallable, Category = "IDButton|Function")
	virtual void OnClickedID_Event();

	/** * 按钮悬浮的委托 */
	UFUNCTION(BlueprintCallable, Category = "IDButton|Function")
	virtual void OnHoveredID_Event();

};
