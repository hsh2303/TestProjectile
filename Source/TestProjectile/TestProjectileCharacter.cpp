// Copyright Epic Games, Inc. All Rights Reserved.

#include "TestProjectileCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TPProjectileCharge.h"
#include "TPProjectileSplit.h"

ATestProjectileCharacter::ATestProjectileCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Create a camera boom attached to the root (capsule)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Rotation of the character should not affect rotation of boom
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->TargetArmLength = 500.f;
	CameraBoom->SocketOffset = FVector(0.f,0.f,75.f);
	CameraBoom->SetRelativeRotation(FRotator(0.f,180.f,0.f));

	// Create a camera and attach to boom
	SideViewCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("SideViewCamera"));
	SideViewCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	SideViewCameraComponent->bUsePawnControlRotation = false; // We don't want the controller rotating the camera

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Face in the direction we are moving..
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->GravityScale = 2.f;
	GetCharacterMovement()->AirControl = 0.80f;
	GetCharacterMovement()->JumpZVelocity = 1000.f;
	GetCharacterMovement()->GroundFriction = 3.f;
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	GetCharacterMovement()->MaxFlySpeed = 600.f;

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)

	m_bSkillKeyPressed = false;
	m_fSkillPressedDelta = 0.0f;
}

//////////////////////////////////////////////////////////////////////////
// Input

void ATestProjectileCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAxis("MoveRight", this, &ATestProjectileCharacter::MoveRight);

	PlayerInputComponent->BindTouch(IE_Pressed, this, &ATestProjectileCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &ATestProjectileCharacter::TouchStopped);

	PlayerInputComponent->BindAction("Skill", IE_Pressed, this, &ATestProjectileCharacter::SkilKeylPressed);
	PlayerInputComponent->BindAction("Skill", IE_Released, this, &ATestProjectileCharacter::SkillKeyReleased);
	PlayerInputComponent->BindAction("SkillOption", IE_Pressed, this, &ATestProjectileCharacter::SkillOptionPressed);
}

void ATestProjectileCharacter::MoveRight(float Value)
{
	// add movement in that direction
	AddMovementInput(FVector(0.f,-1.f,0.f), Value);
}

void ATestProjectileCharacter::TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	// jump on any touch
	Jump();
}

void ATestProjectileCharacter::TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	StopJumping();
}

void ATestProjectileCharacter::Tick(float DeltaTime)
{
	SkillKeyStateCheck(DeltaTime);
}

void ATestProjectileCharacter::SkilKeylPressed()
{
	UE_LOG(TestProjectile, Log, TEXT("SkillKeyPressed"));

	m_bSkillKeyPressed = true;
	m_fSkillPressedDelta = 0.0f;
}

void ATestProjectileCharacter::SkillOptionPressed()
{
	UE_LOG(TestProjectile, Log, TEXT("SkillOptionPressed"));

	if (m_bSkillKeyPressed == true && m_fSkillPressedDelta < 1.0f)
	{
		FVector vLocation = FVector::ZeroVector;
		FRotator rRot = FRotator::ZeroRotator;
		GetSpawnProjectileLocationAndRot(vLocation, rRot);
		SpawnProjectile(ATPProjectileSplit::StaticClass(), vLocation, rRot);
	}
}

void ATestProjectileCharacter::SkillKeyReleased()
{
	UE_LOG(TestProjectile, Log, TEXT("SkillKeyReleased"));

	if (m_fSkillPressedDelta > 3.0f)
	{
		FVector vLocation = FVector::ZeroVector;
		FRotator rRot = FRotator::ZeroRotator;
		GetSpawnProjectileLocationAndRot(vLocation, rRot);
		SpawnProjectile(ATPProjectileCharge::StaticClass(), vLocation, rRot);
	}
	else if (m_bSkillKeyPressed == true)
	{
		FVector vLocation = FVector::ZeroVector;
		FRotator rRot = FRotator::ZeroRotator;
		GetSpawnProjectileLocationAndRot(vLocation, rRot);
		SpawnProjectile(ATPProjectileBase::StaticClass(), vLocation, rRot);
	}

	m_bSkillKeyPressed = false;
	m_fSkillPressedDelta = 0.0f;
}

void ATestProjectileCharacter::SkillKeyStateCheck(float DeltaTime)
{
	if (m_bSkillKeyPressed == true)
	{
		m_fSkillPressedDelta += DeltaTime;
		FString strSkillPressedDeltaMsg = FString::Printf(TEXT("Skill Key Pressed SkillPressedDelta(%.2f)"), m_fSkillPressedDelta);
		GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Red, *strSkillPressedDeltaMsg, false);
	}
}

bool ATestProjectileCharacter::GetSpawnProjectileLocationAndRot(FVector& vLocation, FRotator& rRot)
{
	vLocation = GetActorLocation();
	rRot = GetActorRotation();
	FVector vDir = rRot.Vector();
	vLocation += (vDir * vSpawnProjectileRelativePos);

	return true;
}

void ATestProjectileCharacter::SpawnProjectile(UClass* pUClass, const FVector& vLocation, const FRotator& rRot)
{
	if (pUClass == nullptr)
		return;

	UWorld* pWorld = GetWorld();

	if (pWorld == nullptr)
		return;

	pWorld->SpawnActor(pUClass, &vLocation, &rRot);
}

