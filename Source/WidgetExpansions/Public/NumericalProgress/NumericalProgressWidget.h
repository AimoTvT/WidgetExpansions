// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NumericalProgressWidget.generated.h"

/**
 * 
 */
UCLASS()
class WIDGETEXPANSIONS_API UNumericalProgressWidget : public UUserWidget
{
	GENERATED_BODY()
public:

	/** * 数值 */
	UPROPERTY(BlueprintReadWrite, Category = "Aimo|Variable")
	float Numerical = 100.0f;

	/** * 数值最大 */
	UPROPERTY(BlueprintReadWrite, Category = "Aimo|Variable")
	float NumericalMax = 100.0f;

	/** * 超额数值 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aimo|Variable")
	float ExcessNumerical = 0.0f;

	/** * 插值数值 */
	UPROPERTY(BlueprintReadWrite, Category = "Aimo|Variable")
	float InterpNumerical = 100.0f;

	/** * 插值超额数值 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aimo|Variable")
	float InterpExcessNumerical = 100.0f;

	/** * 插值速度 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aimo|Variable")
	float InterpSpeed = 10.0f;

	/** * 延迟插值时间 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aimo|Variable")
	float DelayInterpTime = 0.5f;

	/** * 插值时间 */
	UPROPERTY(BlueprintReadWrite, Category = "Aimo|Variable")
	float InterpTime = 0.0f;
	
public:

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	/** * */
	UFUNCTION(BlueprintCallable, Category = "Aimo|Function")
	virtual void SetNumerical(float InNumerical);

	/** * */
	UFUNCTION(BlueprintCallable, Category = "Aimo|Function")
	virtual void SetNumericalMax(float InNumerical);

	/** * */
	UFUNCTION(BlueprintCallable, Category = "Aimo|Function")
	virtual void SetExcessNumerical(float InNumerical);

	/** * */
	UFUNCTION(BlueprintCallable, Category = "Aimo|Function")
	virtual void SetNumericalProgress(float InProgress);

	/** * */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Aimo|Function")
	void BPSetProgress(uint8 InIndex, float InProgress);

	/** * */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Aimo|Function")
	void BPOnSet(uint8 InIndex);

	/** * */
	UFUNCTION(BlueprintCallable, Category = "Aimo|Function")
	virtual void NativeOnSet(uint8 InIndex);

};
