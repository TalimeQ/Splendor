// Fill out your copyright notice in the Description page of Project Settings.

#include "InzynierkaSplendorGameModeBase.h"
#include "UnrealNetwork.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "InzynierkaSplendor/Public/SplendorGameState.h"
#include "GameplayObjects/PatronCardVisualizer.h"
#include "Public/ChatHUD.h"
#include "Public/Player/SplendorPlayerState.h"
#include "InzynierkaSplendor/Public/SplendorGameState.h"

AInzynierkaSplendorGameModeBase::AInzynierkaSplendorGameModeBase()
{
	// assign our custom classes above their parents
	HUDClass = AChatHUD::StaticClass();
	PlayerStateClass = ASplendorPlayerState::StaticClass();

	/* use this is you wish to extend the c++ into a bp and assign the bp to the class
	static ConstructorHelpers::FClassFinder<AMyHUD> hudclassobj(TEXT("Blueprint'/MyHUD.MyHUD_C'"));
	if (hudclassobj.Class != NULL)
		HUDClass = hudclassobj.Class;

	static ConstructorHelpers::FClassFinder<AMyPlayerState> psclassobj(TEXT("Blueprint'/MyPlayerState.MyPlayerState_C'"));
	if (psclassobj.Class != NULL)
		PlayerStateClass = psclassobj.Class;
	*/
}

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

