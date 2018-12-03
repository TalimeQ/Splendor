

#pragma once

#include "CoreMinimal.h"
#include "GameplayObjects/Interactable.h"
#include "TokenStruct.h"
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
	UPROPERTY(ReplicatedUsing=OnRep_VisualizeTokens)
	FTokenStruct tokenPool;
	virtual void BeginPlay() override;

	// For visuals ;)
	UPROPERTY(EditInstanceOnly,  Category = "Visuals")
		AActor* diamondTokenBottom;
	UPROPERTY(EditInstanceOnly, Category = "Visuals")
		AActor* rubyTokenBottom;
	UPROPERTY(EditInstanceOnly, Category = "Visuals")
		AActor* goldTokenBottom;
	UPROPERTY(EditInstanceOnly, Category = "Visuals")
		AActor* emeraldTokenBottom;
	UPROPERTY(EditInstanceOnly, Category = "Visuals")
		AActor* sapphireTokenBottom;
	UPROPERTY(EditInstanceOnly, Category = "Visuals")
		AActor* onyxTokenBottom;
	UFUNCTION()
	void OnRep_VisualizeTokens();
	void VisualizeTokens();

public:

	ATokenStash();
	virtual void OnRaycast() override;
	UFUNCTION(BlueprintCallable, Category = "Tokens")
	void ProcessTokenRequest(TArray<int>requestedTokens , ASplendorPlayerController* playerContRef);

	UFUNCTION(BlueprintCallable)
	void SetTokenAmount(FTokenStruct deductedTokenAmount);
	// privatize it?
	UFUNCTION(reliable, server, WithValidation)
	void ServerSetTokenAmount(FTokenStruct deductedTokenAmount);


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
