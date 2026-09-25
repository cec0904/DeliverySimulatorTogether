// Fill out your copyright notice in the Description page of Project Settings.


#include "DST/Vehicle/DST_Vehicle.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"

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

	if (UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		Input->BindAction(ThrottleAction, ETriggerEvent::Triggered, this, &ADST_Vehicle::OnThrottle);
		Input->BindAction(ThrottleAction, ETriggerEvent::Completed, this, &ADST_Vehicle::OnThrottleReleased);
	}
}

bool ADST_Vehicle::TryRide(ADSTogetherCharacter* Player, int32 SeatIndex)
{
	// 운전석에 앉으려고 할 때
	if (Seats[0].AlreadyHaveSeat != nullptr && Seats[0].bCanDrive == true)
	{
		// 내가 에디터에서 좌석 지정한 운전석 자리
		AttachToSeat(Player, SeatIndex);
	}

	// 운전석이 아닌곳에 앉으려고 할 때
	if (SeatIndex != 0 && Seats[0].AlreadyHaveSeat != nullptr)
	{
		// 내가 에디터에서 좌석 지정한 운전석 자리
		AttachToSeat(Player, SeatIndex);
	}

	// 탈 수 없다는 ui 띄워주기
	return false;
}

void ADST_Vehicle::AttachToSeat(ADSTogetherCharacter* Player, int32 SeatIndex)
{
	// 좌석을 어떻게 지정해줄까
	// 생성자에서 각각의 좌석 메시 지정한 곳을 판단해서 해야하나 ?
}

void ADST_Vehicle::DetachFromSeat(ADSTogetherCharacter* Player)
{
	// 마찬가지
}

bool ADST_Vehicle::TryGetOff(ADSTogetherCharacter* Player)
{
	// 유니티에서 했던것처럼 차량밖에 적정 위치 설정해서 스폰하게 하기 ?
	return false;
}

void ADST_Vehicle::OnThrottle(const FInputActionValue& Value)
{
	ThrottleInput = FMath::Clamp(Value.Get<float>(), 0.f, 1.f);
}

void ADST_Vehicle::OnThrottleReleased(const FInputActionValue& Value)
{
	ThrottleInput = 0.f;
}

void ADST_Vehicle::OnBrakeReleased(const FInputActionValue& Value)
{
	BrakeInput = 0.f;
}



