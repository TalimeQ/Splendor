

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"

class USpringArmComponent;
class UCameraComponent;
class APlayerController;
class URaycastHandler;

UCLASS()
class INZYNIERKASPLENDOR_API APlayerPawn : public APawn
{
	GENERATED_BODY()
		
public:
	// Sets default values for this pawn's properties
	APlayerPawn();
	void ChangePosition(FVector newLocationVector);
	void RestartPos();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void InitializeRaycast(FVector mousePos, FVector mouseDir);

private:

	void SetupCamera();
	UCameraComponent* playerCamera = nullptr;
	USpringArmComponent* cameraOffset = nullptr;
	APlayerController* playerController = nullptr;
	URaycastHandler* raycastHandler = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Camera")
		float cameraSpeed = 5.0f;

};
