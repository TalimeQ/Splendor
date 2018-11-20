

#include "SplendorPlayerState.h"
#include "Public/GameplayObjects/TokenStruct.h"
#include "Public/SplendorPlayerController.h"
#include "UnrealNetwork.h"
#include "Public/GameplayObjects/CardStack.h"
#include "Public/GameplayObjects/TokenStash.h"

ASplendorPlayerState::ASplendorPlayerState()
{
	playerTokens = new FTokenStruct();
	playerBonuses = new FTokenStruct();
}
FTokenStruct ASplendorPlayerState::GetPlayerTokens()
{

	return *playerTokens;
}
/*
Sets the amount of player tokens to the one provided in function parameter. Yes that means do calculations out of this place :)
*/
void ASplendorPlayerState::SetPlayerTokens(FTokenStruct newTokenValue)
{
	if(ROLE_Authority){
	playerTokens->setParams(newTokenValue);
	UE_LOG(LogTemp, Warning, TEXT("NEW PLAYER TOKEN STATE D: %d , E: %d, S: %d, O: %d, R: %d "), playerTokens->diamondTokens, playerTokens->emeraldTokens,playerTokens->sapphireTokens, playerTokens->onyxTokens, playerTokens->rubyTokens)
	}
}
int ASplendorPlayerState::ReturnNumberOfCards()
{
	return reservedCards.Num();
}
void ASplendorPlayerState::ReserveCard(FCardStruct CardValues)
{
	if(Role == ROLE_Authority)
	{ 
	FCardStruct* tempCardPtr = new FCardStruct();
	tempCardPtr->cardBonus = CardValues.cardBonus;
	tempCardPtr->cardCost = CardValues.cardCost;
	tempCardPtr->prestige = CardValues.prestige;
	reservedCards.Add(tempCardPtr);
	}
}
void ASplendorPlayerState::BuyReservedCard(int cardIndex)
{
	//theoretical implementation soon :) after i get my game interface.....
}
void ASplendorPlayerState::SetPlayerPrestige(int newPrestige)
{
	if (Role == ROLE_Authority)
	{
		prestige = newPrestige;
	}
}
int ASplendorPlayerState::GetPlayerPrestige()
{
	return prestige;
}
FTokenStruct ASplendorPlayerState::GetPlayerBonuses()
{
	return *playerBonuses;
}
FTokenStruct ASplendorPlayerState::GetPlayerBudget()
{
	FTokenStruct tempBonus = *playerBonuses;
	FTokenStruct tempTokens = *playerTokens;
	FTokenStruct Budget = tempBonus + tempTokens;
	UE_LOG(LogTemp, Warning, TEXT("PLayerstate gold: %d , %d"), Budget.goldTokens,playerBonuses->goldTokens);
	return Budget;
}
void ASplendorPlayerState::SetPlayerBonus(FTokenStruct newBonus)
{
	if (Role == ROLE_Authority)
	{
	playerBonuses->setParams(newBonus);
	}
	UE_LOG(LogTemp,Warning,TEXT("NEW PLAYER BONUSES D: %d , E: %d, S: %d, O: %d, R: %d "),playerBonuses->diamondTokens,playerBonuses->emeraldTokens, playerBonuses->sapphireTokens,playerBonuses->onyxTokens, playerBonuses->rubyTokens)
}
void  ASplendorPlayerState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ASplendorPlayerState,bIsTurn);
	DOREPLIFETIME(ASplendorPlayerState,prestige);
}
void  ASplendorPlayerState::SetTurnStatus(bool bNewTurnStatus)
{
	if (Role == ROLE_Authority)
	{
		
		this->bIsTurn = bNewTurnStatus;
		UE_LOG(LogTemp, Warning, TEXT("Turn changed %s"),( bIsTurn ? TEXT("TRUE") : TEXT("FALSE")))
	}
}
bool ASplendorPlayerState::GetTurnStatus()
{
	return bIsTurn;
}