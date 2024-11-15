// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"

#include "Config/UniversalStruct.h"

#include "WidgetExpansionsSave.generated.h"

/**
 * 
 */
UCLASS()
class WIDGETEXPANSIONS_API UWidgetExpansionsSave : public USaveGame
{
	GENERATED_BODY()
	

public:



	/** *  */
	UPROPERTY(BlueprintReadWrite, Category = "WidgetExpansionsSave")
	TArray<FStringImageData> StringImageDatas;

	/** *  */
	UPROPERTY(BlueprintReadWrite, Category = "WidgetExpansionsSave")
	int ing;


public:


};
