

#include "RaycastHandler.h"
#include "Public/Components/RaycastHandler.h"
#include "Public/Player/PlayerPawn.h"

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
	


}


// Called every frame
void URaycastHandler::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{


	// ...
}
void URaycastHandler::InitializePawn()
{
	playerPawn = Cast<APlayerPawn>(this->GetOwner());
	ensure(playerPawn);
	if (!playerPawn)
	{
		// This component should only communicate with player pawns, no need to keep it when the player pawn is non existant
		this->DestroyComponent();
	}
}
