// Fill out your copyright notice in the Description page of Project Settings.


#include "DST/Cargo/DSTCargo.h"
#include "../Character/DST_Character.h"
#include "../Character/DSTCitizen.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"

// Sets default values
ADSTCargo::ADSTCargo()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.

    PrimaryActorTick.bCanEverTick = false;

    CargoMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CargoMesh"));
    SetRootComponent(CargoMesh);
    CargoMesh->SetCollisionProfileName(TEXT("PhysicsActor"));
    CargoMesh->SetSimulatePhysics(true);

    LeftHandGrip = CreateDefaultSubobject<USceneComponent>(TEXT("LeftHandGrip"));
    LeftHandGrip->SetupAttachment(CargoMesh);

    RightHandGrip = CreateDefaultSubobject<USceneComponent>(TEXT("RightHandGrip"));
    RightHandGrip->SetupAttachment(CargoMesh);
}

bool ADSTCargo::CanPickUp(ADST_Character* Player) const
{
    return IsValid(Player)
        && CargoState == ECargoState::Available
        && !IsValid(Player->GetHeldItem())
        && GetAttachParentActor() == nullptr;

}
// 캐릭터가 이 상자에 상호작용을 요청하면 실행
void ADSTCargo::Interact_Implementation(ADST_Character* Player)
{
    if (!CanPickUp(Player)) return;

    if (PickUp(Player->GetHoldPoint()))
    {
        Player->SetHeldItem(this);
    }
}

// 상자를 캐릭터의 HoldPoint에 붙이기
bool ADSTCargo::PickUp(USceneComponent* HoldPoint)
{
    if (!IsValid(HoldPoint)) return false;
    if (CargoState != ECargoState::Available) return false;
    if (GetAttachParentActor() != nullptr) return false;

    CargoMesh->SetSimulatePhysics(false);
    CargoMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    const bool bAttached = AttachToComponent(
        HoldPoint,
        FAttachmentTransformRules::SnapToTargetNotIncludingScale
    );

    if (!bAttached)
    {
        CargoMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
        CargoMesh->SetSimulatePhysics(true);
        return false;
    }

    SetCargoState(ECargoState::Held);
    return true;
}

bool ADSTCargo::Drop()
{
    if (CargoState != ECargoState::Held) return false;

    DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

    CargoMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    CargoMesh->SetSimulatePhysics(true);

    SetCargoState(ECargoState::Available);
    return true;
}

void ADSTCargo::SetCargoState(ECargoState NewState)
{
    if (CargoState == NewState) return;

    CargoState = NewState;
    OnCargoStateChanged(NewState);
}



