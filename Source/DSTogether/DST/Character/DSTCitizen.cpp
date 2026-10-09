// Fill out your copyright notice in the Description page of Project Settings.


#include "DST/Character/DSTCitizen.h"

// Sets default values
ADSTCitizen::ADSTCitizen()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADSTCitizen::BeginPlay()
{
	Super::BeginPlay();
	
}

bool ADSTCitizen::CanReceiveCargo(ADST_Character* Player) const
{
	return false;
}

bool ADSTCitizen::TryReceiveCargo(ADST_Character* Player)
{
	return false;
}



