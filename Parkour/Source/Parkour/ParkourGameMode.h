// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ParkourGameMode.generated.h"

UCLASS(minimalapi)
class AParkourGameMode : public AGameModeBase
{
	GENERATED_BODY()

	//�洢ֱ�ߵİ���
	UPROPERTY()
	TArray<TSubclassOf<class AActor>> StraightArray;

	//�洢���ҵİ���
	UPROPERTY()
	TArray<TSubclassOf<class AActor>> LeftRightArray;

	UPROPERTY()
	TSubclassOf<AActor> NewFloorTle;

	UPROPERTY()
	FTransform NestTransfroms;
public:
	TSubclassOf<AActor> RandomInputFloor();

	virtual void BeginPlay() override;

	//������ǵذ�
	void AddFloor();
public:
	AParkourGameMode();
};



