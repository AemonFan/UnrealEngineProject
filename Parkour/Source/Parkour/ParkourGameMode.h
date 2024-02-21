// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ParkourGameMode.generated.h"

UCLASS(minimalapi)
class AParkourGameMode : public AGameModeBase
{
	GENERATED_BODY()

	//存储直线的板子
	UPROPERTY()
	TArray<TSubclassOf<class AActor>> StraightArray;

	//存储左右的板子
	UPROPERTY()
	TArray<TSubclassOf<class AActor>> LeftRightArray;

	UPROPERTY()
	TSubclassOf<AActor> NewFloorTle;

	UPROPERTY()
	FTransform NestTransfroms;
public:
	TSubclassOf<AActor> RandomInputFloor();

	virtual void BeginPlay() override;

	//添加我们地板
	void AddFloor();
public:
	AParkourGameMode();
};



