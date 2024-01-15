// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickup.h"
#include "Components/StaticMeshComponent.h"
#include "Components/Image.h"
#include "Blaster/HUD/CharacterOverlay.h"
#include "Blaster/HUD/BlasterHUD.h"
#include "Blaster/BlasterComponents/CombatComponent.h"
#include "Blaster/PlayerController/BlasterPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Components/WidgetComponent.h" 
#include "Blaster/Character/BlasterCharacter.h"


// Constructor
APickup::APickup()
{
    PrimaryActorTick.bCanEverTick = false;
    bReplicates = true;

    MyPickups = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
    SetRootComponent(MyPickups);

    MyPickups->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
    MyPickups->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
    MyPickups->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    MyPickups->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

    AreaSphere = CreateDefaultSubobject<USphereComponent>(TEXT("AreaSphere"));
    AreaSphere->SetupAttachment(RootComponent); // Attach to the root component
    AreaSphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    AreaSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
    Super::BeginPlay();

    AreaSphere->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    AreaSphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
    AreaSphere->OnComponentBeginOverlap.AddDynamic(this, &APickup::OnSphereOverlap);
    AreaSphere->OnComponentEndOverlap.AddDynamic(this, &APickup::OnSphereEndOverlap);

}

// Called every frame
void APickup::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

void APickup::ShowPickupWidget(bool bShowWidget)
{
    if (PickupWidget)
    {
        PickupWidget->SetVisibility(bShowWidget);
    }
}

void APickup::OnSphereOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void APickup::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}
