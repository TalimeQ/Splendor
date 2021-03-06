

#include "Public/Player/PlayerPawn.h"
#include "Engine/Classes/Camera/CameraComponent.h"
#include "Engine/Classes/GameFramework/PlayerController.h"
#include "Public/SplendorPlayerController.h"
#include "Public/Components/RaycastHandler.h"
#include "Classes/GameFramework/SpringArmComponent.h"


// Sets default values
APlayerPawn::APlayerPawn()
{
	raycastHandler = CreateDefaultSubobject<URaycastHandler>(TEXT("Raycast Handling Component"));
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SetupCamera();
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	playerController = Cast<APlayerController>(this->GetController());
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	
}
void APlayerPawn::ChangePosition(FVector newLocationVector)
{
	
	AddActorWorldOffset(newLocationVector * cameraSpeed);
}
void APlayerPawn::SetupCamera()
{
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root component"));
	cameraOffset = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Spring Arm"));
	playerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Player Camera"));
	cameraOffset->SetupAttachment(RootComponent);
	cameraOffset->SetRelativeLocationAndRotation(FVector(0, 0, 0), FRotator(-75,0, 0));

	cameraOffset->TargetArmLength = 500.0f;
	cameraOffset->bEnableCameraLag = true;
	cameraOffset->CameraLagSpeed = 3.5f;
	cameraOffset->bDoCollisionTest = false;

	playerCamera->SetupAttachment(cameraOffset, USpringArmComponent::SocketName);
}

void APlayerPawn::InitializeRaycast(FVector mousePos, FVector mouseDir)
{
	if (!raycastHandler) return;
	
	raycastHandler->Raycast(mousePos,mouseDir);
}
void APlayerPawn::RestartPos()
{
	this->SetActorLocation(FVector(0, 0, 0));
}