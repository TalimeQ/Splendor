

#include "ChatPlayerState.h"
#include "InzynierkaSplendor.h"
#include "ChatHUD.h"
#include "SMyChatWidget.h"

AChatPlayerState::AChatPlayerState() {

}

bool AChatPlayerState::UserChatRPC_Validate(const FSChatMsg& newmessage) {
	return true;
}

void AChatPlayerState::UserChatRPC_Implementation(const FSChatMsg& newmessage) {
	UserChat(newmessage);
}

bool AChatPlayerState::UserChat_Validate(const FSChatMsg& newmessage) {
	return true;
}

void AChatPlayerState::UserChat_Implementation(const FSChatMsg& newmessage) {
	APlayerController* MyCon;
	AChatHUD* MyHud;

	for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)  // find all controllers 
	{
		MyCon = Cast<APlayerController>(*Iterator);
		if (MyCon)
		{
			MyHud = Cast<AChatHUD>(MyCon->GetHUD());
			if (MyHud && MyHud->MyUIWidget.IsValid()) MyHud->MyUIWidget->AddMessage(newmessage); // place the chat message on this player controller 
		}
	}
}