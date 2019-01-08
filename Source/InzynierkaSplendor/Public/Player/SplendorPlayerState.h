

#pragma once
/*TODO : add prestige counter 
add references to stored cards maybe?:)
add references to cards that have been bought ;)


*/
#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Public/GameplayObjects/TokenStruct.h"
#include "Public/GameplayObjects/TokenStash.h"
#include "Public/GameplayObjects/CardStack.h"
#include "Public/ChatHUD.h"
#include "SplendorPlayerState.generated.h"



class ASplendorPlayerController;
/**
 * 
 */
UCLASS()
class INZYNIERKASPLENDOR_API ASplendorPlayerState : public APlayerState
{
	GENERATED_BODY()
private:
		UPROPERTY(Replicated)
		TArray<FCardStruct>  reservedCards;
		UPROPERTY(Replicated,VisibleAnywhere)
		FTokenStruct playerTokens;
		UPROPERTY(Replicated,VisibleAnywhere)
		FTokenStruct playerBonuses;
		UPROPERTY(Replicated)
		int prestige;
		UPROPERTY(Replicated)
		bool bIsTurn = false;
		UFUNCTION(Server, Reliable, WithValidation)
		void ServerSetPlayerPrestige(int newPrestige);
		UPROPERTY(Replicated)
		bool bIsFinished = false;
protected:
	UPROPERTY(BlueprintReadOnly)
		ATokenStash* tokenStashRef = nullptr;
public:
	ASplendorPlayerState();
	UFUNCTION(BlueprintPure)
	FTokenStruct GetPlayerTokens();
	UFUNCTION(BlueprintPure)
	TArray<FCardStruct> GetReservedCards();
	void SetPlayerTokens(FTokenStruct newTokenValue);
	UFUNCTION(BlueprintPure)
	int ReturnNumberOfCards();
	void ReserveCard(FCardStruct cardValues,ATokenStash* tokenStashRef);
	UFUNCTION(BlueprintCallable)
	void BuyReservedCard(int cardIndex, bool bIsWithGold, ASplendorPlayerController* playerCont, ATokenStash* tokenStashPoint);
	void SetPlayerBonus(FTokenStruct newBonus);
	UFUNCTION(BlueprintPure)
	FTokenStruct GetPlayerBudget();
	UFUNCTION(BlueprintPure)
	FTokenStruct GetPlayerBonuses();
	UFUNCTION(BlueprintPure)
	int GetPlayerPrestige();
	void SetPlayerPrestige(int newPrestige);
	void SetTurnStatus(bool bNewTurnStatus);
	UFUNCTION(BlueprintPure)
	bool GetTurnStatus();

	
	void SetFinished();
	bool GetFinishedStatus();

	UFUNCTION(Server, Reliable, WithValidation)
		void ServerSetTokens(FTokenStruct newTokenValue);
	UFUNCTION(Server, Reliable, WithValidation)
		void ServerSetBonus(FTokenStruct newTokenValue);
	UFUNCTION(Server, Reliable, WithValidation)
		void ServerReserveCard(FCardStruct cardValues);
	UFUNCTION(Server, Reliable, WithValidation)
		void ServerBuyReservedCard(int cardIndex, bool bIsWithGold, ASplendorPlayerController* playerCont, ATokenStash* tokenStashPoint);

	UFUNCTION(Server, Reliable, WithValidation) // for player to player rpc you need to first call the message on the server
		virtual void UserChatRPC(const FSChatMsg& newmessage); // first rpc for the server
	UFUNCTION(NetMulticast, Reliable, WithValidation) // then the server calls the function with a multicast that executes on all clients and the server
		virtual void UserChat(const FSChatMsg& newmessage); // second rpc for all the clients
	
};
