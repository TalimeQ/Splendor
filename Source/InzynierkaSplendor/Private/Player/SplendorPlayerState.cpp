

#include "SplendorPlayerState.h"
#include "Public/GameplayObjects/TokenStruct.h"
//TODO :: Refactor point, move struct to single .h file
#include "Public/GameplayObjects/CardStack.h"
#include "Public/GameplayObjects/TokenStash.h"

ASplendorPlayerState::ASplendorPlayerState()
{
	playerTokens = new FTokenStruct();
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