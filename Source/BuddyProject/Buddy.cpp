// Fill out your copyright notice in the Description page of Project Settings.

#include "BuddyProject.h"
#include "Buddy.h"

ABuddy::ABuddy(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	GetCapsuleComponent()->SetCapsuleHalfHeight(83.f);

	bUseControllerRotationYaw = false;
	SprintSpeedModifier = 1.5f;
	MovementBasicSpeed = GetCharacterMovement()->MaxWalkSpeed;
	GetCharacterMovement()->AirControl = 0.6f;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 3000.f, 0.f);
	GetCharacterMovement()->bCanWalkOffLedgesWhenCrouching = true;
	GetCharacterMovement()->NavAgentProps.bCanCrouch = true;

	JumpMaxCount = 2;
	JumpMaxHoldTime = 0.3f;

	SpringComp->bEnableCameraLag = true;
	SpringComp->CameraLagMaxDistance = 50.f;
	SpringComp->CameraLagSpeed = 5.f;
	SpringComp->bInheritYaw = false;
	SpringComp->RelativeLocation = FVector(0.f, 0.f, 50.f);
	SpringComp->TargetArmLength = 1000.f;
}


