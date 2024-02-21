// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../ParkourType.h"
#include "Floor.generated.h"

class USceneComponent;
class UBoxComponent;
class UStaticMeshComponent;
class UArrowComponent;

UCLASS()
class PARKOUR_API AFloor : public AActor
{
	GENERATED_BODY()

	//场景组件
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "C_J", meta = (AllowPrivateAccess = "true"))
	USceneComponent* SeceneComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "C_J", meta = (AllowPrivateAccess = "true"))
	USceneComponent* FloorRootComponent;

	//碰撞
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "C_J", meta = (AllowPrivateAccess = "true"))
	UBoxComponent* BoxComponent;

	//模型
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "C_J", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BoxMesh;

	//表明方向
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "C_J", meta = (AllowPrivateAccess = "true"))
	UArrowComponent* SpawnPiontMiddle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "C_J", meta = (AllowPrivateAccess = "true"))
	UArrowComponent* SpawnPiontRight;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "C_J", meta = (AllowPrivateAccess = "true"))
	UArrowComponent*SpawnPiontLeft;

	UPROPERTY(EditDefaultsOnly, Category = "TowerType")
	FFloorType FloorType;
public:	
	// Sets default values for this actor's properties
	AFloor();

	FTransform GetAttachToTransform(const FVector& MyLoction);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void BoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void DestroyThis();
protected:
	FTimerHandle MyTimeHandle;
};
