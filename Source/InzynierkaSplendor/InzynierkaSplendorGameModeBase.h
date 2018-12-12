// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameplayObjects/TokenStruct.h"
#include "InzynierkaSplendorGameModeBase.generated.h"


/**
 * 
 */


class ASplendorGameState;
class APatronCardVisualizer;

UCLASS()
class INZYNIERKASPLENDOR_API AInzynierkaSplendorGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TArray<APatronCardVisualizer*> aristocratCardsRequirements;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		TArray<FTokenStruct> aristocratRequirements;
	AInzynierkaSplendorGameModeBase();
	UFUNCTION(BlueprintCallable)
	void ProcessTurnInfo();
	void BuyAristocrat(int arrayNum);
private:
	
	virtual void BeginPlay() override;
	ASplendorGameState* stateRef;
	UFUNCTION(reliable, server, WithValidation)
	void ServerProcessTurnInfo();
protected:

	
	UFUNCTION(BlueprintImplementableEvent)
		void RemoveCard(int cardNumber);
};
