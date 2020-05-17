// Fill out your copyright notice in the Description page of Project Settings.


#include "TPProjectileCharge.h"
#include "Components/ArrowComponent.h"

ATPProjectileCharge::ATPProjectileCharge()
{
	if (m_pArrowComp)
	{
		FVector vScale = m_pArrowComp->GetRelativeScale3D();
		m_pArrowComp->SetRelativeScale3D(vScale * 3.0f);
	}
}

void ATPProjectileCharge::BeginPlay()
{
	Super::BeginPlay();

	SetLifeSpan(PROJECTILE_CHARGE_LIFE_SPAN);
}

