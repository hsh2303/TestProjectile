// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TPProjectileBase.h"
#include "TPProjectileSplit.generated.h"

/**
 * 
 */
UCLASS()
class TESTPROJECTILE_API ATPProjectileSplit : public ATPProjectileBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATPProjectileSplit();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	/** Overridable function called whenever this actor is being removed from a level */
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);

private:
	UPROPERTY(VisibleAnywhere, Category=Projectile)
	class UArrowComponent* m_pLeftArrowComp;

	UPROPERTY(VisibleAnywhere, Category=Projectile)
	class UArrowComponent* m_pRightArrowComp;
};
