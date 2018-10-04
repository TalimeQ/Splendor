

#include "Public/SplendorPlayerController.h"
#include "Public/Player/PlayerPawn.h"
#include "Runtime/Engine/Classes/Components/InputComponent.h"
#include "Runtime/Engine/Classes/Engine/World.h"

void ASplendorPlayerController::BeginPlay()
{
	
	// chcemy pokazywac nasz kursor
	this->bShowMouseCursor = true;
	//
	this->bEnableMouseOverEvents = true;
	// Gets upgradedPlayerPawnRef for future use;
	playerPawnRef = Cast<APlayerPawn>(this->GetPawn());
	InitializeInputs();
}

void ASplendorPlayerController::Tick(float DeltaTime)
{

	MovePawn();
}

// Used mostly  to bind controlls to inputs from player.
void ASplendorPlayerController::InitializeInputs()
{
	
}
void ASplendorPlayerController::MovePawn()
{
	FVector cameraDirVector = GetCameraPanDirection();
	playerPawnRef->ChangePosition(cameraDirVector);

}
FVector  ASplendorPlayerController::GetCameraPanDirection()
{
	float mouseX;
	float mouseY;
	float CameraDirX = 0;
	float CameraDirY = 0;

	GetMousePosition(mouseX, mouseY);
	if (mouseX == 0)
	{
		CameraDirY = -1;
	}
	return  FVector(CameraDirX, CameraDirY, 0);
}