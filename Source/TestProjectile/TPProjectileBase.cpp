// Fill out your copyright notice in the Description page of Project Settings.

#include "TPProjectileBase.h"
#include "Engine/Engine.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ATPProjectileBase::ATPProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_pSphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SPHERE"));
	m_pBodyMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BODY"));
	m_pArrowComp = CreateDefaultSubobject<UArrowComponent>(TEXT("ARROW"));
	m_pProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("PROJECTILEMOVEMENT"));
	float fRadius = 1.f;

	if (m_pSphereComp)
	{
		RootComponent = m_pSphereComp;
		m_pSphereComp->InitSphereRadius(10.0f);
		m_pSphereComp->SetCollisionObjectType(ECC_EngineTraceChannel1);
		m_pSphereComp->SetCollisionProfileName(TEXT("Projectile"));
		FCollisionShape shape = m_pSphereComp->GetCollisionShape();
		fRadius = shape.GetSphereRadius();

		m_pSphereComp->OnComponentHit.AddDynamic(this, &ATPProjectileBase::OnHit);
	}

	if (m_pProjectileMovementComponent)
	{
		m_pProjectileMovementComponent->SetUpdatedComponent(m_pSphereComp);
		m_pProjectileMovementComponent->InitialSpeed = 100.0f;
		m_pProjectileMovementComponent->MaxSpeed = 100.0f;
		m_pProjectileMovementComponent->bRotationFollowsVelocity = true;
		m_pProjectileMovementComponent->bShouldBounce = false;
		m_pProjectileMovementComponent->ProjectileGravityScale = 0.0f;
	}

	if (m_pBodyMeshComp)
	{
		static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_SPHERE(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));
		if (SM_SPHERE.Succeeded())
		{
			m_pBodyMeshComp->SetStaticMesh(SM_SPHERE.Object);
			m_pBodyMeshComp->SetupAttachment(m_pSphereComp);
			m_pBodyMeshComp->SetCollisionProfileName(TEXT("NoCollision"));
			m_pBodyMeshComp->SetRelativeLocation(FVector(0.f, 0.f, -fRadius));
			m_pBodyMeshComp->SetRelativeScale3D(FVector(0.195f, 0.195f, 0.195f));
			FCollisionShape shape = m_pBodyMeshComp->GetCollisionShape();
			fRadius = shape.GetSphereRadius();
		}
	}

	if (m_pArrowComp)
	{
		m_pArrowComp->SetupAttachment(m_pBodyMeshComp);
		m_pArrowComp->SetRelativeLocation(FVector(0.f, 0.f, fRadius));
		m_pArrowComp->SetRelativeScale3D(FVector(1.3f, 1.3f, 1.3f));
		m_pArrowComp->SetHiddenInGame(false);
		m_pArrowComp->SetCollisionProfileName(TEXT("NoCollision"));
	}
}

// Called when the game starts or when spawned
void ATPProjectileBase::BeginPlay()
{
	Super::BeginPlay();

	SetLifeSpan(PROJECTILE_BASE_LIFE_SPAN);
}

void ATPProjectileBase::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	Destroy();
}

