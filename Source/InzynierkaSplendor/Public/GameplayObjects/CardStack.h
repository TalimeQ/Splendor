

#pragma once

#include "CoreMinimal.h"
#include "GameplayObjects/Interactable.h"
#include "CardStruct.h"
#include "Public/GameplayObjects/TokenStruct.h"
#include "CardStack.generated.h"

class ATokenStash;
class ASplendorPlayerState;

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
	UPROPERTY(EditAnywhere)
	TArray<FCardStruct> storedCards;
	UPROPERTY(EditAnywhere)
	ATokenStash* tokenStashRef;
	void ShuffleCards();
	void AddGold(ASplendorPlayerController *requestingPlayer);
	void ReserveCard(ASplendorPlayerState *requestingPlayerState);
public:
	UPROPERTY(BlueprintAssignable)
		FOnCardStackRequest OnCardStackRequest;
	UPROPERTY(BlueprintAssignable)
		FNoGoldMessage NoGoldMessage;
	virtual void OnRaycast() override;
	UFUNCTION(BlueprintCallable)
	void ProcessReservationRequest(ASplendorPlayerController *requestingPlayer, bool isForced);
	virtual void BeginPlay() override;
	
};
