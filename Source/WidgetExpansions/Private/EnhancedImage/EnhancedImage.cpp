// Fill out your copyright notice in the Description page of Project Settings.


#include "EnhancedImage/EnhancedImage.h"

#include "UniversalFunctionLibrary/Public/UniversalFunctionLibrarys.h"
#include "UniversalFunctionLibrary/Public/Widget/UniversalWidgetFunctionLibrary.h"



void UEnhancedImage::SetMaxImageSize(const FVector2D& MaxSize)
{
	MaxImageSize = MaxSize;
	SetBrushFromResourceObject(GetBrush().GetResourceObject());
}

void UEnhancedImage::AsyncBrushFromSoftObjectPtr(const TSoftObjectPtr<UObject>& InSoftObjectPtr)
{
	TWeakObjectPtr<UEnhancedImage> WeakThis(this); // using weak ptr in case 'this' has gone out of scope by the time this lambda is called
	RequestAsyncLoad(InSoftObjectPtr,
		[WeakThis, InSoftObjectPtr]() {
			if (UEnhancedImage* StrongThis = WeakThis.Get())
			{
				ensureMsgf(InSoftObjectPtr.Get(), TEXT("Failed to load %s"), *InSoftObjectPtr.ToSoftObjectPath().ToString());
				StrongThis->SetBrushFromResourceObject(InSoftObjectPtr.Get());
				return;
			}
		}
	);
}

void UEnhancedImage::SetBrushFromSoftPath(const FString& Path, const FVector2D& MaxSize)
{
	if (MaxSize.X != 0.0f)
	{
		MaxImageSize = MaxSize;
	}
	TSoftObjectPtr<UObject> SoftObject = TSoftObjectPtr<UObject>(Path);
	if (SoftObject.IsNull() == false)
	{
		if (SoftObject.IsValid())
		{
			SetBrushFromResourceObject(SoftObject.Get());
			return;
		}
		AsyncBrushFromSoftObjectPtr(SoftObject);
	}
	return;
}

void UEnhancedImage::SetBrushFromSoftObjectPtr(const TSoftObjectPtr<UObject>& InSoftObjectPtr, const FVector2D& MaxSize)
{
	if (MaxSize.X != 0.0f)
	{
		MaxImageSize = MaxSize;
	}
	if (InSoftObjectPtr.IsNull())
	{
		return;
	}
	if (InSoftObjectPtr.Get())
	{
		SetBrushFromResourceObject(InSoftObjectPtr.Get());
		return;
	}
	AsyncBrushFromSoftObjectPtr(InSoftObjectPtr);
	return;
}

void UEnhancedImage::SetBrushFromResourceObject(UObject* Object)
{
	if (Object)
	{
		UTexture2D* Texture2D = Cast<UTexture2D>(Object);
		if (Texture2D && MaxImageSize.X != 0.0f)
		{
			SetBrushResourceObject(Object);
			FVector2D Size;
			Size.X = Texture2D->GetSizeX();
			Size.Y = Texture2D->GetSizeY();
			Size = UUniversalFunctionLibrarys::GetXYClampSize(Size.X, Size.Y, MaxImageSize.X, MaxImageSize.Y);
			if (bMaxImageSize  && Size.X < MaxImageSize.X && Size.Y < MaxImageSize.Y)
			{
				Size = Size * (MaxImageSize / Size);
			}
			UUniversalWidgetFunctionLibrary::SetWidgetSize(this, Size);
			return;
		}
		if (Cast<UTexture>(Object) || Cast<UMaterialInterface>(Object))
		{
			SetBrushResourceObject(Object);
		}
		if (MaxImageSize.X != 0.0f)
		{
			UUniversalWidgetFunctionLibrary::SetWidgetSize(this, MaxImageSize);
		}
	}
}

