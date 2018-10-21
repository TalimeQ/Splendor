

#include "Public/GameplayObjects/TokenStash.h"


ATokenStash::ATokenStash()
{
	/* Should be changed based on amount of players
	2 player -> 4 gems of each
	3 player -> 5 gems of each
	4 player -> 7 gems of each
	
	*/
	tokenPool = FTokenStruct(7, 5);
}

void ATokenStash::OnRaycast()
{
	OnTokenRequest.Broadcast();
}
void ATokenStash::BeginPlay()
{
	Super::BeginPlay();

}