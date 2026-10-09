// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DST_Character.h"
#include "DSTCitizen.generated.h"

UCLASS()
class DSTOGETHER_API ADSTCitizen : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADSTCitizen();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	bool CanReceiveCargo(ADST_Character* Player) const;
	bool TryReceiveCargo(ADST_Character* Player);
};
