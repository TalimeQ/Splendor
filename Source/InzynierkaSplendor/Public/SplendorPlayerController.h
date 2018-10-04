

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
	void InitializeInputs();
	APlayerPawn* playerPawnRef = nullptr;
	void MovePawn();
	FVector GetCameraPanDirection();
};
