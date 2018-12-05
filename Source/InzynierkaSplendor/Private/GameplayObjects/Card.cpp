

#include "Card.h"
#include "Public/Player/SplendorPlayerState.h"
#include "UnrealNetwork.h"
#include "Public/GameplayObjects/CardStack.h"
#include "Public/GameplayObjects/TokenStash.h"
#include "Public/SplendorPlayerController.h"



void ACard::OnRaycast()
{
	OnCardRequest.Broadcast();
}
void ACard::BeginPlay()
{
	Super::BeginPlay();
	cardParams = FCardStruct();
	if(Role == ROLE_Authority)
	{
		this->InitCard();
		this->VisualizeCard();
	}

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
	buyingPlayer->BuyCard(this->cardParams.cardBonus, this->cardParams.cardCost, this->cardParams.prestige, false, tokenStashRef);
	buyingPlayer->CallUpdateCard(this);
	// TODO :: Handle card destruction handle card destruction or refill
}
void ACard::GoldCardBuy(ASplendorPlayerController* buyingPlayer)
{
	buyingPlayer->BuyCard(this->cardParams.cardBonus, this->cardParams.cardCost, this->cardParams.prestige, true, tokenStashRef);
	buyingPlayer->CallUpdateCard(this);
	// TODO :: Handle card destruction handle card destruction or refill
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
    cost - playerBudget;
	cost.Count();
	UE_LOG(LogTemp, Warning, TEXT("Final player Token State ::  Rubies: %d , Diamonds: %d , Emeralds: %d , Sapphires: %d , Onyxes : %d "), cost.rubyTokens, cost.diamondTokens, cost.emeraldTokens, cost.sapphireTokens, cost.onyxTokens)
	UE_LOG(LogTemp, Warning, TEXT("%d"), cost.tokensTotal);
	if (cost.tokensTotal <= tempGoldStorage)
	{
	
		return true;
	}
	else
	{
		return false;
	}
}
void ACard::Reserve(ASplendorPlayerController* playerRef)
{
	//ASplendorPlayerState* playerState = Cast<ASplendorPlayerState>(playerRef->PlayerState);
	//playerState->ReserveCard(this->cardParams);
	playerRef->ReserveCard(&(this->cardParams));
	// TODO :: Handle card destruction handle card destruction or refill
	playerRef->CallUpdateCard(this);

}
void  ACard::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ACard, cardParams);
}
void ACard::OnRep_VisualizeCard()
{
	UE_LOG(LogTemp, Warning, TEXT("REPLICATING"));
	VisualizeCard();
	
}
void ACard::VisualizeCard_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("Card Visualized"));
}
void ACard::InitCard()
{
	if (!ownedCardStackRef)
	{
		UE_LOG(LogTemp, Warning, TEXT("Card :: Seems like you have forgotten to set owning card stack reference for %s"),*(this->GetName()));
	}
	this->cardParams = ownedCardStackRef->GetStartingCard();
}
void ACard::UpdateCard()
{
	if (!ownedCardStackRef)
	{
		UE_LOG(LogTemp, Warning, TEXT("Card :: Seems like you have forgotten to set owning card stack reference for %s"), *(this->GetName()));
	}
	this->cardParams = ownedCardStackRef->GetStartingCard();
	if(Role = ROLE_Authority)
	{
		VisualizeCard();
	}
}
void  ACard::ResetCardParams(FCardStruct newCardParams)
{
	cardParams = newCardParams;
}