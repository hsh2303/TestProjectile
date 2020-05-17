// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TestProjectile.h"
#include "GameFramework/Actor.h"
#include "TPProjectileBase.generated.h"

UCLASS()
class TESTPROJECTILE_API ATPProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATPProjectileBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

protected:
	UPROPERTY(VisibleAnywhere, Category=Projectile)
	class USphereComponent* m_pSphereComp;

	UPROPERTY(VisibleAnywhere, Category=Projectile)
	class UStaticMeshComponent* m_pBodyMeshComp;

	UPROPERTY(VisibleAnywhere, Category=Projectile)
	class UArrowComponent* m_pArrowComp;

	UPROPERTY(VisibleAnywhere, Category=Projectile)
	class UProjectileMovementComponent* m_pProjectileMovementComponent;
};
