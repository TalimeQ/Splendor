

#pragma once

#include "CoreMinimal.h"
#include "GameplayObjects/Interactable.h"
#include "CardStruct.h"
#include "Card.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCardRequest);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FChangeCardVisuals);
class ATokenStash;
class ACardStack;


UCLASS()
class INZYNIERKASPLENDOR_API ACard : public AInteractable
{
	GENERATED_BODY()

private:

		virtual void BeginPlay() override;
		bool IsOneGoldAway(FTokenStruct cost, ASplendorPlayerController* playerRef);
		
protected:
	UPROPERTY(EditAnywhere, ReplicatedUsing = OnRep_VisualizeCard, BlueprintReadOnly)
		FCardStruct cardParams;
	UPROPERTY(BlueprintAssignable)
		FOnCardRequest OnCardRequest;
	UPROPERTY(BlueprintAssignable)
		FChangeCardVisuals ChangeCardVisuals;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		ATokenStash* tokenStashRef;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		ACardStack * ownedCardStackRef;

	UFUNCTION()
		 void  OnRep_VisualizeCard();
	UFUNCTION(BlueprintNativeEvent)
		// Implemented in blueprints
	void VisualizeCard();
	virtual void VisualizeCard_Implementation();

	void InitCard();

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
	UFUNCTION()
		void UpdateCard();
};
