// Fill out your copyright notice in the Description page of Project Settings.


#include "TurretPawn.h"
#include "Kismet/GameplayStatics.h"
#include "TankPawn.h"

// Called when the game starts or when spawned
void ATurretPawn::BeginPlay()
{
	Super::BeginPlay();
	
    GetWorld()->GetTimerManager().SetTimer(
        FireRateTimerHandle,
        this,
        &ATurretPawn::CheckFireCondition,
        FireRate,
        true
    );

    PlayerPawn = Cast<ATankPawn>(UGameplayStatics::GetPlayerPawn(this, 0));
}


void ATurretPawn::HandleDestruction()
{
    Super::HandleDestruction();

    Destroy();
}

// Called every frame
void ATurretPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (!PlayerPawn || ReturnDistanceToPlayer() > FireRange) { return; }
    
    RotateTurret(PlayerPawn->GetActorLocation());
}


void ATurretPawn::CheckFireCondition()
{
    if (!PlayerPawn || !PlayerPawn->GetIsPlayerAlive()) { return; }
    
    if (ReturnDistanceToPlayer() <= FireRange)
    {
        Fire();
    }
}


float ATurretPawn::ReturnDistanceToPlayer()
{
    if (!PlayerPawn) { return 0.f; }

    return FVector::Dist(PlayerPawn->GetActorLocation(), GetActorLocation());
}