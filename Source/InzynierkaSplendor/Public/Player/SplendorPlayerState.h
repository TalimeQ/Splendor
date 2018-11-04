

#pragma once
/*TODO : add prestige counter 
add references to stored cards maybe?:)
add references to cards that have been bought ;)


*/
#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "SplendorPlayerState.generated.h"

struct FTokenStruct;
struct FCardStruct;
/**
 * 
 */
UCLASS()
class INZYNIERKASPLENDOR_API ASplendorPlayerState : public APlayerState
{
	GENERATED_BODY()
private:
		TArray<FCardStruct*>  reservedCards;
		FTokenStruct *playerTokens = nullptr;
		FTokenStruct *playerBonuses = nullptr;
		int prestige;
public:
	ASplendorPlayerState();
	FTokenStruct GetPlayerTokens();
	void SetPlayerTokens(FTokenStruct newTokenValue);
	int ReturnNumberOfCards();
	void ReserveCard(FCardStruct cardValues);
	void BuyReservedCard(int cardIndex);
	void SetPlayerBonus(FTokenStruct newBonus);
	FTokenStruct GetPlayerBudget();
	FTokenStruct GetPlayerBonuses();
	int GetPlayerPrestige();
	void SetPlayerPrestige(int newPrestige);

};
