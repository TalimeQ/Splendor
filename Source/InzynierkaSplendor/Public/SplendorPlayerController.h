

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
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

	void MovePawn();
	FVector GetCameraPanDirection();
	// Todo :: Make it inspector editable
	float margin = 15.0f;
	APlayerPawn* playerPawnRef = nullptr;
	int32 screenSizeX;
	int32 screenSizeY;
	void OnLeftClick();
	void OnRightClick();

	virtual void SetupInputComponent() override;
};
