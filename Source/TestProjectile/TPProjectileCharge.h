// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TPProjectileBase.h"
#include "TPProjectileCharge.generated.h"

/**
 * 
 */
UCLASS()
class TESTPROJECTILE_API ATPProjectileCharge : public ATPProjectileBase
{
	GENERATED_BODY()

public:
	ATPProjectileCharge();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
