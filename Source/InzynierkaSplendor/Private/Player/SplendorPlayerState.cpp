

#include "SplendorPlayerState.h"
#include "Public/GameplayObjects/TokenStruct.h"
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
