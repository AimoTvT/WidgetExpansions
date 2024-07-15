// Fill out your copyright notice in the Description page of Project Settings.


#include "NumericalProgress/NumericalProgressWidget.h"

void UNumericalProgressWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	if (Numerical != InterpNumerical)
	{
		InterpNumerical = FMath::FInterpTo(InterpNumerical, Numerical, InDeltaTime, InterpSpeed);
		BPSetProgress(0, InterpNumerical / NumericalMax);

	}
	if (InterpTime <= 0.0f)
	{
		if (InterpExcessNumerical != Numerical + ExcessNumerical)
		{
			InterpExcessNumerical = FMath::FInterpTo(InterpExcessNumerical, Numerical + ExcessNumerical, InDeltaTime, InterpSpeed);
			BPSetProgress(1, InterpExcessNumerical / NumericalMax);
		}
	}
	else
	{
		InterpTime -= InDeltaTime;
	}
}

void UNumericalProgressWidget::SetNumerical(float InNumerical)
{
	if (ExcessNumerical == 0.0f && InNumerical < Numerical)
	{
		InterpTime = 0.5f;
	}
	Numerical = InNumerical;
	BPOnSet(0);
}

void UNumericalProgressWidget::SetNumericalMax(float InNumerical)
{
	NumericalMax = InNumerical;
	BPOnSet(1);
	InterpExcessNumerical += 0.2f;
	if (Numerical == InterpNumerical)
	{
		BPSetProgress(0, Numerical / NumericalMax);
	}
	if (InterpExcessNumerical == Numerical + ExcessNumerical)
	{
		BPSetProgress(0, (Numerical + ExcessNumerical) / NumericalMax);
	}
}

void UNumericalProgressWidget::SetExcessNumerical(float InNumerical)
{
	ExcessNumerical = InNumerical;
	BPOnSet(2);
}

void UNumericalProgressWidget::SetNumericalProgress(float InProgress)
{
	InterpExcessNumerical = 0.0f;
	Numerical = NumericalMax * InProgress;
	InterpNumerical = NumericalMax * InProgress;
	BPOnSet(3);
}

void UNumericalProgressWidget::BPSetProgress_Implementation(uint8 InIndex, float InProgress)
{
}


void UNumericalProgressWidget::BPOnSet_Implementation(uint8 InIndex)
{
	NativeOnSet(InIndex);
}

void UNumericalProgressWidget::NativeOnSet(uint8 InIndex)
{
}