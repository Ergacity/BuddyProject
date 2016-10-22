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

	/*Deklarujemy stucta u g�ry*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Config")
		FEnemyData EnemyConfig;

protected:
	/*Wywo�ywana gdy co� koliduje z BoxComp*/
	UFUNCTION(BlueprintCallable, Category = "Collision")
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFroomSweep, const FHitResult &SweepResult);
	/*Wywo�ywana gdy co� przestaje kolidowa�*/
	UFUNCTION(BlueprintCallable, Category = "Collision")
		void OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	/*Wywo�ywana gdy strzela w gracza*/
	UFUNCTION(BlueprintCallable, Category = "Combat")
		void Shoot();

	/*Zasi�g przeciwnika*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
		USphereComponent* SphereComp;
	/*Handlowanie z timerem*/
	UPROPERTY()
		FTimerHandle ShootTimerHandle;
	/*Czy widzimy przeciwnika?*/
	UPROPERTY()
		bool bEnemyInRange;	
	/*Czy sko�czyli�my timer?*/
	UPROPERTY()
		bool bTimerDone;
	/*Pocisk, kt�rym szczelamy*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
		TSubclassOf<class AProjectile> ProjectileClass;

	
};
