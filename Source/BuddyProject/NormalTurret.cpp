// Fill out your copyright notice in the Description page of Project Settings.

#include "BuddyProject.h"
#include "NormalTurret.h"


ANormalTurret::ANormalTurret(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	EnemyConfig.Name = "NormalTurret";
	EnemyConfig.Health = 100;
	EnemyConfig.InitTime = 0.f;
	EnemyConfig.ShootDelay = 2.f;
	EnemyConfig.DetectRange = 2000.f;
}

