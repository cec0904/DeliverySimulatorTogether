// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "../Character/DST_Character.h"
#include "../../DSTogetherCharacter.h"
#include "DST_Vehicle.generated.h"

UCLASS()
class DSTOGETHER_API ADST_Vehicle : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ADST_Vehicle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	struct FSeat
	{
		ADSTogetherCharacter* AlreadyHaveSeat = nullptr; // 이 좌석에 앉은 사람
		bool bCanDrive = false;							 // 이 좌석이 운전석인가
	};

	FSeat Seats[4];

	// 운전 관련
	// 페달
	enum DriveState
	{
		Accelerator,
		Break,
		Clutch
	};

	// 기어
	enum GearPosition
	{
		Parking,
		Reverse,
		Neutral,
		Drive,
		Low
	};

	// 기어마다 속도
	enum GearStage
	{
		Stage1 = 1,
		Stage2,
		Stage3,
		Stage4,
		Stage5,
		Stage6
	};

	// 차량의 속도
	float MaxSpeed = 1.f;


public:
	// 차량 탑승 -> 좌석 확인 -> 좌석에서 떨어짐 -> 차량 하차

	// 좌석에 앉을 때 누가 앉아있는지 판단
	UFUNCTION(BlueprintCallable, Category = "Ride")
	bool TryRide(ADSTogetherCharacter* Player, int32 SeatIndex);

	// 실제로 좌석에 플레이어 붙이는 역할
	UFUNCTION(BlueprintCallable, Category = "Ride")
	void AttachToSeat(ADSTogetherCharacter* Player, int32 SeatIndex);

	// 좌석에 플레이어 떨어뜨리는 역할
	UFUNCTION(BlueprintCallable, Category = "Ride")
	void DetachFromSeat(ADSTogetherCharacter* Player);

	// 차량 하차
	UFUNCTION(BlueprintCallable, Category = "Ride")
	bool TryGetOff(ADSTogetherCharacter* Player);



	//// 운전관련
	//UFUNCTION(BlueprintCallable, Category = "Ride")
	//void Accelerator();

	//UFUNCTION(BlueprintCallable, Category = "Ride")
	//void Break();

	//UFUNCTION(BlueprintCallable, Category = "Ride")
	//void Clutch();





};
