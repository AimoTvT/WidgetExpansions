// Fill out your copyright notice in the Description page of Project Settings.


#include "BackgroundImage/BackgroundImage.h"
#include "UniversalFunctionLibrarys.h"
#include "WidgetExpansionsController/WidgetExpansionsController.h"

void UBackgroundImage::OnWidgetRebuilt()
{
	Super::OnWidgetRebuilt();
	if (!IsDesignTime())
	{
		NativeConstruct();
	}
}

void UBackgroundImage::NativeConstruct()
{
	InitBackground();
}

void UBackgroundImage::InitBackground()
{
	if (Name.IsValid() && UWidgetExpansionsController::Get())
	{
		UWidgetExpansionsSave* WidgetExpansionsSave = UWidgetExpansionsController::Get()->GetWidgetExpansionsSave(0);
		if (WidgetExpansionsSave)
		{
			for (size_t i = 0; i < WidgetExpansionsSave->StringImageDatas.Num(); i++)
			{
				if (WidgetExpansionsSave->StringImageDatas[i].Name == Name && WidgetExpansionsSave->StringImageDatas[i].ImageString.Len())
				{
					FSlateBrush TSlateBrush = GetBrush();
					TSoftObjectPtr<UObject> SoftObject = TSoftObjectPtr<UObject>(WidgetExpansionsSave->StringImageDatas[i].ImageString);
					if (SoftObject.IsNull() == false)
					{
						TSlateBrush.DrawAs = WidgetExpansionsSave->StringImageDatas[i].DrawAs;
						TSlateBrush.Tiling = WidgetExpansionsSave->StringImageDatas[i].Tiling;
						TSlateBrush.ImageSize = WidgetExpansionsSave->StringImageDatas[i].ImageSize;
						TSlateBrush.Margin = WidgetExpansionsSave->StringImageDatas[i].Margin;
						TSlateBrush.TintColor = WidgetExpansionsSave->StringImageDatas[i].TintColor;
						TSlateBrush.OutlineSettings.CornerRadii.X = WidgetExpansionsSave->StringImageDatas[i].CornerRadii.Left;
						TSlateBrush.OutlineSettings.CornerRadii.Y = WidgetExpansionsSave->StringImageDatas[i].CornerRadii.Top;
						TSlateBrush.OutlineSettings.CornerRadii.Z = WidgetExpansionsSave->StringImageDatas[i].CornerRadii.Right;
						TSlateBrush.OutlineSettings.CornerRadii.W = WidgetExpansionsSave->StringImageDatas[i].CornerRadii.Bottom;
						TSlateBrush.OutlineSettings.RoundingType = ESlateBrushRoundingType::FixedRadius;
						if (SoftObject.IsValid())
						{
							TSlateBrush.SetResourceObject(SoftObject.Get());
							SetBrush(TSlateBrush);
							return;
						}
						else
						{
							SetBrush(TSlateBrush);
							AsyncBrushFromSoftObjectPtr(SoftObject);
							return;
						}
					}
					return;
				}
			}
		}
	}
}


void UBackgroundImage::AsyncBrushFromSoftObjectPtr(const TSoftObjectPtr<UObject>& InSoftObjectPtr)
{
	TWeakObjectPtr<UBackgroundImage> WeakThis(this); // using weak ptr in case 'this' has gone out of scope by the time this lambda is called
	RequestAsyncLoad(InSoftObjectPtr,
		[WeakThis, InSoftObjectPtr]() {
			if (UBackgroundImage* StrongThis = WeakThis.Get())
			{
				ensureMsgf(InSoftObjectPtr.Get(), TEXT("Failed to load %s"), *InSoftObjectPtr.ToSoftObjectPath().ToString());
				StrongThis->SetBrushFromResourceObject(InSoftObjectPtr.Get());
				return;
			}
		}
	);
}

bool UBackgroundImage::SetBrushFromSoftPath(const FString& Path)
{
	TSoftObjectPtr<UObject> SoftObject = TSoftObjectPtr<UObject>(Path);
	if (SoftObject.IsNull() == false)
	{
		if (SoftObject.IsValid())
		{
			return SetBrushFromResourceObject(SoftObject.Get());
		}
		AsyncBrushFromSoftObjectPtr(SoftObject);
		return true;
	}
	return false;
}

bool UBackgroundImage::SetBrushFromSoftObjectPtr(const TSoftObjectPtr<UObject>& InSoftObjectPtr)
{
	if (InSoftObjectPtr.IsNull())
	{
		return false;
	}
	if (InSoftObjectPtr.IsValid())
	{
		return SetBrushFromResourceObject(InSoftObjectPtr.Get());
	}
	AsyncBrushFromSoftObjectPtr(InSoftObjectPtr);
	return true;
}

bool UBackgroundImage::SetBrushFromResourceObject(UObject* Object)
{
	if (Object)
	{
		if (Cast<UTexture>(Object) || Cast<UMaterialInterface>(Object))
		{
			SetBrushResourceObject(Object);
			return true;
		}
	}
	return false;
}