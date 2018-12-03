#include "SplendorGameState.h"
#include "InzynierkaSplendor/Public/Player/SplendorPlayerState.h"
#include "UnrealMathUtility.h"
#include "UnrealNetwork.h"



ASplendorGameState::ASplendorGameState()
{
	this->CurrentState = ECurrentGameState::EUnknown;
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

}
void ASplendorGameState::RandomizeTurnOrder()
{
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
	if(CurrentState == ECurrentGameState::EPlaying || ECurrentGameState::ELastTurn)
	{ 
		playerTurnOrder[currentPlayer]->SetTurnStatus(false);
		currentPlayer++;
		if (currentPlayer >= playerTurnOrder.Num()) currentPlayer = 0;
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