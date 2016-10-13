// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "RotationGate.generated.h"

UCLASS()
class BUDDYPROJECT_API ARotationGate : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARotationGate(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Collision")
		UBoxComponent* BoxComp;
	/*Jaki kat powinien miec gracz po przejscu przez te bramke?*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float GateRot;
	/*Jak szybko powinno gracza obrocic?*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float GateRotSpeed;

protected:
	/*Wzywana gdy ktoœ wejdzie w Gate*/
	UFUNCTION()
		void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFroomSweep, const FHitResult &SweepResult);

	
	
};
