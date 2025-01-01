// MaxEstLa - Blood Rush - ALL RIGHTS RESERVED 2022-2025

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OscillatingMovementComponent.generated.h"

UENUM(BlueprintType, meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))
enum class EOscillatingLocationAxis : uint8
{
	NONE		= 0 UMETA(Hidden),
	UseLocal	= 1 << 0,
	AffectX		= 1 << 1,
	AffectY		= 1 << 2,
	AffectZ		= 1 << 3,
};

UENUM(BlueprintType, meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))
enum class EOscillatingRotationAxis : uint8
{
	NONE		= 0 UMETA(Hidden),
	UseLocal	= 1 << 0 UMETA(Hidden),
	AffectPitch	= 1 << 1,
	AffectYaw	= 1 << 2,
	AffectRoll	= 1 << 3,
};

UCLASS(ClassGroup=(Movement), meta=(BlueprintSpawnableComponent))
class OSCILLATINGMOVEMENT_API UOscillatingMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UOscillatingMovementComponent();
	
	UPROPERTY(EditAnywhere, meta = (Bitmask, BitmaskEnum = "EOscillatingLocationAxis"))
	uint8 LocationOscillationFlags;

	UPROPERTY(EditAnywhere, meta = (Bitmask, BitmaskEnum = "EOscillatingRotationAxis"))
	uint8 RotationOscillationFlags;
	
	UPROPERTY(EditAnywhere, Category = "OscillatingMovement | X", meta = (EditConditionHides, EditCondition="LocationOscillationFlags > 0"))
	float Amplitude_X = 1.f;
	
	UPROPERTY(EditAnywhere, Category = "OscillatingMovement | X", meta = (EditConditionHides, EditCondition="LocationOscillationFlags > 0"))
	float Offset_X = 0.f;

	UPROPERTY(EditAnywhere, Category = "OscillatingMovement | X", meta = (EditConditionHides, EditCondition="LocationOscillationFlags > 0"))
	float Frequency_Y = 1.f;

	UPROPERTY(EditAnywhere, Category = "OscillatingMovement | Y", meta = (EditConditionHides, EditCondition="LocationOscillationFlags > 0"))
	float Amplitude_Y = 1.f;
	
	UPROPERTY(EditAnywhere, Category = "OscillatingMovement | Y", meta = (EditConditionHides, EditCondition="LocationOscillationFlags > 0"))
	float Offset_Y = 0.f;
	
	UPROPERTY(EditAnywhere, Category = "OscillatingMovement | Y", meta = (EditConditionHides, EditCondition="LocationOscillationFlags > 0"))
	float Frequency_X = 1.f;

	UPROPERTY(EditAnywhere, Category = "OscillatingMovement | Z", meta = (EditConditionHides, EditCondition="LocationOscillationFlags > 0"))
	float Amplitude_Z = 1.f;
	
	UPROPERTY(EditAnywhere, Category = "OscillatingMovement | Z", meta = (EditConditionHides, EditCondition="LocationOscillationFlags > 0"))
	float Offset_Z = 0.f;

	UPROPERTY(EditAnywhere, Category = "OscillatingMovement | Z", meta = (EditConditionHides, EditCondition="LocationOscillationFlags > 0"))
	float Frequency_Z = 1.f;

	UPROPERTY(EditAnywhere, Category = "OscillatingMovement | Pitch", meta = (EditConditionHides, EditCondition="RotationOscillationFlags > 0"))
	float Amplitude_Pitch = 1.f;
	
	UPROPERTY(EditAnywhere, Category = "OscillatingMovement | Pitch", meta = (EditConditionHides, EditCondition="RotationOscillationFlags > 0"))
	float Offset_Pitch = 0.f;

	UPROPERTY(EditAnywhere, Category = "OscillatingMovement | Pitch", meta = (EditConditionHides, EditCondition="RotationOscillationFlags > 0"))
	float Frequency_Pitch = 1.f;

	UPROPERTY(EditAnywhere, Category = "OscillatingMovement | Yaw", meta = (EditConditionHides, EditCondition="RotationOscillationFlags > 0"))
	float Amplitude_Yaw = 1.f;
	
	UPROPERTY(EditAnywhere, Category = "OscillatingMovement | Yaw", meta = (EditConditionHides, EditCondition="RotationOscillationFlags > 0"))
	float Offset_Yaw = 0.f;

	UPROPERTY(EditAnywhere, Category = "OscillatingMovement | Yaw", meta = (EditConditionHides, EditCondition="RotationOscillationFlags > 0"))
	float Frequency_Yaw = 1.f;

	UPROPERTY(EditAnywhere, Category = "OscillatingMovement | Roll", meta = (EditConditionHides, EditCondition="RotationOscillationFlags > 0"))
	float Amplitude_Roll = 1.f;
	
	UPROPERTY(EditAnywhere, Category = "OscillatingMovement | Roll", meta = (EditConditionHides, EditCondition="RotationOscillationFlags > 0"))
	float Offset_Roll = 0.f;

	UPROPERTY(EditAnywhere, Category = "OscillatingMovement | Roll", meta = (EditConditionHides, EditCondition="RotationOscillationFlags > 0"))
	float Frequency_Roll = 1.f;

	UPROPERTY(EditAnywhere, Category = "OscillatingMovement | Optimisation")
	bool UpdateWhenOffScreen = false;

	//If false, then we use the world time
	UPROPERTY(EditAnywhere, Category = "OscillatingMovement | Misc")
	bool UseOwnerTime = true;

	UFUNCTION(BlueprintCallable, Category = "OscillatingMovement | Setup")
	void SetUpdatedComponent(USceneComponent* NewUpdatedComponent = nullptr);

	UFUNCTION(BlueprintNativeEvent, Category= "OscillatingMovement | Math")
	float LocationOscillationEquation(const float Time) const;

	UFUNCTION(BlueprintNativeEvent, Category= "OscillatingMovement | Math")
	float RotationOscillationEquation(const float Time) const;

	
	float GetXLocationOffset() const;
	float GetYLocationOffset() const;
	float GetZLocationOffset() const;
	
	FVector GetLocationOffset() const;

	float GetPitchRotationOffset() const;
	float GetYawRotationOffset() const;
	float GetRollRotationOffset() const;
	
	FRotator GetRotationOffset() const;
	
protected:
	virtual void BeginPlay() override;

	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY()
	USceneComponent* UpdatedComponent = nullptr;

	FVector BaseLocation = FVector();
	FRotator BaseRotation = FRotator();

	USceneComponent* GetComponentToUpdate() const;

	bool ShouldUpdateComponent() const;

	bool HasLocationBitFlag(const EOscillatingLocationAxis BitFlag) const
	{
		return LocationOscillationFlags & static_cast<uint8>(BitFlag);
	}

	bool HasRotationBitFlag(const EOscillatingRotationAxis BitFlag) const
	{
		return RotationOscillationFlags & static_cast<uint8>(BitFlag);
	}

	float GetTime() const
	{
		return UseOwnerTime ? GetOwner()->GetGameTimeSinceCreation() : GetWorld()->GetTimeSeconds();
	}
};
