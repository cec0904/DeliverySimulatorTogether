// Fill out your copyright notice in the Description page of Project Settings.


#include "DST/Vehicle/DST_Vehicle.h"

// Sets default values
ADST_Vehicle::ADST_Vehicle()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADST_Vehicle::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADST_Vehicle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADST_Vehicle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

bool ADST_Vehicle::TryRide(ADSTogetherCharacter* Player, int32 SeatIndex)
{
	return false;
}

void ADST_Vehicle::AttachToSeat(ADSTogetherCharacter* Player, int32 SeatIndex)
{
}

void ADST_Vehicle::DetachFromSeat(ADSTogetherCharacter* Player)
{
}

bool ADST_Vehicle::TryGetOff(ADSTogetherCharacter* Player)
{
	return false;
}

