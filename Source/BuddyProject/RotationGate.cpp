// Fill out your copyright notice in the Description page of Project Settings.

#include "BuddyProject.h"
#include "RotationGate.h"

#include "PlayerCharacter.h"


// Sets default values
ARotationGate::ARotationGate(const FObjectInitializer& ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;

	BoxComp = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, "Collision Comp");
	RootComponent = BoxComp;
	BoxComp->SetBoxExtent(FVector(200.f, 200.f, 1000.f));
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &ARotationGate::OnComponentBeginOverlap);
}

void ARotationGate::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFroomSweep, const FHitResult &SweepResult)
{
	APlayerCharacter* PC = Cast<APlayerCharacter>(OtherActor);
	if (PC)
	{
		PC->SetDesiredYawRot(GateRot);
		PC->CharacterRotationSpeed = GateRotSpeed;
	}
}

