// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PlayerCharacter.h"
#include "Bunny.generated.h"

/**
 * 
 */
UCLASS()
class BUDDYPROJECT_API ABunny : public APlayerCharacter
{
	GENERATED_BODY()
	
	ABunny(const FObjectInitializer& ObjectInitializer);
	virtual void OnJumpStart() override;

public:
	/*Wektor si�y, kt�r� kr�lik dostaje przy odbicu si� od �ciany*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
		FVector WallRepulsionForce;

	/*SETTERY*/
	UFUNCTION(BlueprintCallable, Category = "Movement")
		void SetIsTouchingWallFront(bool Val) { bIsTouchingWallFront = Val; };
	UFUNCTION(BlueprintCallable, Category = "Movement")
		void SetIsTouchingWallBack(bool Val) { bIsTouchingWallBack = Val; };
	/*GETTERY*/
	UFUNCTION(BlueprintCallable, Category = "Movement")
		bool GetIsTouchingWallFront() { return bIsTouchingWallFront; };
	UFUNCTION(BlueprintCallable, Category = "Movement")
		bool GetIsTouchingWallBack() { return bIsTouchingWallBack; };

protected:
	/*Collidery, kt�re wy�apuj� odbijanie si� od �cian, z ty�u i z przodu*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
		UBoxComponent* WallJumpFrontColl;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
		UBoxComponent* WallJumpBackColl;
	/*Czy dotykamy �ciany?*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		bool bIsTouchingWallFront;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		bool bIsTouchingWallBack;

	/*Funkcje, kt�re si� dziej� kiedy collidery dotkn� �ciany (na parametry patrz API)*/
	UFUNCTION()
		void OnFrontBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFroomSweep, const FHitResult &SweepResult);
	UFUNCTION()
		void OnBackBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFroomSweep, const FHitResult &SweepResult);
	/*Funkcje kiedy collidery odejd� od �ciany*/
	UFUNCTION()
		void OnFrontEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION()
		void OnBackEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
