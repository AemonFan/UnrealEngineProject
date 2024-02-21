// Copyright Epic Games, Inc. All Rights Reserved.

#include "ParkourGameMode.h"
#include "ParkourCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Actor/Floor.h"

AParkourGameMode::AParkourGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	StraightArray.Add(LoadClass<AActor>(NULL, TEXT("Blueprint'/Game/Environment/Floor/BP/StraightFloor_1.StraightFloor_1_C'")));
	StraightArray.Add(LoadClass<AActor>(NULL, TEXT("Blueprint'/Game/Environment/Floor/BP/StraightFloor_2.StraightFloor_2_C'")));
	StraightArray.Add(LoadClass<AActor>(NULL, TEXT("Blueprint'/Game/Environment/Floor/BP/StraightFloor_3.StraightFloor_3_C'")));
	StraightArray.Add(LoadClass<AActor>(NULL, TEXT("Blueprint'/Game/Environment/Floor/BP/StraightFloor_4.StraightFloor_4_C'")));
	StraightArray.Add(LoadClass<AActor>(NULL, TEXT("Blueprint'/Game/Environment/Floor/BP/DownFloor.DownFloor_C'")));
	StraightArray.Add(LoadClass<AActor>(NULL, TEXT("Blueprint'/Game/Environment/Floor/BP/UPFloor.UPFloor_C'")));

	LeftRightArray.Add(LoadClass<AActor>(NULL, TEXT("Blueprint'/Game/Environment/Floor/BP/TurnRightFloor.TurnRightFloor_C'")));
	LeftRightArray.Add(LoadClass<AActor>(NULL, TEXT("Blueprint'/Game/Environment/Floor/BP/TurnLeftFloor.TurnLeftFloor_C'")));
}

void AParkourGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (GetWorld())
	{
		NestTransfroms = GetWorld()->GetFirstPlayerController()->GetPawn()->GetTransform();

		FVector InLocation = NestTransfroms.GetLocation();

		InLocation.Y += 100.f;
		InLocation.Z -= 200.f;
		NestTransfroms.SetLocation(InLocation);

		for (int32 i = 0; i < 9; i++)
		{
			AddFloor();
		}
	}
}

TSubclassOf<AActor> AParkourGameMode::RandomInputFloor()
{
	if (FMath::RandRange(1, 100) <= 80)
	{
		return StraightArray[FMath::RandRange(0, StraightArray.Num() - 1)];
	}
	else
	{
		return LeftRightArray[FMath::RandRange(0, LeftRightArray.Num() - 1)];
	}
}

//添加我们地板
void AParkourGameMode::AddFloor()
{
	NewFloorTle = RandomInputFloor();
	if (NewFloorTle != NULL)
	{
		FVector const MyLoction = NestTransfroms.GetLocation();
		FRotator MyRotation(NestTransfroms.Rotator());
		if (AFloor* MyFloor = GetWorld()->SpawnActor<AFloor>(NewFloorTle, MyLoction, MyRotation))
		{
			MyFloor->SetActorScale3D(FVector(10.f));

			NestTransfroms = MyFloor->GetAttachToTransform(MyLoction);
		}		
	}
}
