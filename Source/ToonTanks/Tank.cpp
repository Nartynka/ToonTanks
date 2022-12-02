// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

ATank::ATank()
{
   PrimaryActorTick.bCanEverTick = true;

   SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Arm"));
	SpringArm->SetupAttachment(RootComponent);
   Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}