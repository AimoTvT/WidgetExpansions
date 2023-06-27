// Fill out your copyright notice in the Description page of Project Settings.


#include "PictureSequence/PictureSequence.h"


void UPictureSequence::InitWidget(TArray<UTexture2D*> OTexture2Ds, float OFramesPerSecond, int OTexture2DsIndex)
{
	FramesPerSecond = OFramesPerSecond;
	Texture2DsIndex = OTexture2DsIndex;
	Texture2Ds = OTexture2Ds;

	if (Texture2Ds.Num())
	{
		GetWorld()->GetTimerManager().SetTimer(FPSTimerHandle, this, &UPictureSequence::OnFPSTimerHandle, 1 / FramesPerSecond, true);
	}
}

void UPictureSequence::OnFPSTimerHandle()
{
	if (ImageWidget && Texture2Ds[Texture2DsIndex])
	{
		ImageWidget->SetBrushFromTexture(Texture2Ds[Texture2DsIndex],true);
	}
	if (bPictureEndRem && Texture2DsIndex + 1 == Texture2Ds.Num())
	{
		RemoveFromParent(); /** 从父类移除 */
	}
	else
	{
		Texture2DsIndex = (Texture2DsIndex + 1) % Texture2Ds.Num();
	}
}
