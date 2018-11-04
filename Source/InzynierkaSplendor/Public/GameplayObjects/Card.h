

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
protected:

	UPROPERTY(BlueprintAssignable)
		FOnCardRequest OnCardRequest;

public:
	virtual void OnRaycast() override;
	UFUNCTION(BlueprintCallable)
	bool CheckIfBuyable(ASplendorPlayerController* playerRef);
	UFUNCTION(BlueprintCallable)
	void CardBuy(ASplendorPlayerController* buyingPlayer);
};
