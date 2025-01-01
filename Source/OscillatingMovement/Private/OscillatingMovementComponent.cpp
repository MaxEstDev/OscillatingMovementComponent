// MaxEstLa - Oscillating Movement Component - ALL RIGHTS RESERVED 2025


#include "OscillatingMovementComponent.h"


UOscillatingMovementComponent::UOscillatingMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	bAutoActivate = true;

}


void UOscillatingMovementComponent::SetUpdatedComponent(USceneComponent* NewUpdatedComponent)
{
	if (NewUpdatedComponent)
	{
		UpdatedComponent = NewUpdatedComponent;
		BaseLocation = NewUpdatedComponent->GetRelativeLocation();
		BaseRotation = NewUpdatedComponent->GetRelativeRotation();
	}
}

float UOscillatingMovementComponent::LocationOscillationEquation_Implementation(const float Time) const
{
	return FMath::Sin(Time);
}

float UOscillatingMovementComponent::RotationOscillationEquation_Implementation(const float Time) const
{
	return FMath::Cos(Time);
}

float UOscillatingMovementComponent::GetXLocationOffset() const
{
	return LocationOscillationEquation( GetTime() * Frequency_X + Offset_X) * Amplitude_X;
}

float UOscillatingMovementComponent::GetYLocationOffset() const
{
	return LocationOscillationEquation( GetTime() * Frequency_Y + Offset_Y) * Amplitude_Y;
}

float UOscillatingMovementComponent::GetZLocationOffset() const
{
	return LocationOscillationEquation( GetTime() * Frequency_Z + Offset_Z) * Amplitude_Z;
}

FVector UOscillatingMovementComponent::GetLocationOffset() const
{
	FVector Location = FVector::ZeroVector;

	if (HasLocationBitFlag(EOscillatingLocationAxis::AffectX)) //check X
	{
		Location.X = GetXLocationOffset();
	}

	if (HasLocationBitFlag(EOscillatingLocationAxis::AffectY)) //check Y
	{
		Location.Y = GetYLocationOffset();
	}

	if (HasLocationBitFlag(EOscillatingLocationAxis::AffectZ)) //check Z
	{
		Location.Z = GetZLocationOffset();
	}
	
	if (HasLocationBitFlag(EOscillatingLocationAxis::UseLocal))
	{
		Location = GetComponentToUpdate()->GetComponentRotation().RotateVector(Location);
	}
	
	return Location;
}

float UOscillatingMovementComponent::GetPitchRotationOffset() const
{
	return RotationOscillationEquation( GetTime() * Frequency_Pitch + Offset_Pitch) * Amplitude_Pitch;
}

float UOscillatingMovementComponent::GetYawRotationOffset() const
{
	return RotationOscillationEquation( GetTime() * Frequency_Yaw + Offset_Yaw) * Amplitude_Yaw;
}

float UOscillatingMovementComponent::GetRollRotationOffset() const
{
	return RotationOscillationEquation( GetTime() * Frequency_Roll + Offset_Roll) * Amplitude_Roll;
}

FRotator UOscillatingMovementComponent::GetRotationOffset() const
{
	FRotator Rotation = FRotator::ZeroRotator;

	if (HasRotationBitFlag(EOscillatingRotationAxis::AffectPitch))
	{
		Rotation.Pitch = GetPitchRotationOffset();
	}

	if (HasRotationBitFlag(EOscillatingRotationAxis::AffectYaw))
	{
		Rotation.Yaw = GetYawRotationOffset();
	}

	if (HasRotationBitFlag(EOscillatingRotationAxis::AffectRoll))
	{
		Rotation.Roll = GetRollRotationOffset();
	}

	
	return Rotation;
}

// Called when the game starts
void UOscillatingMovementComponent::BeginPlay()
{
	BaseLocation = GetOwner()->GetActorLocation();
	BaseRotation = GetOwner()->GetActorRotation();
	Super::BeginPlay();
}


// Called every frame
void UOscillatingMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                                  FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!ShouldUpdateComponent())
	{
		return;
	}
	
	const FVector FrameLocationOffset = GetLocationOffset();
	const FRotator FrameRotationOffset = GetRotationOffset();
	
	if (FrameLocationOffset != FVector::ZeroVector && FrameRotationOffset != FRotator::ZeroRotator)
	{
		GetComponentToUpdate()->SetRelativeLocationAndRotation(FrameLocationOffset + BaseLocation, FrameRotationOffset + BaseRotation);
	}
	else
	{
		if (FrameLocationOffset != FVector::ZeroVector)
		{
			GetComponentToUpdate()->SetRelativeLocation(FrameLocationOffset + BaseLocation);
		}
		else if (FrameRotationOffset != FRotator::ZeroRotator)
		{
			GetComponentToUpdate()->SetRelativeRotation(FrameRotationOffset + BaseRotation);
		}
	}
}

USceneComponent* UOscillatingMovementComponent::GetComponentToUpdate() const
{
	return UpdatedComponent ? UpdatedComponent : GetOwner()->GetRootComponent();
}

bool UOscillatingMovementComponent::ShouldUpdateComponent() const
{
	return !GetComponentToUpdate()->ShouldRender() || !UpdateWhenOffScreen && IsActive();
}

