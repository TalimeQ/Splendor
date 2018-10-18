

#include "Public/SplendorPlayerController.h"
#include "Public/Player/PlayerPawn.h"
#include "Runtime/Engine/Classes/Components/InputComponent.h"
#include "Runtime/Engine/Classes/Engine/World.h"


void ASplendorPlayerController::BeginPlay()
{
	Super::BeginPlay();
	this->bShowMouseCursor = true;
	//this->bEnableMouseOverEvents = true;
	//this->bEnableClickEvents = true;
	PrimaryActorTick.bCanEverTick = true;
	playerPawnRef = Cast<APlayerPawn>(this->GetPawn());
	this->GetViewportSize(screenSizeX, screenSizeY);
	SetupInputComponent();
	EnableInput(this);
	InputEnabled();
	UE_LOG(LogTemp, Warning, TEXT("Executed"));
}

void ASplendorPlayerController::Tick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	MovePawn();


}


void ASplendorPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	check(InputComponent);
	
	InputComponent->BindAction("Left", EInputEvent::IE_Pressed, this, &ASplendorPlayerController::OnLeftClick);
	InputComponent->BindAction("Right", EInputEvent::IE_Pressed, this, &ASplendorPlayerController::OnRightClick);

	
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
	else if (mouseX >= screenSizeX - margin)
	{
		CameraDirY = 1;
	}
	if (mouseY <= margin)
	{
		 CameraDirX = 1;
	}
	else if (mouseY >= screenSizeY - margin)
	{
		CameraDirX = -1;
	}
	return  FVector(CameraDirX, CameraDirY, 0);
}
void ASplendorPlayerController::OnLeftClick()
{
	UE_LOG(LogTemp, Warning, TEXT("Left mouse button clicked"));
}
void ASplendorPlayerController::OnRightClick()
{
	UE_LOG(LogTemp, Warning, TEXT("Right mouse button clicked"));
}
