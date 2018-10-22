

#include "Public/GameplayObjects/TokenStash.h"
#include "Public/SplendorPlayerController.h"
#include "Runtime/Engine/Classes/Engine/World.h"

ATokenStash::ATokenStash()
{
	/* Should be changed based on amount of players
	2 player -> 4 gems of each
	3 player -> 5 gems of each
	4 player -> 7 gems of each
	
	*/
	tokenPool = FTokenStruct(7, 5);
}

void ATokenStash::OnRaycast()
{
	// TODO :: make networked version, this works in single atm ;)
	ASplendorPlayerController* splendorCont = Cast<ASplendorPlayerController>(this->GetWorld()->GetFirstPlayerController());
	if (splendorCont)
	{
		splendorCont->ToggleInput();
	}
	OnTokenRequest.Broadcast();
	UE_LOG(LogTemp,Warning,TEXT("Raycast kinda clicked"))
		
}
void ATokenStash::BeginPlay()
{
	Super::BeginPlay();

}