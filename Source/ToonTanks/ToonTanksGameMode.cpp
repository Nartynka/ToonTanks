// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"
#include "ToonTanksPlayerController.h"

void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
   if(DeadActor == Tank)
   {
      Tank->HandleDestruction();
      if(ToonTanksPlayerController)
         ToonTanksPlayerController->SetPlayerEnabledState(false);
      GameOver(false);
   } else if(ATower* DestroyedTower = Cast<ATower>(DeadActor))
   {
      DestroyedTower->HandleDestruction();
      TowersLeft--;
      if (TowersLeft == 0)
         GameOver(true);
   }
}

void AToonTanksGameMode::BeginPlay()
{
   Super::BeginPlay();
   HandleGameStart();

   UE_LOG(LogTemp, Error, TEXT("AAA: %i"), GetTowerCount());
}

void AToonTanksGameMode::HandleGameStart()
{
   TowersLeft = GetTowerCount();
   Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
   ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

   StartGame();

   if(!ToonTanksPlayerController) 
      return;
   
   ToonTanksPlayerController->SetPlayerEnabledState(false);

   FTimerHandle TimerHandle;
   FTimerDelegate InputDelegate = FTimerDelegate::CreateUObject(ToonTanksPlayerController, &AToonTanksPlayerController::SetPlayerEnabledState, true);
   GetWorldTimerManager().SetTimer(TimerHandle, InputDelegate, StartDelay, false);
}

int32 AToonTanksGameMode::GetTowerCount()
{
   TArray<AActor*> Towers;
   UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), Towers);
   return Towers.Num();
}
