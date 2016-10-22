// Fill out your copyright notice in the Description page of Project Settings.

#include "BuddyProject.h"
#include "Projectile.h"


// Sets default values
AProjectile::AProjectile(const FObjectInitializer& ObjectInitializer)
{
	SphereComp = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this, TEXT("Sphere Component"));
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnBeginOverlap);
	RootComponent = SphereComp;

	MovementComp = ObjectInitializer.CreateDefaultSubobject<UProjectileMovementComponent>(this, TEXT("Movement Comp"));
}

void AProjectile::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFroomSweep, const FHitResult &SweepResult)
{
//	Destroy();
}
