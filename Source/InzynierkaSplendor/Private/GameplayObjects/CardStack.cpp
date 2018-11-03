#include "CardStack.h"
#include "UnrealMathUtility.h"
#include "Public/SplendorPlayerController.h"
#include "Public/GameplayObjects/TokenStash.h"
#include "Public/Player/SplendorPlayerState.h"
#include "Runtime/Engine/Classes/Engine/World.h"

void ACardStack::BeginPlay()
{
	Super::BeginPlay();
	FGenericPlatformMath::SRandInit(FDateTime::Now().ToUnixTimestamp());
	ShuffleCards();
}
void ACardStack::OnRaycast()
{
	//TODO :: NETWORKING POINT, that thing below works for single atm :<
	ASplendorPlayerController* splendorCont = Cast<ASplendorPlayerController>(this->GetWorld()->GetFirstPlayerController());
	if (splendorCont)
	{
		splendorCont->ToggleInput();
	}
	OnCardStackRequest.Broadcast();
}
void ACardStack::ProcessReservationRequest(ASplendorPlayerController *requestingPlayer, bool isForced)
{
	// Check if player can reserve cards , has slots to do it
	if (!requestingPlayer) return;
	if (!requestingPlayer->CheckIfCanReserve())
	{
		UE_LOG(LogTemp, Warning, TEXT("You are already on maxed reserve BBy"));
		return;
	}
	ASplendorPlayerState* playerState = Cast<ASplendorPlayerState>(requestingPlayer->PlayerState);
	
	
	// Check if theres gold, ask if player still wants to reserve card
	if (!tokenStashRef || !playerState) return;
	else if (isForced)
	{
		ReserveCard(playerState);
		return;
	}
	else if (tokenStashRef->CheckIfTokensAvailable(5, 1))
	{
		//Reserve Card if there was gold
		AddGold(requestingPlayer);
		ReserveCard(playerState);

		
	}
	else
	{
		NoGoldMessage.Broadcast();
	}



	
}
void ACardStack::ShuffleCards()
{
	// Should shuffle decently enough
	for (uint32 i = storedCards.Num() -1; i > 0; i--)
	{
		int32 index = FMath::FloorToInt(FMath::Rand() * (i + 1) % storedCards.Num());
		FCardStruct temp = storedCards[i];
		storedCards[i] = storedCards[index];
		storedCards[index] = temp;

	}
}
void ACardStack::AddGold(ASplendorPlayerController *requestingPlayer)
{
	TArray<int32> goldToken; // token stash function takes TArray of ints as param 
	goldToken.Add(5); // 5 is the number of gold token
	tokenStashRef->ProcessTokenRequest(goldToken, requestingPlayer);
}
void ACardStack::ReserveCard(ASplendorPlayerState *requestingPlayerState)
{
	FCardStruct cardToReserve = storedCards.Pop(true);
	requestingPlayerState->ReserveCard(cardToReserve);
	UE_LOG(LogTemp, Warning, TEXT("Cards remaining %d"), storedCards.Num());
	if (storedCards.Num() <= 0)
	{
		this->Destroy();
	}
}