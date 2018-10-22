

#include "Public/SplendorPlayerController.h"
#include "Public/Player/PlayerPawn.h"
#include "Runtime/Engine/Classes/Components/InputComponent.h"
#include "Runtime/Engine/Classes/Engine/World.h"


void ASplendorPlayerController::BeginPlay()
{
	Super::BeginPlay();
	InitializeEdgePanningParameters();


}

void ASplendorPlayerController::Tick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	MovePawn();


}


void  ASplendorPlayerController::InitializeEdgePanningParameters()
{
	this->bShowMouseCursor = true;
	this->bEnableMouseOverEvents = true;
	this->bEnableClickEvents = true;
	PrimaryActorTick.bCanEverTick = true;
	playerPawnRef = Cast<APlayerPawn>(this->GetPawn());
	this->GetViewportSize(screenSizeX, screenSizeY);
}
void ASplendorPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	check(InputComponent);
	
	InputComponent->BindAction("Left", EInputEvent::IE_Released, this, &ASplendorPlayerController::OnLeftClick);
	InputComponent->BindAction("Right", EInputEvent::IE_Pressed, this, &ASplendorPlayerController::OnRightClick);
	EnableInput(this);
	InputEnabled();
	bIsInputEnabled = true;
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
	// This will do actions
	
	if (!playerPawnRef) return;
	FVector mouseLocation;
	FVector mouseDir;
	DeprojectMousePositionToWorld(mouseLocation,mouseDir);
;
	playerPawnRef->InitializeRaycast(mouseLocation,mouseDir);
}
void ASplendorPlayerController::OnRightClick()
{
	// This will cancel actions
	UE_LOG(LogTemp, Warning, TEXT("Right mouse button clicked"));
}
void ASplendorPlayerController::ToggleInput()
{
	if(bIsInputEnabled)
	{
		this->DisableInput(this);
		bIsInputEnabled = false;
	}
	else
	{
		this->EnableInput(this);
		bIsInputEnabled = true;
	}
	
	
}