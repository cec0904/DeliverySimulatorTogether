// Fill out your copyright notice in the Description page of Project Settings.


#include "DST/Character/DST_Character.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DSTogether.h"
#include "DST/Interaction/DSTInteractable.h"
#include "DST/Cargo/DSTCargo.h"
#include "Components/SceneComponent.h"
#include "Engine/World.h"

// Sets default values
ADST_Character::ADST_Character()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// Create the first person mesh that will be viewed only by this character's owner
	FirstPersonMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("First Person Mesh"));

	FirstPersonMesh->SetupAttachment(GetMesh());
	FirstPersonMesh->SetOnlyOwnerSee(true);
	FirstPersonMesh->FirstPersonPrimitiveType = EFirstPersonPrimitiveType::FirstPerson;
	FirstPersonMesh->SetCollisionProfileName(FName("NoCollision"));

	// Create the Camera Component	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("First Person Camera"));
	FirstPersonCameraComponent->SetupAttachment(FirstPersonMesh, FName("head"));
	FirstPersonCameraComponent->SetRelativeLocationAndRotation(FVector(-2.8f, 5.89f, 0.0f), FRotator(0.0f, 90.0f, -90.0f));
	FirstPersonCameraComponent->bUsePawnControlRotation = true;
	FirstPersonCameraComponent->bEnableFirstPersonFieldOfView = true;
	FirstPersonCameraComponent->bEnableFirstPersonScale = true;
	FirstPersonCameraComponent->FirstPersonFieldOfView = 70.0f;
	FirstPersonCameraComponent->FirstPersonScale = 0.6f;

	// configure the character comps
	GetMesh()->SetOwnerNoSee(true);
	GetMesh()->FirstPersonPrimitiveType = EFirstPersonPrimitiveType::WorldSpaceRepresentation;

	GetCapsuleComponent()->SetCapsuleSize(34.0f, 96.0f);

	// Configure character movement
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;
	GetCharacterMovement()->AirControl = 0.5f;

	HoldPoint = CreateDefaultSubobject<USceneComponent>(TEXT("HoldPoint"));
	HoldPoint->SetupAttachment(GetRootComponent());
	HoldPoint->SetRelativeLocation(FVector(100.f, 0.f, 40.f));
}

void ADST_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ADST_Character::DoJumpStart);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ADST_Character::DoJumpEnd);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ADST_Character::MoveInput);

		// Looking/Aiming
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ADST_Character::LookInput);
		EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &ADST_Character::LookInput);

		EnhancedInputComponent->BindAction(InteractDoorAction, ETriggerEvent::Started, this, &ADST_Character::InteractDoor);
		EnhancedInputComponent->BindAction(InteractItemAction, ETriggerEvent::Started, this, &ADST_Character::InteractItem);
		EnhancedInputComponent->BindAction(CommunicateAction, ETriggerEvent::Started, this, &ADST_Character::Communicate);
	}
	else
	{
		UE_LOG(LogDSTogether, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ADST_Character::InteractDoor()
{

}

void ADST_Character::InteractItem()
{
	// 물건을 들고 있으면 내려놓기
	if (IsValid(HeldItem))
	{
		if (HeldItem->Drop())
		{
			HeldItem = nullptr;
		}
		return;
	}

	// 빈손이면 시선 방향으로 대상 찾기
	FVector ViewLocation;
	FRotator ViewRotation;
	GetActorEyesViewPoint(ViewLocation, ViewRotation);

	FVector TraceEnd = ViewLocation + ViewRotation.Vector() * InteractionDistance;
	FHitResult Hit;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	if (!GetWorld()->LineTraceSingleByChannel(Hit, ViewLocation, TraceEnd, ECC_Visibility, Params)) return;

	AActor* Target = Hit.GetActor();
	if (!IsValid(Target)) return;
	if (!Target->GetClass()->ImplementsInterface(UDSTInteractable::StaticClass())) return;

	// 대상 종류를 구분하지 않고 상호작용 요청
	IDSTInteractable::Execute_Interact(Target, this);
}

void ADST_Character::Communicate()
{
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


void ADST_Character::MoveInput(const FInputActionValue& Value)
{
	// get the Vector2D move axis
	FVector2D MovementVector = Value.Get<FVector2D>();

	// pass the axis values to the move input
	DoMove(MovementVector.X, MovementVector.Y);

}

void ADST_Character::LookInput(const FInputActionValue& Value)
{
	// get the Vector2D look axis
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	// pass the axis values to the aim input
	DoAim(LookAxisVector.X, LookAxisVector.Y);

}

void ADST_Character::DoAim(float Yaw, float Pitch)
{
	if (GetController())
	{
		// pass the rotation inputs
		AddControllerYawInput(Yaw);
		AddControllerPitchInput(Pitch);
	}
}

void ADST_Character::DoMove(float Right, float Forward)
{
	if (GetController())
	{
		// pass the move inputs
		AddMovementInput(GetActorRightVector(), Right);
		AddMovementInput(GetActorForwardVector(), Forward);
	}
}

void ADST_Character::DoJumpStart()
{
	// pass Jump to the character
	Jump();
}

void ADST_Character::DoJumpEnd()
{
	// pass StopJumping to the character
	StopJumping();
}

void ADST_Character::InteractInput(const FInputActionValue& Value)
{
}
