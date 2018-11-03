

#pragma once

#include "CoreMinimal.h"
#include "GameplayObjects/Interactable.h"
//#include "Public/GameplayObjects/CardStruct.h"
#include "CardStack.generated.h"


//struct FCardStruct;
class ASplendorPlayerController;
/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCardStackRequest);

UCLASS(BlueprintType, Blueprintable)
class INZYNIERKASPLENDOR_API ACardStack : public AInteractable
{
	GENERATED_BODY()
	
private:
	//UPROPERTY(EditDefaultsOnly)
		// TArray<FCardStruct> storedCards;
public:
	UPROPERTY(BlueprintAssignable)
		FOnCardStackRequest OnCardStackRequest;
	virtual void OnRaycast() override;
	void ProcessReservationRequest(ASplendorPlayerController *requestingPlayer);
};
