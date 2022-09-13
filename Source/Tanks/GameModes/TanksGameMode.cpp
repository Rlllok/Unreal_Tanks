// Fill out your copyright notice in the Description page of Project Settings.


#include "TanksGameMode.h"
#include "Tanks/Pawns/TankPawn.h"
#include "Tanks/Pawns/TurretPawn.h"
#include "Kismet/GameplayStatics.h"
#include "Tanks/PlayerControllers/PlayerControllerBase.h"


void ATanksGameMode::BeginPlay()
{
    Super::BeginPlay();

    HandleGameStart();
}


void ATanksGameMode::ActorDied(AActor* DeadActor)
{
    if (DeadActor == PlayerTank)
    {
        PlayerTank->HandleDestruction();
        HandleGameOver(false);

        if (PlayerControllerRef)
        {
            PlayerControllerRef->SetPlayerEnabledState(false);
        }
    }
    else if (ATurretPawn* DestroyedTurret = Cast<ATurretPawn>(DeadActor))
    {
        DestroyedTurret->HandleDestruction();

        if (--TargetTurrets == 0)
        {
            HandleGameOver(true);
        }
    }
}


void ATanksGameMode::HandleGameStart()
{
    TargetTurrets = GetTurretsNum();
    PlayerTank = Cast<ATankPawn>(UGameplayStatics::GetPlayerPawn(this, 0));
    PlayerControllerRef = Cast<APlayerControllerBase>(UGameplayStatics::GetPlayerController(this, 0));

    GameStart();
    if (PlayerControllerRef) {
        PlayerControllerRef->SetPlayerEnabledState(false);

        FTimerHandle PlayerEnableHandle;
        FTimerDelegate PlayerEnableDelegate = FTimerDelegate::CreateUObject(PlayerControllerRef,
            &APlayerControllerBase::SetPlayerEnabledState, true);
        GetWorld()->GetTimerManager().SetTimer(PlayerEnableHandle, PlayerEnableDelegate, StartDelay, false);
    }
}


void ATanksGameMode::HandleGameOver(bool PlayerWon)
{
    GameOver(PlayerWon);
}


int32 ATanksGameMode::GetTurretsNum()
{
    TArray<AActor*> TurretActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATurretPawn::StaticClass(), TurretActors);
    return TurretActors.Num();
}