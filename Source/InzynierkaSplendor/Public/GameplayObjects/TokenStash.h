

#pragma once

#include "CoreMinimal.h"
#include "GameplayObjects/Interactable.h"
#include "TokenStash.generated.h"

/**
 *  Struct used to store token info
	TODO:: move it somewhere nice and clean, takes too much irrelevant to class space here
 */
USTRUCT() struct FTokenStruct {
	GENERATED_BODY()
	UPROPERTY()
		int emeraldTokens;
	UPROPERTY()
		int rubyTokens;
	UPROPERTY()
		int onyxTokens;
	UPROPERTY()
		int sapphireTokens;
	UPROPERTY()
		int diamondTokens;
	UPROPERTY()
		int goldTokens;
	
	UPROPERTY()
		int tokensTotal;
	

	// Properties should always be initialized from what i hear 
	FTokenStruct()
	{
		emeraldTokens = 0;
		rubyTokens = 0;
		onyxTokens = 0;
		sapphireTokens = 0;
		diamondTokens = 0;
		goldTokens = 0;
		tokensTotal = 0;
	}
	FTokenStruct(int normalTokens, int initGoldTokens)
	{
		emeraldTokens = normalTokens;
		rubyTokens = normalTokens;
		onyxTokens = normalTokens;
		sapphireTokens = normalTokens;
		diamondTokens = normalTokens;
		goldTokens = initGoldTokens;
		tokensTotal = 5 * normalTokens + goldTokens;
	}
	FTokenStruct operator +(FTokenStruct &added)
	{
		this->diamondTokens = this->diamondTokens + added.diamondTokens;
		this->emeraldTokens = this->emeraldTokens + added.emeraldTokens;
		this->onyxTokens = this->onyxTokens + added.onyxTokens;
		this->goldTokens = this->goldTokens + added.goldTokens;
		this->sapphireTokens = this->sapphireTokens + added.sapphireTokens;
		this->rubyTokens = this->rubyTokens + added.rubyTokens;

		this->tokensTotal = this->tokensTotal + added.tokensTotal;

		return *this;
	}
	FTokenStruct operator -(FTokenStruct &deducted)
	{
		this->diamondTokens = this->diamondTokens - deducted.diamondTokens;
		this->emeraldTokens = this->emeraldTokens - deducted.emeraldTokens;
		this->onyxTokens = this->onyxTokens - deducted.onyxTokens;
		this->goldTokens = this->goldTokens - deducted.goldTokens;
		this->sapphireTokens = this->sapphireTokens - deducted.sapphireTokens;
		this->rubyTokens = this->rubyTokens - deducted.rubyTokens;

		this->tokensTotal = this->tokensTotal - deducted.tokensTotal;
		return *this;
	}
	bool operator ==(FTokenStruct &compared)
	{
		bool isSame = true;
		if (tokensTotal != compared.tokensTotal)
		{
			isSame = false;
			return isSame;
		}
		else if (onyxTokens != compared.onyxTokens)
		{
			isSame = false;
			return isSame;
		}
		else if (rubyTokens != compared.rubyTokens)
		{
			isSame = false;
			return isSame;
		}
		else if (emeraldTokens != compared.emeraldTokens)
		{
			isSame = false;
			return isSame;
		}
		if (sapphireTokens != compared.sapphireTokens)
		{
			isSame = false;
			return isSame;
		}
		if (diamondTokens != compared.diamondTokens)
		{
			isSame = false;
			return isSame;
		}
		if (goldTokens != compared.goldTokens)
		{
			isSame = false;
			return isSame;
		}
		return isSame;
	}
};

/*
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

	UPROPERTY(BlueprintAssignable)
		FOnTokenRequest OnTokenRequest;

};
