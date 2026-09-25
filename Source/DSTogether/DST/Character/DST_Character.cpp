// Fill out your copyright notice in the Description page of Project Settings.


#include "DST/Character/DST_Character.h"

// Sets default values
ADST_Character::ADST_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADST_Character::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADST_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADST_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

