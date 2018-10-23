

#include "RaycastHandler.h"
#include "Public/Components/RaycastHandler.h"
#include "Public/Player/PlayerPawn.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Runtime/Engine/Public/CollisionQueryParams.h"
#include "Public/GameplayObjects/Interactable.h"


// Sets default values for this component's properties
URaycastHandler::URaycastHandler()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void URaycastHandler::BeginPlay()
{
	
	Super::BeginPlay();

}


// Called every frame
void URaycastHandler::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
void URaycastHandler::InitializePawn()
{
	playerPawn = Cast<APlayerPawn>(this->GetOwner());
	ensure(playerPawn);
	if (!playerPawn)
	{
		// This component should only communicate with player pawns, no need to keep it when the player pawn is non-existant
		this->DestroyComponent();
	}
}
void URaycastHandler::Raycast(FVector mousePos, FVector mouseDir)
{
	// TODO Remove/disable debug stuff and refactor it to be cleaner
	// Raycast Params
	UWorld * worldRef = this->GetWorld();
	FVector endVector = mousePos + mouseDir * 1500;
	FHitResult traceHitResult;

	// Just for debugs :)
	DrawDebugLine(GetWorld(), mousePos, endVector, FColor::Orange, false, 35.0f, 0, 5.0f);
	// to prevent from crashing
	//ensure(!worldRef);
		worldRef->LineTraceSingleByChannel(traceHitResult,mousePos,endVector,ECollisionChannel::ECC_GameTraceChannel18);
		AActor* actorHit = traceHitResult.GetActor(); // Tbh its debug purposes only
		if (!actorHit) return; // there certainly is and will be a possibility of not hitting anything :)
		UE_LOG(LogTemp, Warning, TEXT("Raycasted on object &s"), *(actorHit->GetName())) // Debug purposes

			AInteractable* interactedObject = Cast<AInteractable>(actorHit);
		if (interactedObject)
		{
			interactedObject->OnRaycast();
		}
	
}