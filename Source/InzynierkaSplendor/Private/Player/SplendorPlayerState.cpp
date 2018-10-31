

#include "SplendorPlayerState.h"
#include "Public/GameplayObjects/TokenStash.h"

ASplendorPlayerState::ASplendorPlayerState()
{
	playerTokens = FTokenStruct();
}
FTokenStruct ASplendorPlayerState::GetPlayerTokens()
{
	return playerTokens;
}
/*
Sets the amount of player tokens to the one provided in function parameter. Yes that means do calculations out of this place :)
*/
void ASplendorPlayerState::SetPlayerTokens(FTokenStruct newTokenValue)
{
	playerTokens = newTokenValue;
}
