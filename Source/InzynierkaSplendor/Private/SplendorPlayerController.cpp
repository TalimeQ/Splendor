

#include "Public/SplendorPlayerController.h"
#include "Public/Player/PlayerPawn.h"
#include "UnrealNetwork.h"
#include "Public/Player/SplendorPlayerState.h"
#include "Public/GameplayObjects/TokenStruct.h"
#include "Public/GameplayObjects/TokenStash.h"
#include "Public/GameplayObjects/CardStack.h"
#include "InzynierkaSplendorGameModeBase.h"
#include "Runtime/Engine/Classes/Components/InputComponent.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Public/GameplayObjects/Card.h"


void ASplendorPlayerController::BeginPlay()
{
	Super::BeginPlay();
	InitializeEdgePanningParameters();
	UE_LOG(LogTemp, Warning, TEXT("Controller Created"));


}

void ASplendorPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
//if (!playerPawnRef) return;
//	MovePawn();
//	GetCameraPanDirection();
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
void ASplendorPlayerController::MovePawn(FVector cameraDirVector)
{
	//FVector cameraDirVector = GetCameraPanDirection();

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
	UE_LOG(LogTemp, Warning, TEXT("Positions %f, %f"),mouseX,mouseY);
	
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
	if (!Cast<ASplendorPlayerState>(this->PlayerState)->GetTurnStatus() || Cast<ASplendorPlayerState>(this->PlayerState)->GetFinishedStatus()) return;
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
		this->EnableInput(this);
		bIsInputEnabled = true;
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
void ASplendorPlayerController::BuyCard(FTokenStruct cardBonus,FTokenStruct cost, int prestige, bool bIsWithGold, ATokenStash* tokenStashRef)
{
	ASplendorPlayerState* playerState = Cast<ASplendorPlayerState>(this->PlayerState);
	if (!playerState) return;
	int oldPrestige = playerState->GetPlayerPrestige();
	playerState->SetPlayerPrestige(oldPrestige + prestige);

	FTokenStruct playerBonuses = playerState->GetPlayerBonuses();
	FTokenStruct playerBudget = playerState->GetPlayerTokens();
	FTokenStruct initialBudget = playerBudget;
	cost - playerBonuses;
	cost.NormalizeCost();
	playerBudget - cost;

	if(bIsWithGold)
	{
		playerBudget.DeductGold(playerBudget);
	}
	// Po odjeciu od startowego budzetu nowego budzetu otrzymujemy ilosc tokenow ktore gracz wydal
	initialBudget - playerBudget;
	// Update stasha o wartosci od gracza
	CallTokenStashUpdate( tokenStashRef,-initialBudget);
	
	playerState->SetPlayerTokens(playerBudget);
	FTokenStruct oldBonus = playerState->GetPlayerBonuses();
	FTokenStruct newBonus = oldBonus + cardBonus;
	playerState->SetPlayerBonus(newBonus);
	int playerPrestige = playerState->GetPlayerPrestige();
	playerState->SetPlayerPrestige(prestige + playerPrestige);
	
	// Jesli w tym momecie mielismy ture, to ja informujemy serwer ze chcemy ja zakonczyc
	if (Cast<ASplendorPlayerState>(this->PlayerState)->GetTurnStatus()) this->CallTurnEnd();
}
void ASplendorPlayerController::RestartPawn()
{
	playerPawnRef->RestartPos();
}
void  ASplendorPlayerController::ReserveCard(FCardStruct* reservedCard,ATokenStash * tokenStashRef)
{
	ASplendorPlayerState* playerState = Cast<ASplendorPlayerState>(this->PlayerState);
	if (playerState->GetTurnStatus()) this->CallTurnEnd();
	playerState->ReserveCard(*reservedCard, tokenStashRef);
	
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
void ASplendorPlayerController::CallRequestCardPop(ACardStack* cardStackToPop)
{
	if (Role == ROLE_Authority)
	{
		cardStackToPop->PopCardArray();
	}
	else
	{
		ServerRequestsCardPop(cardStackToPop);
	}
}
void ASplendorPlayerController::ServerRequestsCardPop_Implementation(ACardStack* cardStackToPop)
{
	CallRequestCardPop(cardStackToPop);
}
bool ASplendorPlayerController::ServerRequestsCardPop_Validate(ACardStack* cardStackToPop)
{
	return true;
}

void  ASplendorPlayerController::CallUpdateCard(ACard* cardToCall)
{
	if (Role == ROLE_Authority)
	{
		cardToCall->UpdateCard();
	}
	else
	{
		ServerUpdateCard(cardToCall);
	}
}
void ASplendorPlayerController::ServerUpdateCard_Implementation(ACard* cardToCall)
{
	CallUpdateCard(cardToCall);
}
bool ASplendorPlayerController::ServerUpdateCard_Validate(ACard* cardToCall)
{
	return true;
}
void ASplendorPlayerController::CallInitCard(ACard* cardToCall)
{
	if (Role == ROLE_Authority)
	{
		FCardStruct cardParams = cardToCall->GetCardParams();
		this->SetCardParamsOnClient(cardToCall,cardParams);
	}
	else
	{
		ServerInitCard(cardToCall);
	}
} 
void ASplendorPlayerController::ServerInitCard_Implementation(ACard* cardToCall)
{
	CallInitCard(cardToCall);
}
bool ASplendorPlayerController::ServerInitCard_Validate(ACard* cardToCall)
{
	return true;
}
void ASplendorPlayerController::SetCardParamsOnClient_Implementation(ACard* cardToCall, FCardStruct cardParams)
{
	cardToCall->ResetCardParams(cardParams);
}