// Fill out your copyright notice in the Description page of Project Settings.

#include "ChatHUD.h"

#include "SMyChatWidget.h"
#include "Player/SplendorPlayerState.h"

AChatHUD::AChatHUD()
{

}

void AChatHUD::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (GEngine && GEngine->GameViewport) // make sure our screen is ready for the widget
	{
		SAssignNew(MyUIWidget, SMyChatWidget).OwnerHUD(this); // add the widget and assign it to the var
		GEngine->GameViewport->AddViewportWidgetContent(SNew(SWeakWidget).PossiblyNullContent(MyUIWidget.ToSharedRef()));
	}
}

void AChatHUD::DrawHUD()
{
	Super::DrawHUD();

	if (!MyPC)
	{
		MyPC = GetOwningPlayerController();
		AddMessageBP(2, TEXT(""), TEXT("Welcome. Press Enter to chat."), false); // random Welcome message shown to the local player. To be deleted. note type 2 is system message and username is blank
		return;
	}

	if (MyPC->WasInputKeyJustPressed(EKeys::Enter))
		if (MyUIWidget.IsValid() && MyUIWidget->ChatInput.IsValid())
			FSlateApplication::Get().SetKeyboardFocus(MyUIWidget->ChatInput); // When the user presses Enter he will focus his keypresses on the chat input bar
}

void AChatHUD::AddMessageBP(const int32 Type, const FString& Username, const FString& Text, const bool Replicate)
{
	if (!MyPC || !MyUIWidget.IsValid())
		return;

	FSChatMsg newmessage;
	newmessage.Init(Type, FText::FromString(Username), FText::FromString(Text)); // initialize our struct and prep the message
	if (newmessage.Type > 0)
		if (Replicate)
		{
			ASplendorPlayerState* MyPS = Cast<ASplendorPlayerState>(MyPC->PlayerState);
			if (MyPS)
				MyPS->UserChatRPC(newmessage); // Send the complete chat message to the PlayerState so it can be replicated then displayed
		}
		else
			MyUIWidget->AddMessage(newmessage); // Send a local message to this client only, no one else receives it
}