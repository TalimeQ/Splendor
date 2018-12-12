

#include "Public/GameplayObjects/TokenStash.h"
#include "Public/GameplayObjects/TokenStruct.h"
#include "Public/SplendorPlayerController.h"
#include "UnrealNetwork.h"
#include "Runtime/Engine/Classes/Engine/World.h"

ATokenStash::ATokenStash()
{
	/*
	TODO ::
	Should be changed based on amount of players
	2 player -> 4 gems of each
	3 player -> 5 gems of each
	4 player -> 7 gems of each

	*/
	bReplicates = true;
	bAlwaysRelevant = true;
	tokenPool =  FTokenStruct(7, 5);
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


void ATokenStash::ProcessTokenRequest(TArray<int> requestedTokens, ASplendorPlayerController* playerContRef)
{
	FTokenStruct tokensBeingTaken = FTokenStruct();
	if (!playerContRef) return;

	uint8 lenght = requestedTokens.Num();
	for(int i = 0; i < lenght; i ++)
	{
		switch (requestedTokens[i])
		{
		case 0:
			tokensBeingTaken.rubyTokens += 1;
			tokensBeingTaken.tokensTotal++;
			break;
		case 1:
			tokensBeingTaken.emeraldTokens += 1;
			tokensBeingTaken.tokensTotal++;
			break;
		case 2:
			tokensBeingTaken.diamondTokens += 1;
			tokensBeingTaken.tokensTotal++;
			break;
		case 3:
			tokensBeingTaken.onyxTokens += 1;
			tokensBeingTaken.tokensTotal++;
			break;
		case 4:
			tokensBeingTaken.sapphireTokens += 1;
			tokensBeingTaken.tokensTotal++;
			break;
		case 5: 
			tokensBeingTaken.goldTokens += 1;
			tokensBeingTaken.tokensTotal++;
			break;
		default:
			UE_LOG(LogTemp, Warning, TEXT("TokenStash :: Unknown token operation"));
			break;
		}
		
	}
	if (tokensBeingTaken.goldTokens == 1 && tokenPool.goldTokens <= 0)
	{
		
		return;
	}
	playerContRef->CallTokenStashUpdate(this, tokensBeingTaken);
	playerContRef->AddTokens(tokensBeingTaken);
		

}
bool ATokenStash::CheckIfTokensAvailable(int tokenNumber, int checkedAmount)
{
	bool bIsAvailable = true;
	switch (tokenNumber)
	{
	case 0:
		if (tokenPool.rubyTokens < checkedAmount) bIsAvailable = false;
		break;
	case 1:
		if (tokenPool.emeraldTokens < checkedAmount) bIsAvailable = false;
		break;
	case 2:
		if (tokenPool.diamondTokens < checkedAmount) bIsAvailable = false;
		break;
	case 3:
		if (tokenPool.onyxTokens< checkedAmount) bIsAvailable = false;
		break;
	case 4:
		if (tokenPool.sapphireTokens < checkedAmount) bIsAvailable = false;
		break;
	case 5:
		if (tokenPool.goldTokens < checkedAmount) bIsAvailable = false;
		break;
	default:
		UE_LOG(LogTemp,Warning,TEXT("Check if available :: unknown token"))
		break;
	}
	return bIsAvailable;
}

void  ATokenStash::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ATokenStash, tokenPool);
}
void  ATokenStash::SetTokenAmount(FTokenStruct deductedTokenAmount)
{
	
	if (Role == ROLE_Authority)
	{
		UE_LOG(LogTemp, Warning, TEXT("Servered Tokens D: %d , E: %d, S: %d, O: %d, R: %d "), deductedTokenAmount.diamondTokens, deductedTokenAmount.emeraldTokens, deductedTokenAmount.sapphireTokens, deductedTokenAmount.onyxTokens, deductedTokenAmount.rubyTokens)
		this->tokenPool - deductedTokenAmount;
		// Updates visualy
		this->VisualizeTokens();
		
	}
	else
	{
		ServerSetTokenAmount(deductedTokenAmount);
	}
	
}
void  ATokenStash::ServerSetTokenAmount_Implementation(FTokenStruct deductedTokenAmount)
{
	SetTokenAmount(deductedTokenAmount);
}
bool ATokenStash::ServerSetTokenAmount_Validate(FTokenStruct deductedTokenAmount)
{
	return true;
}
void ATokenStash::OnRep_VisualizeTokens()
{
	if (!(emeraldTokenBottom || rubyTokenBottom || goldTokenBottom || sapphireTokenBottom ||onyxTokenBottom || diamondTokenBottom ))
	{
		UE_LOG(LogTemp,Warning,TEXT("ATokenStash :: stopped visualisation execution, one of top pointers is null"))
		return;
	}
	VisualizeTokens();


}
void ATokenStash::VisualizeTokens()
{
	emeraldTokenBottom->SetActorLocation(FVector(emeraldTokenBottom->GetActorLocation().X, emeraldTokenBottom->GetActorLocation().Y, tokenPool.emeraldTokens * 15 - 75));
	rubyTokenBottom->SetActorLocation(FVector(rubyTokenBottom->GetActorLocation().X, rubyTokenBottom->GetActorLocation().Y, tokenPool.rubyTokens * 15 - 75));
	goldTokenBottom->SetActorLocation(FVector(goldTokenBottom->GetActorLocation().X, goldTokenBottom->GetActorLocation().Y, tokenPool.goldTokens * 15 - 45));
	sapphireTokenBottom->SetActorLocation(FVector(sapphireTokenBottom->GetActorLocation().X, sapphireTokenBottom->GetActorLocation().Y, tokenPool.sapphireTokens * 15 - 75));
	diamondTokenBottom->SetActorLocation(FVector(diamondTokenBottom->GetActorLocation().X, diamondTokenBottom->GetActorLocation().Y, tokenPool.diamondTokens * 15 - 75));
	onyxTokenBottom->SetActorLocation(FVector(onyxTokenBottom->GetActorLocation().X, onyxTokenBottom->GetActorLocation().Y, tokenPool.onyxTokens * 15 - 75));
}