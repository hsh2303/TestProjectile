// Fill out your copyright notice in the Description page of Project Settings.

#include "TPProjectileSplit.h"
#include "Components/ArrowComponent.h"

ATPProjectileSplit::ATPProjectileSplit()
{
	m_pLeftArrowComp = CreateDefaultSubobject<UArrowComponent>(TEXT("LEFTARROW"));
	m_pRightArrowComp = CreateDefaultSubobject<UArrowComponent>(TEXT("RIGHTARROW"));

	float fRadius = 1.0f;

	if (m_pBodyMeshComp)
	{
		FCollisionShape shape = m_pBodyMeshComp->GetCollisionShape();
		fRadius = shape.GetSphereRadius();
	}

	if (m_pLeftArrowComp)
	{
		m_pLeftArrowComp->SetupAttachment(m_pBodyMeshComp);
		m_pLeftArrowComp->SetRelativeLocation(FVector(0.f, 0.f, fRadius));
		m_pLeftArrowComp->SetRelativeRotation(FRotator(0, 45, 0));
		m_pLeftArrowComp->SetRelativeScale3D(FVector(1.3f, 1.3f, 1.3f));
		m_pLeftArrowComp->SetHiddenInGame(false);
		m_pLeftArrowComp->SetCollisionProfileName(TEXT("NoCollision"));
	}

	if (m_pRightArrowComp)
	{
		m_pRightArrowComp->SetupAttachment(m_pBodyMeshComp);
		m_pRightArrowComp->SetRelativeLocation(FVector(0.f, 0.f, fRadius));
		m_pRightArrowComp->SetRelativeRotation(FRotator(0, -45, 0));
		m_pRightArrowComp->SetRelativeScale3D(FVector(1.3f, 1.3f, 1.3f));
		m_pRightArrowComp->SetHiddenInGame(false);
		m_pRightArrowComp->SetCollisionProfileName(TEXT("NoCollision"));
	}	
}

void ATPProjectileSplit::BeginPlay()
{
	Super::BeginPlay();

	SetLifeSpan(PROJECTILE_SPLIT_LIFE_SPAN);
}

void ATPProjectileSplit::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (GetLifeSpan() < KINDA_SMALL_NUMBER)
	{
		FVector vLocation = GetActorLocation();
		FRotator rRot = GetActorRotation();
		FVector vDir = rRot.Vector();

		UWorld* pWorld = GetWorld();
		if (pWorld)
		{
			pWorld->SpawnActor<ATPProjectileBase>(vLocation, rRot);
			pWorld->SpawnActor<ATPProjectileBase>(vLocation, FRotator(rRot.Pitch, rRot.Yaw + 45, rRot.Roll));
			pWorld->SpawnActor<ATPProjectileBase>(vLocation, FRotator(rRot.Pitch, rRot.Yaw - 45, rRot.Roll));
		}
	}

	Super::EndPlay(EndPlayReason);
}
