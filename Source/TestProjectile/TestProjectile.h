// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "EngineMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(TestProjectile, Log, All);

const float PROJECTILE_BASE_LIFE_SPAN = 3.0f;
const float PROJECTILE_CHARGE_LIFE_SPAN = 5.0f;
const float PROJECTILE_SPLIT_LIFE_SPAN = 3.0f;

///< 발사체 스폰 위치
const FVector vSpawnProjectileRelativePos = FVector(20.0f, 50.0f, 0.0f);
