

#include "SplendorPlayerState.h"
#include "Public/GameplayObjects/TokenStruct.h"
#include "Public/SplendorPlayerController.h"
#include "UnrealNetwork.h"
#include "Public/GameplayObjects/CardStack.h"
#include "Public/GameplayObjects/TokenStash.h"
#include "Public/ChatHUD.h"
#include "Public/SMyChatWidget.h"


ASplendorPlayerState::ASplendorPlayerState()
{
	playerTokens = new FTokenStruct();
	playerBonuses = new FTokenStruct();
}
FTokenStruct ASplendorPlayerState::GetPlayerTokens()
{

	return *playerTokens;
}
/*
Sets the amount of player tokens to the one provided in function parameter. Yes that means do calculations out of this place :)
*/
void ASplendorPlayerState::SetPlayerTokens(FTokenStruct newTokenValue)
{
	if(ROLE_Authority){
	playerTokens->setParams(newTokenValue);
	UE_LOG(LogTemp, Warning, TEXT("NEW PLAYER TOKEN STATE D: %d , E: %d, S: %d, O: %d, R: %d "), playerTokens->diamondTokens, playerTokens->emeraldTokens,playerTokens->sapphireTokens, playerTokens->onyxTokens, playerTokens->rubyTokens)
	}
}
int ASplendorPlayerState::ReturnNumberOfCards()
{
	return reservedCards.Num();
}
void ASplendorPlayerState::ReserveCard(FCardStruct CardValues)
{
	if(Role == ROLE_Authority)
	{ 
	FCardStruct* tempCardPtr = new FCardStruct();
	tempCardPtr->cardBonus = CardValues.cardBonus;
	tempCardPtr->cardCost = CardValues.cardCost;
	tempCardPtr->prestige = CardValues.prestige;
	reservedCards.Add(tempCardPtr);
	
	}
}
void ASplendorPlayerState::BuyReservedCard(int cardIndex)
{
	//theoretical implementation soon :) after i get my game interface.....
}
void ASplendorPlayerState::SetPlayerPrestige(int newPrestige)
{
	if (Role == ROLE_Authority)
	{
		prestige = newPrestige;
	}
	else
	{
		ServerSetPlayerPrestige(newPrestige);
	}
}
int ASplendorPlayerState::GetPlayerPrestige()
{
	return prestige;
}
FTokenStruct ASplendorPlayerState::GetPlayerBonuses()
{
	return *playerBonuses;
}
FTokenStruct ASplendorPlayerState::GetPlayerBudget()
{
	FTokenStruct tempBonus = *playerBonuses;
	FTokenStruct tempTokens = *playerTokens;
	FTokenStruct Budget = tempBonus + tempTokens;
	UE_LOG(LogTemp, Warning, TEXT("PLayerstate gold: %d , %d"), Budget.goldTokens,playerBonuses->goldTokens);
	return Budget;
}
void ASplendorPlayerState::SetPlayerBonus(FTokenStruct newBonus)
{
	if (Role == ROLE_Authority)
	{
	playerBonuses->setParams(newBonus);
	}
	UE_LOG(LogTemp,Warning,TEXT("NEW PLAYER BONUSES D: %d , E: %d, S: %d, O: %d, R: %d "),playerBonuses->diamondTokens,playerBonuses->emeraldTokens, playerBonuses->sapphireTokens,playerBonuses->onyxTokens, playerBonuses->rubyTokens)
}
void  ASplendorPlayerState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ASplendorPlayerState,bIsTurn);
	DOREPLIFETIME(ASplendorPlayerState,prestige);
	DOREPLIFETIME(ASplendorPlayerState,bIsFinished);
}
void  ASplendorPlayerState::SetTurnStatus(bool bNewTurnStatus)
{
	if (Role == ROLE_Authority)
	{
		
		this->bIsTurn = bNewTurnStatus;
		UE_LOG(LogTemp, Warning, TEXT("Turn changed %s"),( bIsTurn ? TEXT("TRUE") : TEXT("FALSE")))
	}
}
bool ASplendorPlayerState::GetTurnStatus()
{
	return bIsTurn;
}

bool ASplendorPlayerState::UserChatRPC_Validate(const FSChatMsg& newmessage)
{
	return true;
}
void ASplendorPlayerState::UserChatRPC_Implementation(const FSChatMsg& newmessage)
{
	UserChat(newmessage);
}
bool ASplendorPlayerState::UserChat_Validate(const FSChatMsg& newmessage)
{
	return true;
}
void ASplendorPlayerState::UserChat_Implementation(const FSChatMsg& newmessage)
{
	APlayerController* MyCon;
	AChatHUD* MyHud;

	for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator) // find all controllers
	{
		MyCon = Cast<ASplendorPlayerController>(*Iterator);
		if (MyCon)
		{
			MyHud = Cast<AChatHUD>(MyCon->GetHUD());
			if (MyHud && MyHud->MyUIWidget.IsValid())
				MyHud->MyUIWidget->AddMessage(newmessage); // place the chat message on this player controller
		}
	}
}
void ASplendorPlayerState::ServerSetPlayerPrestige_Implementation(int newPrestige)
{
	this->SetPlayerPrestige(newPrestige);
}
bool ASplendorPlayerState::ServerSetPlayerPrestige_Validate(int newPrestige)
{
	return true;
}
void ASplendorPlayerState::SetFinished()
{
	bIsFinished = true;
}
bool ASplendorPlayerState::GetFinishedStatus()
{
	return bIsFinished;
}