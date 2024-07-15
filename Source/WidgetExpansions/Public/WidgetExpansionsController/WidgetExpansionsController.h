// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SaveGames/WidgetExpansionsSave.h"

#include "WidgetExpansionsController.generated.h"

/**
 * 
 */
UCLASS()
class WIDGETEXPANSIONS_API UWidgetExpansionsController : public UObject
{
	GENERATED_BODY()
	

public:

	UFUNCTION(BlueprintPure, DisplayName = "WidgetExpansionsController")
	static UWidgetExpansionsController* Get();

	/** *  */
	UPROPERTY(BlueprintReadWrite, Category = "WidgetExpansionsController")
	TObjectPtr<UWidgetExpansionsSave> MyWidgetExpansionsSave;
	
	/** *  */
	UPROPERTY(BlueprintReadWrite, Category = "WidgetExpansionsController")
	FString WidgetExpansionsSaveName = TEXT("WidgetExpansionsSave");

	


public:

	/** *  */
	UFUNCTION(BlueprintCallable, Category = "WidgetExpansionsController|Function")
	UWidgetExpansionsSave* GetWidgetExpansionsSave(int32 UserIndex);

	/** *  */
	UFUNCTION(BlueprintCallable, Category = "WidgetExpansionsController|Function")
	bool SaveWidgetExpansionsSave(UWidgetExpansionsSave* InSettingSave, int32 UserIndex);



};
