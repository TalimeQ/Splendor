

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
/*
Refactoring
*/

#include "SplendorPlayerController.generated.h"


class APlayerPawn;
struct FTokenStruct;

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

	FVector GetCameraPanDirection();
	// Todo :: Make it inspector editable
	float margin = 15.0f;
	APlayerPawn* playerPawnRef = nullptr;
	int32 screenSizeX;
	int32 screenSizeY;
public:
	UFUNCTION(BlueprintCallable)
	void ToggleInput();
	UFUNCTION(BlueprintCallable)
	void ForceInput();
	void AddTokens(FTokenStruct tokensToAdd);
	bool CheckIfCanReserve();
	bool CheckBudget(FTokenStruct comparedAmount);
	void BuyCard(FTokenStruct cardBonus, int prestige);
protected:
	virtual void SetupInputComponent() override;
	UFUNCTION(BlueprintCallable)
	void OnLeftClick();
	UFUNCTION(BlueprintCallable)
	void OnRightClick();
	
	
};
