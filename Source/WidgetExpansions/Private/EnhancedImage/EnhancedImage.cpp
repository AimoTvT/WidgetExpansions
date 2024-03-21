// Fill out your copyright notice in the Description page of Project Settings.


#include "EnhancedImage/EnhancedImage.h"

#include "UniversalFunctionLibrary/Public/UniversalFunctionLibrarys.h"
#include "UniversalFunctionLibrary/Public/Widget/UniversalWidgetFunctionLibrary.h"



void UEnhancedImage::SetMaxImageSize(const FVector2D& MaxSiz)
{
	MaxImageSize = MaxSiz;
	SetBrushFromResourceObject(GetBrush().GetResourceObject());
}

void UEnhancedImage::SetBrushFromSoftTextureEnhanced(TSoftObjectPtr<UTexture> SoftTexture, const FVector2D& MaxSize)
{
	TWeakObjectPtr<UImage> WeakThis(this); // using weak ptr in case 'this' has gone out of scope by the time this lambda is called
	RequestAsyncLoad(SoftTexture,
		[WeakThis, SoftTexture, MaxSize]() {
			if (UImage* StrongThis = WeakThis.Get())
			{
				ensureMsgf(SoftTexture.Get(), TEXT("Failed to load %s"), *SoftTexture.ToSoftObjectPath().ToString());
				StrongThis->SetBrushResourceObject(SoftTexture.Get());
				if (MaxSize.X != 0.0f)
				{
					UTexture2D* Texture2D = Cast<UTexture2D>(SoftTexture.Get());
					if (Texture2D)
					{
						FVector2D Size;
						Size.X = Texture2D->GetSizeX();
						Size.Y = Texture2D->GetSizeY();
						Size = UUniversalFunctionLibrarys::GetXYClampSize(Size.X, Size.Y, MaxSize.X, MaxSize.Y);
						UUniversalWidgetFunctionLibrary::SetWidgetSize(StrongThis, Size);
						return;
					}
				}
				UUniversalWidgetFunctionLibrary::SetWidgetSize(StrongThis, MaxSize);
				return;
			}
		}
	);
}

bool UEnhancedImage::SetBrushFromSoftPath(const FString& Path, const FVector2D& MaxSize)
{
	if (MaxSize.X != 0.0f)
	{
		MaxImageSize = MaxSize;
	}
	TSoftObjectPtr<UTexture> SoftTexture = TSoftObjectPtr<UTexture>(Path);
	if (SoftTexture.IsNull() == false)
	{
		if (SoftTexture.IsValid())
		{
			SetBrushFromResourceObject(SoftTexture.Get());
			return true;
		}
		SetBrushFromSoftTextureEnhanced(SoftTexture, MaxImageSize);
		return true;
	}
	TSoftObjectPtr<UMaterialInterface> SoftMaterial = TSoftObjectPtr<UMaterialInterface>(Path);
	if (SoftMaterial.IsNull() == false)
	{
		if (SoftMaterial.IsValid())
		{
			SetBrushFromResourceObject(SoftMaterial.Get());
			return true;
		}
		SetBrushFromSoftMaterial(SoftMaterial);
		UUniversalWidgetFunctionLibrary::SetWidgetSize(this, MaxImageSize);
		return true;
	}
	return false;
}

bool UEnhancedImage::SetBrushFromSoftObject(TSoftObjectPtr<UObject> SoftObjectPtr, const FVector2D& MaxSize)
{
	if (MaxSize.X != 0.0f)
	{
		MaxImageSize = MaxSize;
	}
	if (SoftObjectPtr.IsNull())
	{
		return false;
	}
	if (SoftObjectPtr.Get())
	{
		SetBrushFromResourceObject(SoftObjectPtr.Get());
		return true;
	}
	return SetBrushFromSoftPath(SoftObjectPtr.ToString(), MaxSize);
}

void UEnhancedImage::SetBrushFromResourceObject(UObject* Object)
{
	if (Object)
	{
		SetBrushResourceObject(Object); 
		UTexture2D* Texture2D = Cast<UTexture2D>(Object);
		if (Texture2D)
		{
			FVector2D Size;
			Size.X = Texture2D->GetSizeX();
			Size.Y = Texture2D->GetSizeY();
			Size = UUniversalFunctionLibrarys::GetXYClampSize(Size.X, Size.Y, MaxImageSize.X, MaxImageSize.Y);
			UUniversalWidgetFunctionLibrary::SetWidgetSize(this, Size);
			return;
		}
		UUniversalWidgetFunctionLibrary::SetWidgetSize(this, MaxImageSize);
	}
}

