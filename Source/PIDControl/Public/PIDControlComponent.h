
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "PIDControlComponent.generated.h"

USTRUCT(BlueprintType)
struct FPIDError {
    GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
    float Value;

    UPROPERTY(BlueprintReadWrite)
    float DeltaTime;
    
    FPIDError() {
        Value = 0.0f;
        DeltaTime = 0.0f;
    }
    
    FPIDError(const float MeasuredValue, const float DeltaTime) {
        this->Value = MeasuredValue;
        this->DeltaTime = DeltaTime;
    }
};

/** 
 * PID Controller actor component
 */
UCLASS(BlueprintType, Blueprintable, meta=(BlueprintSpawnableComponent))
class UPIDControl final : public UActorComponent
{
	GENERATED_UCLASS_BODY()

    // Minimum of 3 errors need to be stored
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=PIDControl)
    int32 ErrorCacheSize;

	// Proportional coefficient is responsible for how fast error should be corrected
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=PIDControl)
    float ProportionalCoefficient;

	// Integral coefficient is responsible for correcting systematic errors of measurement over time
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=PIDControl)
    float IntegralCoefficient;

    // Derivative coefficient is responsible for correcting oscillation introduced by derivative coefficient
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=PIDControl)
    float DerivativeCoefficient;

    // Queue of PID error measurements
    UPROPERTY(BlueprintReadOnly, Category=PIDControl)
    TArray<FPIDError> MeasuredErrors;

	// Add a single float error measurement with the world delta seconds
	UFUNCTION(BlueprintCallable, Category="PIDControl")
    void AddMeasuredError(FPIDError Error);

	// Supplies the coefficient based on the combined results of the Proportional, Integral and Derivative
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="PIDControl")
    void GetControlCoefficient(float &Result);

	// Clear the measured errors list
	UFUNCTION(BlueprintCallable, Category="PIDControl")
    void ResetController();
};
