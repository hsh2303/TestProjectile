// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "TestProjectile.h"
#include "GameFramework/Character.h"
#include "TestProjectileCharacter.generated.h"

UCLASS(config=Game)
class ATestProjectileCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Side view camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* SideViewCameraComponent;

	/** Camera boom positioning the camera beside the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

protected:

	/** Called for side to side input */
	void MoveRight(float Val);

	/** Handle touch inputs. */
	void TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location);

	/** Handle touch stop event. */
	void TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location);

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End of APawn interface

public:
	virtual void Tick(float DeltaTime) override;

public:
	ATestProjectileCharacter();

	/** Returns SideViewCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetSideViewCameraComponent() const { return SideViewCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

protected:
	void SkilKeylPressed();
	void SkillKeyReleased();
	void SkillOptionPressed();

protected:
	void SkillKeyStateCheck(float DeltaTime);
	bool GetSpawnProjectileLocationAndRot(FVector& vLocation, FRotator& rRot);
	void SpawnProjectile(UClass* pUClass, const FVector& vLocation, const FRotator& rRot);

protected:
	///< SkillKey 눌렸는지 여부
	bool m_bSkillKeyPressed;
	///< SkillKey 눌려진 시간
	float m_fSkillPressedDelta;
};
