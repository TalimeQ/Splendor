// Fill out your copyright notice in the Description page of Project Settings.

#include "InzynierkaSplendorGameModeBase.h"
#include "UnrealNetwork.h"
#include "InzynierkaSplendor/Public/SplendorGameState.h"

void AInzynierkaSplendorGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	this->stateRef = Cast<ASplendorGameState>(this->GameState);
	this->stateRef->Initialize();
	UE_LOG(LogTemp, Warning, TEXT("Begin Play"));
}
void  AInzynierkaSplendorGameModeBase::ProcessTurnInfo()
{
	UE_LOG(LogTemp, Warning, TEXT("Wlazlem do processturn"))
	if (Role != ROLE_Authority)
	{
		ServerProcessTurnInfo();
	}
	else
	{
		stateRef->NextTurn();
	}
}
void AInzynierkaSplendorGameModeBase::ServerProcessTurnInfo_Implementation()
{
	ProcessTurnInfo();
}
bool  AInzynierkaSplendorGameModeBase::ServerProcessTurnInfo_Validate()
{
	return true;
}

