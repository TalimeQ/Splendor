

#include "SplendorPlayerState.h"
#include "Public/GameplayObjects/TokenStruct.h"
//TODO :: Refactor point, move struct to single .h file
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
	playerTokens->setParams(newTokenValue);
	UE_LOG(LogTemp, Warning, TEXT("NEW PLAYER TOKEN STATE D: %d , E: %d, S: %d, O: %d, R: %d "), playerTokens->diamondTokens, playerTokens->emeraldTokens,playerTokens->sapphireTokens, playerTokens->onyxTokens, playerTokens->rubyTokens)
}
int ASplendorPlayerState::ReturnNumberOfCards()
{
	return reservedCards.Num();
}
void ASplendorPlayerState::ReserveCard(FCardStruct CardValues)
{
	FCardStruct* tempCardPtr = new FCardStruct();
	tempCardPtr->cardBonus = CardValues.cardBonus;
	tempCardPtr->cardCost = CardValues.cardCost;
	tempCardPtr->prestige = CardValues.prestige;
	reservedCards.Add(tempCardPtr);
}
void ASplendorPlayerState::BuyReservedCard(int cardIndex)
{
	//theoretical implementation soon :) after i get my game interface.....
}
void ASplendorPlayerState::SetPlayerPrestige(int newPrestige)
{
	prestige = newPrestige;
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
	playerBonuses->setParams(newBonus);
	UE_LOG(LogTemp,Warning,TEXT("NEW PLAYER BONUSES D: %d , E: %d, S: %d, O: %d, R: %d "),playerBonuses->diamondTokens,playerBonuses->emeraldTokens, playerBonuses->sapphireTokens,playerBonuses->onyxTokens, playerBonuses->rubyTokens)
}