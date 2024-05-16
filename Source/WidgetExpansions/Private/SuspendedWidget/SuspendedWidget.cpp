/**
 * Copyright: Aimo_皑墨
 * Open Source Date: Jun 27, 2023
 * BiLiBiLi (哔哩哔哩) address: https://space.bilibili.com/146962867
 * Open source address(Git): https://github.com/AimoTvT/WidgetExpansions
 * We welcome the contributions of powerful movers and movers to join this plugin
 * Build powerful plugins together!!
 *
 * 版权所有权: Aimo_皑墨
 * 开源时间: 2023年6月27日
 * BiLiBiLi(哔哩哔哩)地址: https://space.bilibili.com/146962867
 * 开源地址(Git): https://github.com/AimoTvT/WidgetExpansions
 * 欢迎有实力的大佬/萌新加入本插件的贡献
 * 一起打造强大的插件!!!
 */


#include "SuspendedWidget/SuspendedWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Animation/WidgetAnimation.h"


bool USuspendedWidget::Initialize()
{
	bool InitializeT = Super::Initialize();
	AnimTimer = 0.5;
	Location = FVector(0.0f, 0.0f, 40.0f);
	EndLocation = FVector(0.0f, 0.0f, 40.0f);
	return InitializeT;
}

void USuspendedWidget::NativeConstruct()
{
	Super::NativeConstruct();
	AddDestructTimer(2.2); /** * 添加销毁时间 */
	SuspendedPlayAnimation(TEXT("Play"));  /** * 播放开始动画 */
	if (!GetWorld()->GetTimerManager().IsTimerActive(TimerHandle))
	{
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &USuspendedWidget::TimerHandleLocation, 0.02f, true); /** * 启动设置位置定时器 */
	}
}

void USuspendedWidget::SetSuspended(const FString& String, const FVector& LocationT, const FVector& EndLocationT, TSoftObjectPtr<UObject> Image, const FVector2D& ImageSize)
{
	Location = LocationT;
	EndLocation = EndLocationT;
	SetImage(Image, ImageSize); /** * 设置图像 */
	if (GetWorld() && GetWorld()->GetFirstPlayerController() && GetWorld()->GetFirstPlayerController()->PlayerCameraManager)
	{
		float Size = FVector::Distance(LocationT, GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetCameraLocation()); /** * 计算摄像机和目标的距离 */
		Size = 1 - FMath::Clamp(Size * 0.22 * 0.001, 0.0, 0.6);
		SetRenderTransform(FWidgetTransform{ {0.0f, 0.0f},{Size,Size},{0.0f, 0.0f},0.0f }); /** * 设置变换 */
	}
	if (TextBlockWidget)
	{
		TextBlockWidget->SetText(FText::FromString(String));
	}
}

void USuspendedWidget::SetSuspendedOffset(const FString& String, const FVector& LocationT, FVector OffsetLocationT, TSoftObjectPtr<UObject> Image, FVector2D ImageSize)
{
	return SetSuspended(String, LocationT, LocationT + OffsetLocationT, Image, ImageSize);
}

void USuspendedWidget::TimerHandleLocation() /** * 定时器0.02秒设置三维到屏幕位置 */
{
	if (Location != EndLocation)
	{
		FVector2D OffsetT;
		Location = FMath::VInterpTo(Location, EndLocation, 0.02f, AnimTimer);
		if (UWidgetLayoutLibrary::ProjectWorldLocationToWidgetPosition(GetOwningPlayer(), Location, OffsetT, bPlayerViewportRelative))
		{
			if (GetVisibility() != ESlateVisibility::Visible)
			{
				SetVisibility(ESlateVisibility::Visible);
			}
			OffsetT = (OffsetT + GetDesiredSize() * -0.5 + Offset) * UWidgetLayoutLibrary::GetViewportScale(this);
			SetPositionInViewport(OffsetT);/** * 计算完整偏移,并设置位置 */
		}
		else
		{
			if (GetVisibility() != ESlateVisibility::Hidden)
			{
				SetVisibility(ESlateVisibility::Hidden);
			}
		}
	}
	return;
}

