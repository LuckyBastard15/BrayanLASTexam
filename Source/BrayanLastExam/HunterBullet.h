// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HunterBullet.generated.h"

class UStaticMeshComponent;
class USphereComponent;
UCLASS()
class BRAYANLASTEXAM_API AHunterBullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHunterBullet();

	UPROPERTY(EditAnywhere, Category="Components")
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere, Category="Components")
	USphereComponent* SphereComponent;

	UPROPERTY(EditAnywhere, Category="Config")
	int32 LifeTime;

	FTimerHandle TimerHandle;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void LifeTimeOver();

	

};
