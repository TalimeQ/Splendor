

#pragma once

#include "CoreMinimal.h"
#include "GameplayObjects/Interactable.h"
#include "CardStruct.h"
#include "Public/GameplayObjects/TokenStruct.h"
#include "CardStack.generated.h"

class ATokenStash;


class ASplendorPlayerController;
/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCardStackRequest);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FNoGoldMessage);

UCLASS(BlueprintType, Blueprintable)
class INZYNIERKASPLENDOR_API ACardStack : public AInteractable
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere,Replicated)
	TArray<FCardStruct> storedCards;
	// Kept in case of reinitialization
	TArray<FCardStruct> copyOfStoredCards;
	UPROPERTY(EditAnywhere)
	ATokenStash* tokenStashRef;
	void ShuffleCards();
	void AddGold(ASplendorPlayerController *requestingPlayer);
	void ReserveCard(ASplendorPlayerController *requestingPlayer);
public:
	ACardStack();
	UPROPERTY(BlueprintAssignable)
		FOnCardStackRequest OnCardStackRequest;
	UPROPERTY(BlueprintAssignable)
		FNoGoldMessage NoGoldMessage;
	virtual void OnRaycast() override;
	UFUNCTION(BlueprintCallable)
	void ProcessReservationRequest(ASplendorPlayerController *requestingPlayer, bool isForced);
	FCardStruct GetStartingCard();
	virtual void BeginPlay() override;
	/*
	Called when client pops a reserved card from stack.
	*/
	int GetCardStackCount();
	int GetInitialCardStackCount();
	void RequestReset();
	void PopCardArray();
	UFUNCTION(Server, reliable,WithValidation)
	void ServerPopCardArray();
};
