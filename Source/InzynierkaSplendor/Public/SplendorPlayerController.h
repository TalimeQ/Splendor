

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameplayObjects/TokenStruct.h"
/*
Refactoring
*/

#include "SplendorPlayerController.generated.h"


class APlayerPawn;
class ACardStack;
class ATokenStash;
struct FCardStruct;
/**	
 * 
 */
UCLASS()
class INZYNIERKASPLENDOR_API ASplendorPlayerController : public APlayerController
{
	GENERATED_BODY()
private:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	bool bIsInputEnabled = true;
	void MovePawn();
	void InitializeEdgePanningParameters();
	void StartRaycasting();
	void RestartPawn();
	FVector GetCameraPanDirection();
	// Todo :: Make it inspector editable
	float margin = 15.0f;
	APlayerPawn* playerPawnRef = nullptr;
	int32 screenSizeX;
	int32 screenSizeY;
	UFUNCTION(Server, Reliable, WithValidation)
	void ServerCallTokenStashUpdate(ATokenStash * tokenStash, FTokenStruct tokenAmount);
	UFUNCTION(Server, Reliable, WithValidation)
	void ServerRequestsCardPop(ACardStack* cardStackToPop);
	UFUNCTION(Server, Reliable, WithValidation)
	void ServerCallTurnEnd();

public:
	UFUNCTION(BlueprintCallable)
	void ToggleInput();
	UFUNCTION(BlueprintCallable)
	void ForceInput();
	void AddTokens(FTokenStruct tokensToAdd);
	UFUNCTION(BlueprintCallable)
	bool CheckIfCanReserve();
	bool CheckBudget(FTokenStruct comparedAmount);
	void ReserveCard(FCardStruct* reservedCard);
	void BuyCard(FTokenStruct cardBonus, FTokenStruct cost, int prestige, bool bIsWithGold);

	void CallTokenStashUpdate(ATokenStash * tokenStash, FTokenStruct tokenAmount);
	void CallTurnEnd();
	void CallRequestCardPop(ACardStack* cardStackToPop);
	

protected:
	virtual void SetupInputComponent() override;
	UFUNCTION(BlueprintCallable)
	void OnLeftClick();
	UFUNCTION(BlueprintCallable)
	void OnRightClick();
	
	
};
