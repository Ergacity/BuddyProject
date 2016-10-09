// Fill out your copyright notice in the Description page of Project Settings.

#include "BuddyProject.h"
#include "PlayerCharacter.h"


//------------------------------KONSTRUKCJA, BEGINPLAY, INPUT------------------------------
APlayerCharacter::APlayerCharacter(const FObjectInitializer& ObjectInitializer)
{
	GetCapsuleComponent()->SetCapsuleHalfHeight(83.f);
	bUseControllerRotationYaw = false;
	SprintSpeedModifier = 1.5f;
	MovementBasicSpeed = GetCharacterMovement()->MaxWalkSpeed;

	SpringComp = ObjectInitializer.CreateDefaultSubobject<USpringArmComponent>(this, TEXT("SpringArm Component"));
	SpringComp->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	SpringComp->bEnableCameraLag = true;
	SpringComp->CameraLagMaxDistance = 50.f;
	SpringComp->CameraLagSpeed = 5.f;
	SpringComp->bInheritYaw = false;
	SpringComp->RelativeRotation = FRotator(0.f, -15.f, -90.f);
	SpringComp->RelativeLocation = FVector(0.f, 0.f, 50.f);
	SpringComp->TargetArmLength = 1000.f;

	CameraComp = ObjectInitializer.CreateDefaultSubobject<UCameraComponent>(this, TEXT("Camera Component"));
	CameraComp->AttachToComponent(SpringComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	SetCanDoubleJump(true);
	bIsCrouching = false;
	bIsSprinting = false;
}

void APlayerCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	InputComponent->BindAxis("MoveX", this, &APlayerCharacter::MoveX);

	InputComponent->BindAction("Crouch", IE_Pressed, this, &APlayerCharacter::OnCrouchStart);
	InputComponent->BindAction("Crouch", IE_Released, this, &APlayerCharacter::OnCrouchEnd);
	InputComponent->BindAction("Jump", IE_Pressed, this, &APlayerCharacter::OnJumpStart);
	InputComponent->BindAction("Jump", IE_Released, this, &APlayerCharacter::OnJumpEnd);
	InputComponent->BindAction("Sprint", IE_Pressed, this, &APlayerCharacter::OnSprintStart);
	InputComponent->BindAction("Sprint", IE_Released, this, &APlayerCharacter::OnSprintEnd);
}
//------------------------------TICK------------------------------
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick( DeltaTime );

}
//------------------------------MOVEMENT------------------------------
void APlayerCharacter::MoveX(float Val)
{
	if (GetController() && Val != 0.f) //Upewnijmy siê, ¿e mamy controller który bêdzie nas chodzi³ i czy w³aœciwie musimy siê ruszaæ
	{
		FVector Dir = GetControlRotation().Vector(); //sprawdzamy swoja rotacje by wiedziec gdzie isc
		AddMovementInput(Dir, Val);
	}
}

void APlayerCharacter::Landed(const FHitResult& Hit)
{
	SetCanDoubleJump(true);
}

void APlayerCharacter::OnCrouchStart()
{
	if (GetCharacterMovement()->IsMovingOnGround()) //Sprawdzamy, czy nie kucamy w powietrzu
	{
		Crouch();
		bIsCrouching = true;
	}
}

void APlayerCharacter::OnCrouchEnd()
{
	UnCrouch();
	bIsCrouching = false;
}

void APlayerCharacter::OnJumpStart()
{
	if (GetCharacterMovement()->IsMovingOnGround()) //Sprawdzamy, czy nie skaczemy z powietrza
		bPressedJump = true;
	else if (!GetCharacterMovement()->IsMovingOnGround() && GetCanDoubleJump()) //Jeœli skaczemy z powietrza, ale mo¿emy double jumpowaæ
	{
		GetCharacterMovement()->Velocity = FVector(0.f, 0.f, 0.f); //Zerujemy prêdkoœæ, ¿eby móc lepiej kontrolowaæ drugi skok
		bPressedJump = true;
		SetCanDoubleJump(false);
	}
}

void APlayerCharacter::OnJumpEnd()
{
	bPressedJump = false;
}

void APlayerCharacter::OnSprintStart()
{
	if (GetCharacterMovement()->IsMovingOnGround()) //Nie mo¿emy sprintowaæ w powietrzu...
	{
		if (GetIsCrouching()) //Jeœli kucamy, to wstajemy
			OnCrouchEnd();

		GetCharacterMovement()->MaxWalkSpeed = MovementBasicSpeed * SprintSpeedModifier; //Przyœpieszamy movement
		bIsSprinting = true;
	}
}

void APlayerCharacter::OnSprintEnd()
{
	GetCharacterMovement()->MaxWalkSpeed = MovementBasicSpeed;
	bIsSprinting = false;
}