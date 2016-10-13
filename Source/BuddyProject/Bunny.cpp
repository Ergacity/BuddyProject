// Fill out your copyright notice in the Description page of Project Settings.

#include "BuddyProject.h"
#include "Bunny.h"


ABunny::ABunny(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	GetCapsuleComponent()->SetCapsuleHalfHeight(40.f);

	bUseControllerRotationYaw = false;
	SprintSpeedModifier = 1.5f;
	MovementBasicSpeed = GetCharacterMovement()->MaxWalkSpeed;
	GetCharacterMovement()->AirControl = 0.6f;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 3000.f, 0.f);
	GetCharacterMovement()->bCanWalkOffLedgesWhenCrouching = true;
	GetCharacterMovement()->NavAgentProps.bCanCrouch = true;

	WallRepulsionForce = FVector(700.f, 0.f, 0.f);

	JumpMaxCount = 1;
	JumpMaxHoldTime = 0.4f;

	SpringComp->bEnableCameraLag = true;
	SpringComp->CameraLagMaxDistance = 50.f;
	SpringComp->CameraLagSpeed = 5.f;
	SpringComp->bInheritYaw = false;
	SpringComp->RelativeLocation = FVector(0.f, 0.f, 50.f);
	SpringComp->TargetArmLength = 800.f;

	/*Tworzy kolizje do walljumpów*/
	WallJumpFrontColl = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, "Walljump Front");
	WallJumpFrontColl->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	WallJumpFrontColl->SetBoxExtent(FVector(5.f, GetCapsuleComponent()->GetScaledCapsuleRadius(), GetCapsuleComponent()->GetScaledCapsuleHalfHeight() * 2));
	WallJumpFrontColl->RelativeLocation = FVector(GetCapsuleComponent()->GetScaledCapsuleRadius(), 0.f, 0.f);
	WallJumpFrontColl->OnComponentBeginOverlap.AddDynamic(this, &ABunny::OnFrontBeginOverlap);
	WallJumpFrontColl->OnComponentEndOverlap.AddDynamic(this, &ABunny::OnFrontEndOverlap);
	WallJumpFrontColl->SetCollisionProfileName("WallJumpPre");

	WallJumpBackColl = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, "Walljump Back");
	WallJumpBackColl->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	WallJumpBackColl->SetBoxExtent(FVector(5.f, GetCapsuleComponent()->GetScaledCapsuleRadius(), GetCapsuleComponent()->GetScaledCapsuleHalfHeight() * 2));
	WallJumpBackColl->RelativeLocation = FVector(-GetCapsuleComponent()->GetScaledCapsuleRadius(), 0.f, 0.f);
	WallJumpBackColl->OnComponentBeginOverlap.AddDynamic(this, &ABunny::OnBackBeginOverlap);
	WallJumpBackColl->OnComponentEndOverlap.AddDynamic(this, &ABunny::OnBackEndOverlap);
	WallJumpBackColl->SetCollisionProfileName("WallJumpPre");

	SetIsTouchingWallFront(false);
	SetIsTouchingWallBack(false);
}

void ABunny::OnJumpStart()
{
	if (JumpCurrentCount != JumpMaxCount && GetCharacterMovement()->IsMovingOnGround())
		Jump();
	else if (GetIsTouchingWallFront() && !GetCharacterMovement()->IsMovingOnGround())
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, "!!");
		LaunchCharacter(FVector((-GetActorForwardVector() * WallRepulsionForce.X).Size(), 0.f, GetCharacterMovement()->JumpZVelocity), true, true);
	}
	else if (GetIsTouchingWallBack() && !GetCharacterMovement()->IsMovingOnGround())
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, "!!");
		LaunchCharacter(FVector((GetActorForwardVector() * WallRepulsionForce.X).Size(), 0.f, GetCharacterMovement()->JumpZVelocity), true, true);
	}
}

//------------------------------OVERLAPY------------------------------
void ABunny::OnFrontBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFroomSweep, const FHitResult &SweepResult)
{
	SetIsTouchingWallFront(true);
}

void ABunny::OnBackBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFroomSweep, const FHitResult &SweepResult)
{
	SetIsTouchingWallBack(true);
}

void ABunny::OnFrontEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	SetIsTouchingWallFront(false);
}

void ABunny::OnBackEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	SetIsTouchingWallBack(false);
}