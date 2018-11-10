#pragma once

#include "CardStruct.generated.h"

USTRUCT(BlueprintType, Blueprintable) struct FCardStruct
{
	GENERATED_USTRUCT_BODY()
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Card Cost")
		FTokenStruct cardCost;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Currency Provided")
		FTokenStruct cardBonus;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Points Provided")
		int prestige;

	FCardStruct() : cardCost(FTokenStruct()), cardBonus(FTokenStruct()), prestige(0)
	{

	}
};