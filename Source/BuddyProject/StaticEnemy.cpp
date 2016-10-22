// Fill out your copyright notice in the Description page of Project Settings.

#include "BuddyProject.h"
#include "StaticEnemy.h"


// Sets default values
AStaticEnemy::AStaticEnemy(const FObjectInitializer& ObjectInitializer)
{
	SphereComp = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this, TEXT("Sphere Component"));
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AStaticEnemy::OnBeginOverlap);
	SphereComp->OnComponentEndOverlap.AddDynamic(this, &AStaticEnemy::OnEndOverlap);
	SphereComp->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetIncludingScale, NAME_None);
	SphereComp->SetSphereRadius(EnemyConfig.DetectRange);

	bEnemyInRange = false;
	bTimerDone = true;
}

// Called every frame
void AStaticEnemy::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	if (GetEnemyInRange() && bTimerDone)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, "<");
		GetWorld()->GetTimerManager().SetTimer(ShootTimerHandle, this, &AStaticEnemy::Shoot, EnemyConfig.ShootDelay);
		bTimerDone = false;
	}

}

void AStaticEnemy::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFroomSweep, const FHitResult &SweepResult)
{
	APlayerCharacter* PC = Cast<APlayerCharacter>(OtherActor);
	if (PC)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, "<<");
		SetEnemyInRange(true);
		bTimerDone = true;
	}
}

void AStaticEnemy::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	APlayerCharacter* PC = Cast<APlayerCharacter>(OtherActor);
	if (PC)
	{
		SetEnemyInRange(false);
	}
}

void AStaticEnemy::Shoot()
{
	bTimerDone = true;
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, "!");
	if (ProjectileClass != NULL)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, "!!");
		//Ustawiamy parametry spawnowania
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = Instigator;

		//Spawnujemy rakietê
		AProjectile *const Spawner = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, GetActorLocation() +200.f, GetActorRotation(), SpawnParams);
		if (Spawner) //Jesli siê zespawnuje
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Emerald, "Bam!");
		}
	}
}