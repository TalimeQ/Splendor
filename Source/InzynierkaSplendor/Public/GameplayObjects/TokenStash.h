

#pragma once

#include "CoreMinimal.h"
#include "GameplayObjects/Interactable.h"
#include "TokenStash.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTokenRequest);

UCLASS(BlueprintType, Blueprintable)
class INZYNIERKASPLENDOR_API ATokenStash : public AInteractable
{
	GENERATED_BODY()
	
public:


	virtual void OnRaycast() override;

	UPROPERTY(BlueprintAssignable)
		FOnTokenRequest OnTokenRequest;

};
