

#pragma once
/*TODO : add prestige counter 
add references to stored cards maybe?:)
add references to cards that have been bought ;)


*/
#include "CoreMinimal.h"
/*
TODO: Struct refactor point
*/
#include "Public/GameplayObjects/TokenStash.h"
#include "GameFramework/PlayerState.h"
#include "SplendorPlayerState.generated.h"


/**
 * 
 */
UCLASS()
class INZYNIERKASPLENDOR_API ASplendorPlayerState : public APlayerState
{
	GENERATED_BODY()


		FTokenStruct playerTokens;
public:
	ASplendorPlayerState();
	FTokenStruct GetPlayerTokens();
	void SetPlayerTokens(FTokenStruct newTokenValue);
};
