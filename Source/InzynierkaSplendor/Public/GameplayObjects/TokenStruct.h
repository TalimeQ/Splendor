#pragma once


#include "TokenStruct.generated.h"

USTRUCT(BlueprintType) struct FTokenStruct {
	GENERATED_USTRUCT_BODY()
		UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Emeralds")
		int emeraldTokens;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Rubies")
		int rubyTokens;
	UPROPERTY(BlueprintReadWrite, EditAnywhere,Category = "Onyxes")
		int onyxTokens;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Sapphires")
		int sapphireTokens;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Diamonds")
		int diamondTokens;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Gold")
		int goldTokens;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Total")
		int tokensTotal;


	// Properties should always be initialized from what i hear 
	void setParams(FTokenStruct tokensToSet)
	{
		this->emeraldTokens = tokensToSet.emeraldTokens;
		this->rubyTokens = tokensToSet.rubyTokens;
		this->onyxTokens = tokensToSet.onyxTokens;
		this->sapphireTokens = tokensToSet.sapphireTokens;
		this->goldTokens = tokensToSet.goldTokens;
		this->diamondTokens = tokensToSet.diamondTokens;
		this->tokensTotal = tokensToSet.tokensTotal;

	}
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
			
		}
		else if (onyxTokens != compared.onyxTokens)
		{
			isSame = false;
		
		}
		else if (rubyTokens != compared.rubyTokens)
		{
			isSame = false;
			
		}
		else if (emeraldTokens != compared.emeraldTokens)
		{
			isSame = false;
			
		}
		if (sapphireTokens != compared.sapphireTokens)
		{
			isSame = false;
		
		}
		if (diamondTokens != compared.diamondTokens)
		{
			isSame = false;
			
		}
		if (goldTokens != compared.goldTokens)
		{
			isSame = false;
			
		}
		return isSame;
	}
	/* Overloaded just to check if cards are purchasable
	*/
	bool operator <=(FTokenStruct &compared)
	{
		bool compResult = true;
		if (emeraldTokens > compared.emeraldTokens)
		{
			compResult = false;
		}
		if (goldTokens > compared.goldTokens)
		{
			compResult = false;
		}
		if (sapphireTokens > compared.sapphireTokens)
		{
			compResult = false;
		}
		if (rubyTokens > compared.rubyTokens)
		{
			compResult = false;
		}
		if (onyxTokens > compared.onyxTokens)
		{
			compResult = false;
		}
		if (diamondTokens > compared.diamondTokens)
		{
			compResult = false;
		}
		return compResult;
	}
	int Count()
	{
		int tokensTotal = emeraldTokens + rubyTokens + onyxTokens + sapphireTokens + diamondTokens + goldTokens;
		return tokensTotal;
	}
};