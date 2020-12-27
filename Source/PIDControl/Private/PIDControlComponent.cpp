
#include "PIDControlComponent.h"

UPIDControl::UPIDControl(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = false;
	ErrorCacheSize = 5;
	ProportionalCoefficient = 0.5f;
	IntegralCoefficient = 0.5f;
	DerivativeCoefficient = 0.05f;
}

void UPIDControl::AddMeasuredError(FPIDError Error)
{
	MeasuredErrors.Insert(Error, 0);
	if (MeasuredErrors.Num() > ErrorCacheSize) {
		MeasuredErrors.RemoveAt(MeasuredErrors.Num() - 1);
	}
}

void UPIDControl::GetControlCoefficient(float &Result)
{
	Result = 0.0f;
	
	if (MeasuredErrors.Num() < 3) return;
	if (ProportionalCoefficient != 0.0f) {
		Result += (MeasuredErrors[0].Value * ProportionalCoefficient);
	}
	if (IntegralCoefficient != 0.0f) {
		float IntegralError = 0.0f;
		for (const auto Error: MeasuredErrors) {
			IntegralError += Error.Value * Error.DeltaTime;
		}
		Result += IntegralError * IntegralCoefficient;
	}
	if (DerivativeCoefficient != 0.0f) {
		Result += (MeasuredErrors[0].Value - MeasuredErrors[1].Value) / MeasuredErrors[0].DeltaTime * DerivativeCoefficient; 
	}
}

void UPIDControl::ResetController()
{
    MeasuredErrors.Empty();
}