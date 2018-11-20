

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
class ASplendorPlayerController;
/**
 * 
 */
UCLASS()
class INZYNIERKASPLENDOR_API ASplendorPlayerState : public APlayerState
{
	GENERATED_BODY()
private:
		//UPROPERTY(Replicated)
		TArray<FCardStruct*>  reservedCards;
		//UPROPERTY(Replicated) TODO :replication maybe
		FTokenStruct *playerTokens = nullptr;
		//UPROPERTY(Replicated) TODO :replication maybe
		FTokenStruct *playerBonuses = nullptr;
		UPROPERTY(Replicated)
		int prestige;
		UPROPERTY(Replicated)
		bool bIsTurn = false;

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
	void SetTurnStatus(bool bNewTurnStatus);
	bool GetTurnStatus();
};
