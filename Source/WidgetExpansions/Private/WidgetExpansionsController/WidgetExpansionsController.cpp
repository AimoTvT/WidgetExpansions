// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetExpansionsController/WidgetExpansionsController.h"
#include "Kismet/GameplayStatics.h"

UWidgetExpansionsController* UWidgetExpansionsController::Get()
{
	return GetMutableDefault<UWidgetExpansionsController>();
}



UWidgetExpansionsSave* UWidgetExpansionsController::GetWidgetExpansionsSave(int32 UserIndex)
{
	if (MyWidgetExpansionsSave)
	{
		return MyWidgetExpansionsSave;
	}
	if (UGameplayStatics::DoesSaveGameExist(WidgetExpansionsSaveName, UserIndex))
	{
		USaveGame* LoadSaveGame = UGameplayStatics::LoadGameFromSlot(WidgetExpansionsSaveName, UserIndex);
		if (LoadSaveGame)
		{
			MyWidgetExpansionsSave = Cast<UWidgetExpansionsSave>(LoadSaveGame);
			if (MyWidgetExpansionsSave)
			{
				MyWidgetExpansionsSave->AddToRoot();
				return MyWidgetExpansionsSave;
			}
			else
			{
				LoadSaveGame->RemoveFromRoot();
				LoadSaveGame->ConditionalBeginDestroy();
			}
			UGameplayStatics::DeleteGameInSlot(WidgetExpansionsSaveName, UserIndex);
		}
	}
	USaveGame* SaveGame = UGameplayStatics::CreateSaveGameObject(UWidgetExpansionsSave::StaticClass());
	if (SaveGame)
	{
		UGameplayStatics::SaveGameToSlot(SaveGame, WidgetExpansionsSaveName, UserIndex);
		MyWidgetExpansionsSave = Cast<UWidgetExpansionsSave>(SaveGame);
		if (MyWidgetExpansionsSave)
		{
			MyWidgetExpansionsSave->AddToRoot();
		}
		else
		{
			SaveGame->RemoveFromRoot();
			SaveGame->ConditionalBeginDestroy();
		}
	}
	return MyWidgetExpansionsSave;
}

bool UWidgetExpansionsController::SaveWidgetExpansionsSave(UWidgetExpansionsSave* InSettingSave, int32 UserIndex)
{
	if (InSettingSave)
	{
		return UGameplayStatics::SaveGameToSlot(InSettingSave, WidgetExpansionsSaveName, UserIndex);
	}
	return false;
}