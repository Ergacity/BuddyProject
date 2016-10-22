// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PlayerCharacter.h"
#include "Projectile.h"

#include "GameFramework/Pawn.h"
#include "StaticEnemy.generated.h"

USTRUCT()
struct FEnemyData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
		FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
		int32 Health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
		float InitTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
		float ShootDelay;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
		float DetectRange;
};

UCLASS()
class BUDDYPROJECT_API AStaticEnemy : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AStaticEnemy(const FObjectInitializer& ObjectInitializer);
	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	/*SETTERY*/
	UFUNCTION(BlueprintCallable, Category = "Combat")
		void SetEnemyInRange(bool Val) { bEnemyInRange = Val; };
	/*GETTERY*/
	UFUNCTION(BlueprintCallable, Category = "Combat")
		bool GetEnemyInRange() { return bEnemyInRange; };

	/*Deklarujemy stucta u góry*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Config")
		FEnemyData EnemyConfig;

protected:
	/*Wywo³ywana gdy coœ koliduje z BoxComp*/
	UFUNCTION(BlueprintCallable, Category = "Collision")
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFroomSweep, const FHitResult &SweepResult);
	/*Wywo³ywana gdy coœ przestaje kolidowaæ*/
	UFUNCTION(BlueprintCallable, Category = "Collision")
		void OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	/*Wywo³ywana gdy strzela w gracza*/
	UFUNCTION(BlueprintCallable, Category = "Combat")
		void Shoot();

	/*Zasiêg przeciwnika*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
		USphereComponent* SphereComp;
	/*Handlowanie z timerem*/
	UPROPERTY()
		FTimerHandle ShootTimerHandle;
	/*Czy widzimy przeciwnika?*/
	UPROPERTY()
		bool bEnemyInRange;	
	/*Czy skoñczyliœmy timer?*/
	UPROPERTY()
		bool bTimerDone;
	/*Pocisk, którym szczelamy*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
		TSubclassOf<class AProjectile> ProjectileClass;

	
};
