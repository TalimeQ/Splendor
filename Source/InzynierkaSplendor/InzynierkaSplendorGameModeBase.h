// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "InzynierkaSplendorGameModeBase.generated.h"

/**
 * 
 */
class ASplendorGameState;
UCLASS()
class INZYNIERKASPLENDOR_API AInzynierkaSplendorGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void ProcessTurnInfo();
private:
	virtual void BeginPlay() override;
	ASplendorGameState* stateRef;
	UFUNCTION(reliable, server, WithValidation)
	void ServerProcessTurnInfo();
};
