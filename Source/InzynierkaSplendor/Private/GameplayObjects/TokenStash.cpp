

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
		
}
void ATokenStash::BeginPlay()
{
	Super::BeginPlay();

}
void ATokenStash::ProcessTokenRequest(TArray<int> requestedTokens)
{
	FTokenStruct tokensBeingTaken = FTokenStruct();
	
	uint8 lenght = requestedTokens.Num();
	//UE_LOG(LogtTemp,Warning,("Number of items in array %d"),)
	for(int i = 0; i < lenght; i ++)
	{
		switch (requestedTokens[i])
		{
			//
		case 0:
			tokensBeingTaken.rubyTokens += 1;
			break;
		case 1:
			tokensBeingTaken.emeraldTokens += 1;
			break;
		case 2:
			tokensBeingTaken.diamondTokens += 1;
			break;
		case 3:
			tokensBeingTaken.onyxTokens += 1;
			break;
		case 4:
			tokensBeingTaken.sapphireTokens += 1;
			break;
		case 5: 
			tokensBeingTaken.goldTokens += 1;
			break;
		default:
			UE_LOG(LogTemp, Warning, TEXT("TokenStash :: Unknown token operation"));
			break;
		}
	}
	tokenPool - tokensBeingTaken; 
	UE_LOG(LogTemp,Warning, TEXT("TokenStash State ::  Rubies: %d , Diamonds: %d , Emeralds: %d , Sapphires: %d , Onyxes : %d "),tokenPool.rubyTokens,tokenPool.diamondTokens,tokenPool.emeraldTokens,tokenPool.sapphireTokens,tokenPool.onyxTokens)
}