#include "SplendorGameState.h"
#include "InzynierkaSplendor/Public/Player/SplendorPlayerState.h"
#include "UnrealMathUtility.h"
#include "UnrealNetwork.h"



ASplendorGameState::ASplendorGameState()
{
	this->CurrentState = ECurrentGameState::EUnknown;
	FGenericPlatformMath::SRandInit(FDateTime::Now().ToUnixTimestamp());
}
void ASplendorGameState::BeginPlay()
{
	Super::BeginPlay();
	FGenericPlatformMath::SRandInit(FDateTime::Now().ToUnixTimestamp());

}
void ASplendorGameState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ASplendorGameState, CurrentState);
}
void  ASplendorGameState::OnRep_CurrentState()
{
	if (CurrentState != ECurrentGameState::EGameOver) return;
	GameFinalizer();
}
void ASplendorGameState::RandomizeTurnOrder()
{
	FGenericPlatformMath::SRandInit(FDateTime::Now().ToUnixTimestamp());
	if (Role != ROLE_Authority) return;
	for (uint32 i = PlayerArray.Num() - 1; i > 0; i--)
	{
		int32 index = FMath::FloorToInt(FMath::Rand() * (i + 1) % PlayerArray.Num());
		ASplendorPlayerState *temp = playerTurnOrder[i];
		playerTurnOrder[i] = playerTurnOrder[index];
		playerTurnOrder[index] = temp;

	}
}
void ASplendorGameState::InitializePlayerArray()
{
	if (Role != ROLE_Authority) return;
	for (ASplendorPlayerState* x : playerTurnOrder)
	{
		x->SetTurnStatus(false);
	}
	playerTurnOrder.Empty();
	for (int i = 0 ; i < PlayerArray.Num(); i++)
	{
		playerTurnOrder.Add(Cast<ASplendorPlayerState>(PlayerArray[i]));
	}

}
void ASplendorGameState::NextTurn()
{

	if (Role != ROLE_Authority) return;
	if(CurrentState == ECurrentGameState::EPlaying )
	{ 
		if (playerTurnOrder[currentPlayer]->GetPlayerPrestige() >= 15)
		{
			bLastTurn = true;
			playerTurnOrder[currentPlayer]->SetFinished();
		}
		else if (bLastTurn)
		{
			playerTurnOrder[currentPlayer]->SetFinished();
		}
		playerTurnOrder[currentPlayer]->SetTurnStatus(false);

		currentPlayer++;

		if (currentPlayer >= playerTurnOrder.Num()) currentPlayer = 0;
		if (playerTurnOrder[currentPlayer]->GetFinishedStatus())
		{
			// Player is already finished after getting 15+ prestige
			// Now game should finish
			CurrentState = ECurrentGameState::EGameOver;
			if (Role = ROLE_Authority) this->OnRep_CurrentState();
			return;
		}
		playerTurnOrder[currentPlayer]->SetTurnStatus(true);
		UE_LOG(LogTemp, Warning, TEXT("Next Turn current player %d"),currentPlayer);
	}

}
void ASplendorGameState::Initialize()
{
	
	if (Role != ROLE_Authority)
	{
		ServerInitialize();
	}
	else
	{ 
		InitializePlayerArray();
		RandomizeTurnOrder();
		this->CurrentState = ECurrentGameState::EPlaying;
		playerTurnOrder[currentPlayer]->SetTurnStatus(true);

	}
}
void ASplendorGameState::ServerInitialize_Implementation()
{

	Initialize();
}
bool ASplendorGameState::ServerInitialize_Validate()
{
	return true;
}
void ASplendorGameState::GameFinalizer_Implementation()
{
	UE_LOG(LogTemp, Error, TEXT("GRA SKONCZONA"))
}