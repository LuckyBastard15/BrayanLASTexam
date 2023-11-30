// Fill out your copyright notice in the Description page of Project Settings.
#include "HunterBullet.h"
#include "BrayanLastExamCharacter.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AHunterBullet::AHunterBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	MeshComponent->SetCollisionResponseToChannels(ECR_Block);
	RootComponent = MeshComponent;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	SphereComponent->SetupAttachment(MeshComponent);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovementComponent->InitialSpeed = 5000.0f;
	ProjectileMovementComponent->MaxSpeed = 5000.0f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->ProjectileGravityScale = 9.8f;
}

// Called when the game starts or when spawned
void AHunterBullet::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AHunterBullet::LifeTimeOver, LifeTime, true);
}

void AHunterBullet::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	ABrayanLastExamCharacter* Character = Cast<ABrayanLastExamCharacter>(OtherActor);
	if (Character)
	{
		Character->CanDie();
	}
}

// Called every frame
void AHunterBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHunterBullet::GetPlayer(ABrayanLastExamCharacter* Player)
{
	OwningPlayer = Player;
	OwningPlayer->bCanShoot = false;
}

void AHunterBullet::LifeTimeOver()
{
	OwningPlayer->bCanShoot = true;
	Destroy();
}

