

#include "Card.h"
#include "Public/Player/SplendorPlayerState.h"
#include "UnrealNetwork.h"
#include "Runtime/Engine/Classes/Engine/World.h"
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
	//

	if(Role == ROLE_Authority)
	{
		this->InitCard();
		this->VisualizeCard();
	}
	else
	{
		Cast<ASplendorPlayerController>(this->GetWorld()->GetFirstPlayerController())->CallInitCard(this);
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
}
void ACard::GoldCardBuy(ASplendorPlayerController* buyingPlayer)
{
	buyingPlayer->BuyCard(this->cardParams.cardBonus, this->cardParams.cardCost, this->cardParams.prestige, true, tokenStashRef);
	buyingPlayer->CallUpdateCard(this);
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

	playerRef->ReserveCard(&(this->cardParams),tokenStashRef);
	
	playerRef->CallUpdateCard(this);

}
void  ACard::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ACard, cardParams);
}
void ACard::OnRep_VisualizeCard()
{

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
	if (ownedCardStackRef->GetCardStackCount() <= ownedCardStackRef->GetInitialCardStackCount() - cardsInTier)
	{
		ownedCardStackRef->RequestReset();
	}
	this->cardParams = ownedCardStackRef->GetStartingCard();
	VisualizeCard();

}
void ACard::UpdateCard()
{
	if (!ownedCardStackRef)
	{
		UE_LOG(LogTemp, Warning, TEXT("Card :: Seems like you have forgotten to set owning card stack reference for %s"), *(this->GetName()));
		this->Destroy();
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
	VisualizeCard();
}
FCardStruct  ACard::GetCardParams()
{
	return cardParams;
}
