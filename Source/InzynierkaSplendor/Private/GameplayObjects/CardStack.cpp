#include "CardStack.h"
#include "UnrealMathUtility.h"
#include "UnrealNetwork.h"
#include "Public/SplendorPlayerController.h"
#include "Public/GameplayObjects/TokenStash.h"
#include "Public/Player/SplendorPlayerState.h"
#include "Runtime/Engine/Classes/Engine/World.h"

ACardStack::ACardStack()
{
	
	 FGenericPlatformMath::SRandInit(FDateTime::Now().ToUnixTimestamp());
	 ShuffleCards();
	 copyOfStoredCards = storedCards;
}
void ACardStack::BeginPlay()
{
	Super::BeginPlay();


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
	if (!tokenStashRef ) return;
	else if (isForced)
	{
		ReserveCard(requestingPlayer);
		return;
	}
	else if (tokenStashRef->CheckIfTokensAvailable(5, 1))
	{
		//Reserve Card if there was gold
		AddGold(requestingPlayer);
		ReserveCard(requestingPlayer);

		
	}
	else
	{
		NoGoldMessage.Broadcast();
	}



	
}
void ACardStack::ShuffleCards()
{
	// Should shuffle decently enough
	if (storedCards.Num() == 0) return;
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
void ACardStack::ReserveCard(ASplendorPlayerController *requestingPlayer)
{
	// We will ask server to pop it with removal instead 
	FCardStruct cardToReserve = storedCards.Pop(false);
	requestingPlayer->ReserveCard(&cardToReserve);
	requestingPlayer->CallRequestCardPop(this);

}
void  ACardStack::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ACardStack, storedCards);
}
void ACardStack::PopCardArray()
{
	if (Role != ROLE_Authority)
	{
		ServerPopCardArray();
	}
	else
	{
		this->storedCards.Pop(true);
		if (storedCards.Num() <= 0)
		{
			this->Destroy();
		}
	}
}
void ACardStack::ServerPopCardArray_Implementation()
{
	PopCardArray();
}
bool ACardStack::ServerPopCardArray_Validate()
{
	return true;
}
FCardStruct ACardStack::GetStartingCard()
{
	return storedCards.Pop(true);
}
int ACardStack::GetCardStackCount()
{
	return storedCards.Num();
}
int ACardStack::GetInitialCardStackCount()
{
	return copyOfStoredCards.Num();
}
void ACardStack::RequestReset()
{
	storedCards = copyOfStoredCards;
}