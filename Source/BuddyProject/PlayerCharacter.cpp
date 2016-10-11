// Fill out your copyright notice in the Description page of Project Settings.

#include "BuddyProject.h"
#include "PlayerCharacter.h"


//------------------------------KONSTRUKCJA, BEGINPLAY, INPUT------------------------------
APlayerCharacter::APlayerCharacter(const FObjectInitializer& ObjectInitializer)
{
	SpringComp = ObjectInitializer.CreateDefaultSubobject<USpringArmComponent>(this, TEXT("SpringArm Component"));
	SpringComp->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	CameraComp = ObjectInitializer.CreateDefaultSubobject<UCameraComponent>(this, TEXT("Camera Component"));
	CameraComp->AttachToComponent(SpringComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
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
	if (GetController() && Val != 0.f) //Upewnijmy si�, �e mamy controller kt�ry b�dzie nas chodzi� i czy w�a�ciwie musimy si� rusza�
	{
		FVector Dir = GetControlRotation().Vector(); //sprawdzamy swoja rotacje by wiedziec gdzie isc
		AddMovementInput(Dir, Val);
	}
}

void APlayerCharacter::Landed(const FHitResult& Hit)
{
	SetJustLanded(true); //Aktywujemy to, �e w�a�nie wyl�dowali�my, aby m�c wezwa� zachowania przy l�dowaniu

	if (GetWantToCrouch())
		OnCrouchStart();

	SetJustLanded(false); //Sko�czyli�my rzeczy od l�dowania, wi�c ju� nie jeste�my tu� po l�dowaniu
}

void APlayerCharacter::OnCrouchStart()
{
	SetWantToCrouch(true);
	if (GetCharacterMovement()->IsMovingOnGround() || (GetWantToCrouch() && GetJustLanded())) //Sprawdzamy, czy nie kucamy w powietrzu
		Crouch();
}

void APlayerCharacter::OnCrouchEnd()
{
	SetWantToCrouch(false);
	UnCrouch();
}

void APlayerCharacter::OnJumpStart()
{
	Jump();
}

void APlayerCharacter::OnJumpEnd()
{
	StopJumping();
}

void APlayerCharacter::OnSprintStart()
{
	if (GetCharacterMovement()->IsMovingOnGround()) //Nie mo�emy sprintowa� w powietrzu...
	{
		if (bIsCrouched) //Je�li kucamy, to wstajemy
			OnCrouchEnd();

		GetCharacterMovement()->MaxWalkSpeed = MovementBasicSpeed * SprintSpeedModifier; //Przy�pieszamy movement
		bIsSprinting = true;
	}
}

void APlayerCharacter::OnSprintEnd()
{
	GetCharacterMovement()->MaxWalkSpeed = MovementBasicSpeed;
	bIsSprinting = false;
}