

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
/*
TODO:
Przeniesc Ustructa w normalne miejsce. Robi sie balagan z klasami.
*/
#include "Public/GameplayObjects/TokenStruct.h"
#include "SplendorPlayerController.generated.h"


class APlayerPawn;


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
	FVector GetCameraPanDirection();
	// Todo :: Make it inspector editable
	float margin = 15.0f;
	APlayerPawn* playerPawnRef = nullptr;
	int32 screenSizeX;
	int32 screenSizeY;
public:
	UFUNCTION(BlueprintCallable)
	void ToggleInput();
	void AddTokens(FTokenStruct tokensToAdd);
protected:
	virtual void SetupInputComponent() override;
	UFUNCTION(BlueprintCallable)
	void OnLeftClick();
	UFUNCTION(BlueprintCallable)
	void OnRightClick();
	
	
};
