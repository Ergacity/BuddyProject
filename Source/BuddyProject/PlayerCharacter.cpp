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

	SpringComp->RelativeRotation = FRotator(-5.f, -90.f, 0.f);
	SpringComp->bDoCollisionTest = false;
	CharacterRotationSpeed = 100.f;
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	bIsSprinting = false;
	CurrentFrontYaw = GetActorRotation().Yaw;
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, FString::SanitizeFloat(CurrentFrontYaw));
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
	/*JAK SZYBKO OBRACA SI� POSTA�?*/
	float FrameRate = 1.f / DeltaTime;

	/*OBRACANIE POSTACI*/
	if (FMath::Abs(GetDesiredYawRot() - CurrentFrontYaw) > 1.f)
	{
		if (CurrentFrontYaw < DesiredYawRot)
		{
			CurrentFrontYaw += CharacterRotationSpeed * DeltaTime * FrameRate/60.f;
			GetController()->SetControlRotation(FRotator(0.f, CurrentFrontYaw, 0.f));
			SpringComp->RelativeRotation = FRotator(-15.f, -90.f + CurrentFrontYaw, 0.f);
		}
		else
		{
			CurrentFrontYaw -= CharacterRotationSpeed * DeltaTime * FrameRate / 60.f;
			GetController()->SetControlRotation(FRotator(0.f, CurrentFrontYaw, 0.f));
			SpringComp->RelativeRotation = FRotator(-15.f, -90.f + CurrentFrontYaw, 0.f);
		}
	}
}
//------------------------------MOVEMENT------------------------------
void APlayerCharacter::MoveX(float Val)
{
	if (GetController() && Val != 0.f) //Upewnijmy si�, �e mamy controller kt�ry b�dzie nas chodzi� i czy w�a�ciwie musimy si� rusza�
	{
		FRotator Rot = GetControlRotation();
		FVector Dir = Rot.Vector(); //sprawdzamy swoja rotacje by wiedziec gdzie isc
		AddMovementInput(Dir, Val);
	}
}

void APlayerCharacter::Landed(const FHitResult& Hit)
{
	SetJustLanded(true); //Aktywujemy to, �e w�a�nie wyl�dowali�my, aby m�c wezwa� zachowania przy l�dowaniu

	//Wzywamy kucanie lub sprintowanie je�li trzymali�my w powietrzu przycisk
	if (GetWantToCrouch())
		OnCrouchStart();

	if (GetWantToSprint())
		OnSprintStart();

	SetJustLanded(false); //Sko�czyli�my rzeczy od l�dowania, wi�c ju� nie jeste�my tu� po l�dowaniu
}

void APlayerCharacter::OnCrouchStart()
{
	if(!GetWantToSprint()) //Sprint nadpisuje kucanie, wi�c nie mo�emy chcie� kuca� kiedy chcemy sprintowa�
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
	SetWantToSprint(true);
	if (GetWantToCrouch()) //Sprint nadpisuje kucanie, wi�c nie mo�emy chcie� kuca� kiedy chcemy sprintowa�
		SetWantToCrouch(false);

	if (GetCharacterMovement()->IsMovingOnGround() || (GetWantToSprint() && GetJustLanded())) //Nie mo�emy sprintowa� w powietrzu... ale mo�liwe, �e wyl�dowali�my a ju� chcieli�my sprintowa�
	{
		if (bIsCrouched) //Je�li kucamy, to wstajemy
			OnCrouchEnd();

		GetCharacterMovement()->MaxWalkSpeed = MovementBasicSpeed * SprintSpeedModifier; //Przy�pieszamy movement
		bIsSprinting = true;
	}
}

void APlayerCharacter::OnSprintEnd()
{
	SetWantToSprint(false);
	GetCharacterMovement()->MaxWalkSpeed = MovementBasicSpeed;
	bIsSprinting = false;
}
