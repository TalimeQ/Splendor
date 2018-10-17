

#include "Public/SplendorPlayerController.h"
#include "Public/Player/PlayerPawn.h"
#include "Runtime/Engine/Classes/Components/InputComponent.h"
#include "Runtime/Engine/Classes/Engine/World.h"

//TODO :: Wstawic Super do konstruktora


void ASplendorPlayerController::BeginPlay()
{
	Super::BeginPlay();
	this->bShowMouseCursor = true;
	this->bEnableMouseOverEvents = true;
	this->bEnableClickEvents = true;
	playerPawnRef = Cast<APlayerPawn>(this->GetPawn());
	this->GetViewportSize(screenSizeX, screenSizeY);
	SetupInputComponent();
	EnableInput(this);
	//AutoPossesPlayer = EAutoReceiveInput::Player0;
	
	InitInputSystem();

}

void ASplendorPlayerController::Tick(float DeltaTime)
{

	MovePawn();
}


void ASplendorPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction("Left", EInputEvent::IE_Pressed, this, &ASplendorPlayerController::OnLeftClick);
	InputComponent->BindAction("Right", EInputEvent::IE_Pressed, this, &ASplendorPlayerController::OnRightClick);
	InputComponent->BindAction("Karol", EInputEvent::IE_Pressed, this, &ASplendorPlayerController::OnKarol);
	
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
void ASplendorPlayerController::OnLeftClick()
{
	UE_LOG(LogTemp, Verbose, TEXT("Left mouse button clicked"));
}
void ASplendorPlayerController::OnRightClick()
{
	UE_LOG(LogTemp, Verbose, TEXT("Right mouse button clicked"));
}
void ASplendorPlayerController::OnKarol()
{
	UE_LOG(LogTemp, Verbose, TEXT("On Karol"));
}