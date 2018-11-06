

#include "Card.h"
#include "Public/Player/SplendorPlayerState.h"
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
	buyingPlayer->BuyCard(this->cardParams.cardBonus, this->cardParams.cardCost, this->cardParams.prestige, false);
}
void ACard::GoldCardBuy(ASplendorPlayerController* buyingPlayer)
{
	buyingPlayer->BuyCard(this->cardParams.cardBonus, this->cardParams.cardCost, this->cardParams.prestige, true);
}
bool ACard::CheckIfBuyableWithGold(ASplendorPlayerController* playerRef)
{
	FTokenStruct cardCost = this->cardParams.cardCost;
	
	return IsOneGoldAway(cardCost,playerRef);
}
bool ACard::IsOneGoldAway(FTokenStruct cost, ASplendorPlayerController* playerRef)
{
	FTokenStruct playerBudget = Cast<ASplendorPlayerState>(playerRef->PlayerState)->GetPlayerBudget();
	int tempGoldStorage = playerBudget.goldTokens;
	
	playerBudget.goldTokens = 0;
	FTokenStruct compared = cost - playerBudget;
	compared.Count();
	UE_LOG(LogTemp, Warning, TEXT("Player gold %d, compared %d"), tempGoldStorage,compared.Count())
	if (compared.tokensTotal <= tempGoldStorage)
	{
		return true;
	}
	else
	{
		return false;
	}
}