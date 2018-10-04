

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
	this->GetViewportSize(screenSizeX, screenSizeY);
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
	if (cameraDirVector == FVector(0, 0, 0)) return;
	playerPawnRef->ChangePosition(cameraDirVector);

}
FVector  ASplendorPlayerController::GetCameraPanDirection()
{
	float mouseX;
	float mouseY;
	float CameraDirX = 0;
	float CameraDirY = 0;

	GetMousePosition(mouseX, mouseY);
	if (mouseX <= margin)
	{
		CameraDirY = -1;
	}
	if (mouseY <= margin)
	{
		CameraDirX = 1;
	}
	if (mouseX >= screenSizeX - margin)
	{
		CameraDirY = 1;
	}
	if (mouseY >= screenSizeY - margin)
	{
		CameraDirX = -1;
	}
	return  FVector(CameraDirX, CameraDirY, 0);
}