// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"


ATankPawn::ATankPawn()
{
    SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    SpringArmComp->SetupAttachment(RootComponent);

    CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    CameraComp->SetupAttachment(SpringArmComp);
}

// Called when the game starts or when spawned
void ATankPawn::BeginPlay()
{
	Super::BeginPlay();
	
    PlayerControllerRef = Cast<APlayerController>(GetController());
}


void ATankPawn::HandleDestruction()
{
    Super::HandleDestruction();
    
    bIsPlayerAlive = false;

    SetActorHiddenInGame(true);
    SetActorTickEnabled(false);
}

bool ATankPawn::GetIsPlayerAlive()
{
    return bIsPlayerAlive;
}

// Called every frame
void ATankPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    Rotate();
    Move();

    if (PlayerControllerRef)
    {
        FHitResult TraceHitResult;
        PlayerControllerRef->GetHitResultUnderCursor(ECC_Visibility, false, TraceHitResult);
        FVector HitLocation = TraceHitResult.ImpactPoint;

        RotateTurret(HitLocation);
    }
}

// Called to bind functionality to input
void ATankPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
    PlayerInputComponent->BindAxis("MoveForward", this, &ATankPawn::CalculateMoveInput);
    PlayerInputComponent->BindAxis("Turn", this, &ATankPawn::CalculateRotateInput);
    PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ATankPawn::Fire);
}


void ATankPawn::CalculateMoveInput(float Value)
{
    float MoveAmount = Value * MoveSpeed * GetWorld()->DeltaTimeSeconds;
    MoveDirection = FVector(MoveAmount, 0, 0);
}


void ATankPawn::CalculateRotateInput(float Value)
{
    float RotateAmount = Value * RotateSpeed * GetWorld()->DeltaTimeSeconds;
    FRotator Rotation = FRotator(0, RotateAmount, 0);
    RotationDirection = FQuat(Rotation);
}


void ATankPawn::Move()
{
    AddActorLocalOffset(MoveDirection, true);
}


void ATankPawn::Rotate()
{
    AddActorLocalRotation(RotationDirection, true);
}