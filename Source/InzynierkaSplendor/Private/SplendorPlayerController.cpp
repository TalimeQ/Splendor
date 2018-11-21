

#include "Public/SplendorPlayerController.h"
#include "Public/Player/PlayerPawn.h"
#include "UnrealNetwork.h"
#include "Public/Player/SplendorPlayerState.h"
#include "Public/GameplayObjects/TokenStruct.h"
#include "Public/GameplayObjects/TokenStash.h"
#include "Public/GameplayObjects/CardStruct.h"
#include "InzynierkaSplendorGameModeBase.h"
#include "Runtime/Engine/Classes/Components/InputComponent.h"
#include "Runtime/Engine/Classes/Engine/World.h"


void ASplendorPlayerController::BeginPlay()
{
	Super::BeginPlay();
	InitializeEdgePanningParameters();
	UE_LOG(LogTemp, Warning, TEXT("Controller Created"));


}

void ASplendorPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!playerPawnRef) return;
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
	if (!Cast<ASplendorPlayerState>(this->PlayerState)->GetTurnStatus()) return;
	StartRaycasting();
}
void ASplendorPlayerController::OnRightClick()
{
	// This will cancel actions
	// TODO :: Implement :)
	RestartPawn();

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
void ASplendorPlayerController::AddTokens(FTokenStruct tokensToAdd)
{
	ASplendorPlayerState* playerStateRef = Cast<ASplendorPlayerState>( this->PlayerState);
	if (playerStateRef)
	{
		FTokenStruct playerOwnedTokens = playerStateRef->GetPlayerTokens();
		playerOwnedTokens + tokensToAdd;
		playerStateRef->SetPlayerTokens(playerOwnedTokens);
		// This is just for debug purposes :) TODO :: When the interface will be implemented, remove this.
		playerOwnedTokens = playerStateRef->GetPlayerTokens();
		UE_LOG(LogTemp, Warning, TEXT("Final player Token State ::  Rubies: %d , Diamonds: %d , Emeralds: %d , Sapphires: %d , Onyxes : %d "), playerOwnedTokens.rubyTokens, playerOwnedTokens.diamondTokens, playerOwnedTokens.emeraldTokens, playerOwnedTokens.sapphireTokens, playerOwnedTokens.onyxTokens)
		// Zabezpiecza przed podwojnym requestem zmiany tury.
		if (tokensToAdd.goldTokens >= 1) return;
		// Jesli w tym momecie mielismy ture, to ja informujemy serwer ze chcemy ja zakonczyc
		if(Cast<ASplendorPlayerState>(this->PlayerState)->GetTurnStatus()) this->CallTurnEnd();
	}
}
void ASplendorPlayerController::StartRaycasting()
{
	if (!playerPawnRef) return;
	FVector mouseLocation;
	FVector mouseDir;
	// Deprojecting the mouse so we can extract the raycast start point.
	DeprojectMousePositionToWorld(mouseLocation, mouseDir);
	// The pawn handles raycasts, we just provide intent.
	playerPawnRef->InitializeRaycast(mouseLocation, mouseDir);
}
bool ASplendorPlayerController::CheckIfCanReserve()
{
	ASplendorPlayerState* playerState = Cast<ASplendorPlayerState>(this->PlayerState);
	if (!playerState) return false;
	if (playerState->ReturnNumberOfCards() >= 3) return false;
	else return true;
}
void ASplendorPlayerController::ForceInput()
{
	this->EnableInput(this);
	bIsInputEnabled = true;
}
bool ASplendorPlayerController::CheckBudget(FTokenStruct comparedAmount)
{
	ASplendorPlayerState* playerState = Cast<ASplendorPlayerState>(this->PlayerState);
	if (!playerState) return false;
	FTokenStruct playerBudget = playerState->GetPlayerBudget();
	// Note to self, atm cards are initialized as empty. This is not a bug, but a kinda struct protection, well at least its not NULLPTR
	return comparedAmount <= playerBudget;
}
void ASplendorPlayerController::BuyCard(FTokenStruct cardBonus,FTokenStruct cost, int prestige, bool bIsWithGold)
{
	ASplendorPlayerState* playerState = Cast<ASplendorPlayerState>(this->PlayerState);
	if (!playerState) return;
	int oldPrestige = playerState->GetPlayerPrestige();
	playerState->SetPlayerPrestige(oldPrestige + prestige);

	FTokenStruct playerBonuses = playerState->GetPlayerBonuses();
	FTokenStruct playerBudget = playerState->GetPlayerTokens();

	cost - playerBonuses;
	cost.NormalizeCost();
	playerBudget - cost;

	if(bIsWithGold)
	{
		playerBudget.DeductGold(playerBudget);
	}

	playerState->SetPlayerTokens(playerBudget);
	FTokenStruct oldBonus = playerState->GetPlayerBonuses();
	FTokenStruct newBonus = oldBonus + cardBonus;
	playerState->SetPlayerBonus(newBonus);
	// Jesli w tym momecie mielismy ture, to ja informujemy serwer ze chcemy ja zakonczyc
	if (Cast<ASplendorPlayerState>(this->PlayerState)->GetTurnStatus()) this->CallTurnEnd();
}
void ASplendorPlayerController::RestartPawn()
{
	playerPawnRef->RestartPos();
}
void  ASplendorPlayerController::ReserveCard(FCardStruct* reservedCard)
{
	ASplendorPlayerState* playerState = Cast<ASplendorPlayerState>(this->PlayerState);
	if (playerState->GetTurnStatus()) this->CallTurnEnd();
	playerState->ReserveCard(*reservedCard);
	
}


/*
Server Calls
*/



void ASplendorPlayerController::CallTokenStashUpdate(ATokenStash * tokenStash, FTokenStruct tokenAmount)
{
	
	if (Role == ROLE_Authority)
	{
		tokenStash->SetTokenAmount(tokenAmount);
	}
	else 
	{
		ServerCallTokenStashUpdate(  tokenStash,  tokenAmount);
	}
	
}
void  ASplendorPlayerController::ServerCallTokenStashUpdate_Implementation(ATokenStash * tokenStash, FTokenStruct tokenAmount)
{
	CallTokenStashUpdate(tokenStash, tokenAmount);
	
}
bool ASplendorPlayerController::ServerCallTokenStashUpdate_Validate(ATokenStash * tokenStash, FTokenStruct tokenAmount)
{
	return true;
}
void ASplendorPlayerController::CallTurnEnd()
{
	if (Role == ROLE_Authority)
	{
		Cast<AInzynierkaSplendorGameModeBase>(GetWorld()->GetAuthGameMode())->ProcessTurnInfo();
	}
	else
	{
		ServerCallTurnEnd();
	}
}
void ASplendorPlayerController::ServerCallTurnEnd_Implementation()
{
	CallTurnEnd();
}
bool ASplendorPlayerController::ServerCallTurnEnd_Validate()
{
	return true;
}