void USuspendedWidget::SetImage(TSoftObjectPtr<UObject> SoftObject, FVector2D ImageSize) /** * 设置图像 */
{
	if (SoftObject.IsValid())
	{
		TSoftObjectPtr<UTexture2D> SoftObjectPtrTexture2D;
		SoftObjectPtrTexture2D = SoftObject.ToString();
		if (SoftObjectPtrTexture2D.IsValid())
		{
			ImageWidget->SetBrushFromSoftTexture(SoftObjectPtrTexture2D);
			if (SizeBoxWidget)
			{
				SizeBoxWidget->SetWidthOverride(ImageSize.X);
				SizeBoxWidget->SetHeightOverride(ImageSize.Y);
			}
			return;
		}
		else
		{
			TSoftObjectPtr<UMaterialInterface> SoftObjectPtrMaterialInterface;
			SoftObjectPtrMaterialInterface = SoftObject.ToString();
			if (SoftObjectPtrMaterialInterface.IsValid())
			{
				ImageWidget->SetBrushFromSoftMaterial(SoftObjectPtrMaterialInterface);
				if (SizeBoxWidget)
				{
					SizeBoxWidget->SetWidthOverride(ImageSize.X);
					SizeBoxWidget->SetHeightOverride(ImageSize.Y);
				}
				return;
			}
			else
			{
				if (SizeBoxWidget)
				{
					SizeBoxWidget->SetWidthOverride(0);
					SizeBoxWidget->SetHeightOverride(0);
				}
			}
		}
	}
	else
	{
		if (SizeBoxWidget)
		{
			SizeBoxWidget->SetWidthOverride(0);
			SizeBoxWidget->SetHeightOverride(0);
		}
	}
}

void USuspendedWidget::AddDestructTimer(float Timer) /** * 添加销毁时间 */
{
	DestructTimer += Timer;
	if (DestructTimer > 0)
	{
		if (!GetWorld()->GetTimerManager().IsTimerActive(DestructTimerHandle))
		{
			GetWorld()->GetTimerManager().SetTimer(DestructTimerHandle, this, &USuspendedWidget::NativeDestructTimerHandle, 0.2f, true);
		}
	}
	else
	{
		if (GetWorld()->GetTimerManager().IsTimerActive(DestructTimerHandle))
		{
			GetWorld()->GetTimerManager().ClearTimer(DestructTimerHandle);
		}
		SuspendedPlayAnimation(TEXT("Des")); /** * 播放销毁动画 */
	}
}

void USuspendedWidget::SuspendedPlayAnimation(const FString& String)
{
	UObject* Object;
	FObjectProperty* ObjectProperty;
	UWidgetAnimation* WidgetAnimation;
	if (String == TEXT("Des")) /** * 判断是否销毁 */
	{
		if (DestructTimer < 1.8)
		{
			return;
		}
		ObjectProperty = FindFProperty<FObjectProperty>(GetClass(), TEXT("JianBianXianShiAnimation")); //Object指针类型变量
		Object = Cast<UWidgetAnimation>(ObjectProperty->GetObjectPropertyValue_InContainer(this)); //转换Object类型
		if (Object)
		{
			WidgetAnimation = Cast<UWidgetAnimation>(Object);
			if (WidgetAnimation)
			{
				PlayAnimation(WidgetAnimation, 0.0f, 1, EUMGSequencePlayMode::Forward);
			}
		}
		return;
	}
	if (String == TEXT("Play")) /** * 判断是否开始 */
	{
		ObjectProperty = FindFProperty<FObjectProperty>(GetClass(), TEXT("BianDaAnimation")); //Object指针类型变量
		Object = Cast<UWidgetAnimation>(ObjectProperty->GetObjectPropertyValue_InContainer(this)); //转换Object类型
		if (Object)
		{
			WidgetAnimation = Cast<UWidgetAnimation>(Object);
			if (WidgetAnimation)
			{
				PlayAnimation(WidgetAnimation, 0.0f, 1, EUMGSequencePlayMode::Forward);
			}
		}
		return;
	}
}

void USuspendedWidget::NativeDestructTimerHandle()
{
	DestructTimer = DestructTimer - 0.2;
	if (DestructTimer <= 2.0)
	{
		SuspendedPlayAnimation(TEXT("Des"));
	}
	if (DestructTimer <= 0.0)
	{
		RemoveFromParent(); /** * 从父类移除 */
	}
}
