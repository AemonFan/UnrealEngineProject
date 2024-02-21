// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ParkourType.generated.h"

UENUM()
enum class FFloorType :uint8//0-255
{
	StraightFloor,
	TurnFloor,
	UPAndDownFloor,
	MAX,
};