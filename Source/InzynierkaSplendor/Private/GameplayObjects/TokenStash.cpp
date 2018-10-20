

#include "Public/GameplayObjects/TokenStash.h"




void ATokenStash::OnRaycast()
{
	OnTokenRequest.Broadcast();
}
