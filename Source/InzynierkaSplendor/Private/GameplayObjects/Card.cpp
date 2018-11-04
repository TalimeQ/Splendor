

#include "Card.h"

#include "Public/SplendorPlayerController.h"



void ACard::OnRaycast()
{
	OnCardRequest.Broadcast();
}
void ACard::BeginPlay()
{
	Super::BeginPlay();
	cardParams = FCardStruct();
}
bool ACard::CheckIfBuyable(ASplendorPlayerController* playerRef)
{
	if(!playerRef)
	{
		return false;
	}
	return playerRef->CheckBudget(this->cardParams.cardCost);
}
void ACard::CardBuy(ASplendorPlayerController* buyingPlayer)
{
	if (!buyingPlayer)
	{
		return;
	}
	buyingPlayer->BuyCard(this->cardParams.cardBonus,this->cardParams.prestige);
}
	