// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "TurretPawn.generated.h"

class ATankPawn;

UCLASS()
class TANKS_API ATurretPawn : public ABasePawn
{
	GENERATED_BODY()
	
private:


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float FireRate = 2.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float FireRange = 300.f;

	FTimerHandle FireRateTimerHandle;
	ATankPawn* PlayerPawn = nullptr;

	void CheckFireCondition();
	float ReturnDistanceToPlayer();

public:

	virtual void Tick(float DeltaTime) override;
	virtual void HandleDestruction() override;

protected:

	virtual void BeginPlay() override;
};
