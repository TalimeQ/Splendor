

#pragma once

#include "CoreMinimal.h"
#include "GameplayObjects/Interactable.h"
#include "GameplayObjects/TokenStruct.h"
#include "TokenStash.generated.h"


/**
*
*/
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTokenRequest);

UCLASS(BlueprintType, Blueprintable)
class INZYNIERKASPLENDOR_API ATokenStash : public AInteractable
{
	GENERATED_BODY()
private:
	FTokenStruct tokenPool;
	virtual void BeginPlay() override;
public:

	ATokenStash();
	virtual void OnRaycast() override;
	UFUNCTION(BlueprintCallable, Category = "Tokens")
	void ProcessTokenRequest(TArray<int> requestedTokens, ASplendorPlayerController* playerContRef);
	/* Checks if token can be taken in amount of 2 or not
	@param int tokenNumber
	-> 0 ruby
	-> 1 emerald
	-> 2 diamond
	-> 3 onyx
	-> 4 sapphire
	-> 5 gold
	@param int checkedAmount
	amount to which we compare the number of gems in stash,

	Returns true if the amount of gems in stash is greater or equal to the amount passed in argument 
	*/
	UFUNCTION(BlueprintCallable, Category = "Tokens")
		bool CheckIfTokensAvailable(int tokenNumber,int checkedAmount);

	UPROPERTY(BlueprintAssignable)
		FOnTokenRequest OnTokenRequest;

};
