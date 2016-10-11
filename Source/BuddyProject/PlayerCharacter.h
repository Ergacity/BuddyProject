// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class BUDDYPROJECT_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter(const FObjectInitializer& ObjectInitializer);
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	/*Ustala ile razy szybciej siê biega ze sprintem*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
		float SprintSpeedModifier;

	/*GETTERY*/
	UFUNCTION(BlueprintCallable, Category = "Movement")
		bool GetWantToCrouch() { return bWantToCrouch; };
	UFUNCTION(BlueprintCallable, Category = "Movement")
		bool GetIsSprinting() { return bIsSprinting; };
	UFUNCTION(BlueprintCallable, Category = "Movement")
		bool GetJustLanded() { return bJustLanded; };
	/*SETTERY*/
	UFUNCTION(BlueprintCallable, Category = "Movement")
		void SetWantToCrouch(bool Val) { bWantToCrouch = Val; };
	UFUNCTION(BlueprintCallable, Category = "Movement")
		void SetJustLanded(bool Val) { bJustLanded = Val; };

protected:
	/*Spring arm, na którym bêdzie trzyma³a siê kamera*/
	UPROPERTY(EditDefaultsOnly, Category = "Camera")
		USpringArmComponent* SpringComp;
	/*Kamera, któr¹ bêdzie patrzy³ gracz*/
	UPROPERTY(EditDefaultsOnly, Category = "Camera")
		UCameraComponent* CameraComp;
	/*Sprawdza, czy kucamy*/
	UPROPERTY()
		bool bWantToCrouch;
	/*Prawda, jeœli dopiero co wyl¹dowaliœmy*/
	UPROPERTY()
		bool bJustLanded;
	/*Sprawdza, czy sprintujemy*/
	UPROPERTY()
		bool bIsSprinting;
	/*Zapamiêtuje podstaw¹ prêdkoœæ postaci*/
	UPROPERTY()
		float MovementBasicSpeed;

	/*Wzywana do poruszania postaci na lewo i prawo
	@param Val - Dawana przez input waroœæ w przedziale <-1, 1>, która okreœla kierunek i si³ê ruchu
	*/
	UFUNCTION(BlueprintCallable, Category = "Movement")
		void MoveX(float Val);
	/*Wzywana gdy gracz wyl¹duje
	@param Hit - zwraca miejsce l¹dowania
	*/
	UFUNCTION(BlueprintCallable, Category = "Movement")
		void Landed(const FHitResult& Hit);
	/*Wzywane kiedy siê przyciœnie kucanie, oraz puœci kucanie*/
	UFUNCTION(BlueprintCallable, Category = "Movement")
		void OnCrouchStart();
	UFUNCTION(BlueprintCallable, Category = "Movement")
		void OnCrouchEnd();
	/*Wzywane kiedy siê przyciœnie skok, oraz puœci skok*/
	UFUNCTION(BlueprintCallable, Category = "Movement")
		virtual void OnJumpStart();
	UFUNCTION(BlueprintCallable, Category = "Movement")
		void OnJumpEnd();
	/*Wzywane kiedy siê przyciœnie sprint, oraz puœci sprint*/
	UFUNCTION(BlueprintCallable, Category = "Movement")
		void OnSprintStart();
	UFUNCTION(BlueprintCallable, Category = "Movement")
		void OnSprintEnd();

private:

};
