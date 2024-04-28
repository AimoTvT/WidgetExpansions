// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Image.h"
#include "EnhancedImage.generated.h"

/** *
 * 
 */
UCLASS()
class WIDGETEXPANSIONS_API UEnhancedImage : public UImage
{
	GENERATED_BODY()

public:

	/** * 最大图像大小 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget), Category = "EnhancedImage|Variable")
	FVector2D MaxImageSize = FVector2D(32.0f, 32.0f);

	/** * 图像比例 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget), Category = "EnhancedImage|Variable")
	bool bMaxImageSize = true;

public:

	/** * 设置最大图像大小 */
	UFUNCTION(BlueprintCallable, Category = "EnhancedImage|Function")
	virtual void SetMaxImageSize(const FVector2D& MaxSize);

	/** * 异步样式软Object增强 */
	UFUNCTION(BlueprintCallable, Category = "EnhancedImage|Function")
	virtual void AsyncBrushFromSoftObjectPtr(const TSoftObjectPtr<UObject>& InSoftObjectPtr);

	/** * 设置样式软路径 */
	UFUNCTION(BlueprintCallable, Category = "EnhancedImage|Function")
	virtual void SetBrushFromSoftPath(const FString& Path, const FVector2D& MaxSize = FVector2D(0.0f, 0.0f));

	/** * 设置样式软Object */
	UFUNCTION(BlueprintCallable, Category = "EnhancedImage|Function")
	virtual void SetBrushFromSoftObjectPtr(const TSoftObjectPtr<UObject>& InSoftObjectPtr, const FVector2D& MaxSize = FVector2D(0.0f, 0.0f));

	/** * 设置样式资源Object */
	UFUNCTION(BlueprintCallable, Category = "EnhancedImage|Function")
	virtual void SetBrushFromResourceObject(UObject* Object);

	


}; 
