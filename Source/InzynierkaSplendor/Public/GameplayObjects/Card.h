

#pragma once

#include "CoreMinimal.h"
#include "GameplayObjects/Interactable.h"
// TODO :: refactor point FCARDSTUCK
#include "Public/GameplayObjects/CardStack.h"
#include "Card.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCardRequest);


UCLASS()
class INZYNIERKASPLENDOR_API ACard : public AInteractable
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
		FCardStruct cardParams;
		virtual void BeginPlay() override;
		bool IsOneGoldAway(FTokenStruct cost, ASplendorPlayerController* playerRef);
protected:

	UPROPERTY(BlueprintAssignable)
		FOnCardRequest OnCardRequest;

public:
	virtual void OnRaycast() override;
	UFUNCTION(BlueprintCallable)
	void Reserve(ASplendorPlayerController* playerRef);
	UFUNCTION(BlueprintCallable)
	bool CheckIfBuyable(ASplendorPlayerController* playerRef);
	UFUNCTION(BlueprintCallable)
	bool CheckIfBuyableWithGold(ASplendorPlayerController* playerRef);
	UFUNCTION(BlueprintCallable)
	void CardBuy(ASplendorPlayerController* buyingPlayer);
	UFUNCTION(BlueprintCallable)
		void GoldCardBuy(ASplendorPlayerController* buyingPlayer);
};
