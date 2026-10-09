// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DST/Interaction/DSTInteractable.h"
#include "DSTCargo.generated.h"

class UStaticMeshComponent;
class USceneComponent;

UENUM(BlueprintType)
enum class ECargoState : uint8
{
    Available UMETA(DisplayName = "Available"),
    Held      UMETA(DisplayName = "Held"),
    Delivered UMETA(DisplayName = "Delivered")
};

UCLASS()
class DSTOGETHER_API ADSTCargo : public AActor, public IDSTInteractable
{
	GENERATED_BODY()
	
public:
    ADSTCargo();

    virtual void Interact_Implementation(ADST_Character* Player) override;

    bool PickUp(USceneComponent* HoldPoint);
    bool Drop();

    UFUNCTION(BlueprintPure, Category = "Cargo")
    ECargoState GetCargoState() const { return CargoState; }

    UFUNCTION(BlueprintPure, Category = "Cargo")
    bool CanPickUp(ADST_Character* Player) const;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Cargo")
    TObjectPtr<UStaticMeshComponent> CargoMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cargo")
    ECargoState CargoState = ECargoState::Available;

    UFUNCTION(BlueprintImplementableEvent, Category = "Cargo")
    void OnCargoStateChanged(ECargoState NewState);




    // 왼손이 잡을 위치와 방향
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Cargo|Grip")
    TObjectPtr<USceneComponent> LeftHandGrip;

    // 오른손이 잡을 위치와 방향
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Cargo|Grip")
    TObjectPtr<USceneComponent> RightHandGrip;

private:
    void SetCargoState(ECargoState NewState);
};
