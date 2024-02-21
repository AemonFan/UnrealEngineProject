// Fill out your copyright notice in the Description page of Project Settings.
#include "Floor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "../ParkourCharacter.h"
#include "../ParkourGameMode.h"

// Sets default values
AFloor::AFloor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SeceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Father"));
	FloorRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("FloorRootComponent"));
	RootComponent = FloorRootComponent;

	BoxMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoxMesh"));
	//碰撞
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));

	//方向的确定
	SpawnPiontMiddle = CreateDefaultSubobject<UArrowComponent>(TEXT("SpawnPiontMiddle"));
	SpawnPiontRight = CreateDefaultSubobject<UArrowComponent>(TEXT("SpawnPiontRight"));
	SpawnPiontLeft = CreateDefaultSubobject<UArrowComponent>(TEXT("SpawnPiontLeft"));

	SeceneComponent->SetupAttachment(RootComponent);
	BoxMesh->SetupAttachment(SeceneComponent);
	BoxComponent->SetupAttachment(SeceneComponent);
	SpawnPiontMiddle->SetupAttachment(SeceneComponent);
	SpawnPiontRight->SetupAttachment(SeceneComponent);
	SpawnPiontLeft->SetupAttachment(SeceneComponent);
}

FTransform AFloor::GetAttachToTransform(const FVector &MyLoction)
{
	FTransform Transform;

	Transform.SetLocation(SpawnPiontMiddle->GetComponentToWorld().GetLocation());
	Transform.SetRotation(SpawnPiontMiddle->GetComponentQuat());

	return Transform;
}

// Called when the game starts or when spawned
void AFloor::BeginPlay()
{
	Super::BeginPlay();

	BoxComponent->OnComponentBeginOverlap.AddUniqueDynamic(this, &AFloor::BoxOverlap);
}

// Called every frame
void AFloor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFloor::BoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(AParkourCharacter::StaticClass()))
	{
		if (AParkourGameMode* InGameMode = GetWorld()->GetAuthGameMode<AParkourGameMode>())
		{
			InGameMode->AddFloor();

			GetWorldTimerManager().SetTimer(MyTimeHandle, this, &AFloor::DestroyThis, 2.20f, true);
		}
	}
}

void AFloor::DestroyThis()
{
	if (MyTimeHandle.IsValid())
	{
		GetWorldTimerManager().ClearTimer(MyTimeHandle);
	}

	Destroy(true);
}