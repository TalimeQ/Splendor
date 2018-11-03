

#pragma once

#include "CoreMinimal.h"
#include "GameplayObjects/Interactable.h"
#include "CardStack.generated.h"



/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCardStackRequest);

UCLASS(BlueprintType, Blueprintable)
class INZYNIERKASPLENDOR_API ACardStack : public AInteractable
{
	GENERATED_BODY()
	
	
public:
	UPROPERTY(BlueprintAssignable)
		FOnCardStackRequest OnCardStackRequest;
	virtual void OnRaycast() override;
};
