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

	/*Ustala ile razy szybciej si� biega ze sprintem*/
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
	/*Spring arm, na kt�rym b�dzie trzyma�a si� kamera*/
	UPROPERTY(EditDefaultsOnly, Category = "Camera")
		USpringArmComponent* SpringComp;
	/*Kamera, kt�r� b�dzie patrzy� gracz*/
	UPROPERTY(EditDefaultsOnly, Category = "Camera")
		UCameraComponent* CameraComp;
	/*Sprawdza, czy kucamy*/
	UPROPERTY()
		bool bWantToCrouch;
	/*Prawda, je�li dopiero co wyl�dowali�my*/
	UPROPERTY()
		bool bJustLanded;
	/*Sprawdza, czy sprintujemy*/
	UPROPERTY()
		bool bIsSprinting;
	/*Zapami�tuje podstaw� pr�dko�� postaci*/
	UPROPERTY()
		float MovementBasicSpeed;

	/*Wzywana do poruszania postaci na lewo i prawo
	@param Val - Dawana przez input waro�� w przedziale <-1, 1>, kt�ra okre�la kierunek i si�� ruchu
	*/
	UFUNCTION(BlueprintCallable, Category = "Movement")
		void MoveX(float Val);
	/*Wzywana gdy gracz wyl�duje
	@param Hit - zwraca miejsce l�dowania
	*/
	UFUNCTION(BlueprintCallable, Category = "Movement")
		void Landed(const FHitResult& Hit);
	/*Wzywane kiedy si� przyci�nie kucanie, oraz pu�ci kucanie*/
	UFUNCTION(BlueprintCallable, Category = "Movement")
		void OnCrouchStart();
	UFUNCTION(BlueprintCallable, Category = "Movement")
		void OnCrouchEnd();
	/*Wzywane kiedy si� przyci�nie skok, oraz pu�ci skok*/
	UFUNCTION(BlueprintCallable, Category = "Movement")
		virtual void OnJumpStart();
	UFUNCTION(BlueprintCallable, Category = "Movement")
		void OnJumpEnd();
	/*Wzywane kiedy si� przyci�nie sprint, oraz pu�ci sprint*/
	UFUNCTION(BlueprintCallable, Category = "Movement")
		void OnSprintStart();
	UFUNCTION(BlueprintCallable, Category = "Movement")
		void OnSprintEnd();

private:

};
