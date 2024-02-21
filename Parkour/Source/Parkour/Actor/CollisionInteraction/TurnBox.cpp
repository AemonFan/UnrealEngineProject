// Fill out your copyright notice in the Description page of Project Settings.


//#include "Actor/CollisionInteraction/TurnBox.h"
#include "TurnBox.h"
#include "../../ParkourCharacter.h"
#include "Components/BoxComponent.h"

// Sets default values
ATurnBox::ATurnBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = Box;
}

// Called when the game starts or when spawned
void ATurnBox::BeginPlay()
{
	Super::BeginPlay();
	
	Box->OnComponentBeginOverlap.AddDynamic(this, &ATurnBox::CharacterOverlapStart);
	Box->OnComponentEndOverlap.AddDynamic(this, &ATurnBox::CharacterOverlapEnd);
}

// Called every frame
void ATurnBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATurnBox::CharacterOverlapStart(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, 
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep, 
	const FHitResult& SweepResult)
{
	if (AParkourCharacter *InCharacter = Cast<AParkourCharacter>(OtherActor))
	{
		InCharacter->bTurn = true;
	}
}

void ATurnBox::CharacterOverlapEnd(
	UPrimitiveComponent* OverlappedComponent, 
	AActor* OtherActor, 
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	if (AParkourCharacter* InCharacter = Cast<AParkourCharacter>(OtherActor))
	{
		InCharacter->bTurn = false;
	}
}


