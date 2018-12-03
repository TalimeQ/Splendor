// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"
#include "ChatHUD.generated.h"

USTRUCT()
struct FSChatMsg // Struct to hold the message data to be passed between classes
{
	GENERATED_BODY()

		UPROPERTY() // UProperty means this variable will be replicated
		int32 Type;

	UPROPERTY()
		FText Username;

	UPROPERTY()
		FText Text;

	FText Timestamp; // Dont replicate time because we can set it locally once we receive the struct

	double Created;

	void Init(int32 NewType, FText NewUsername, FText NewText) // Assign only the vars we wish to replicate
	{
		Type = NewType;
		Username = NewUsername;
		Text = NewText;
	}
	void SetTime(FText NewTimestamp, double NewCreated)
	{
		Timestamp = NewTimestamp;
		Created = NewCreated;
	}
	void Destroy()
	{
		Type = NULL;
		Username.GetEmpty();
		Text.GetEmpty();
		Timestamp.GetEmpty();
		Created = NULL;
	}
};

/**
 *
 */
UCLASS()
class INZYNIERKASPLENDOR_API AChatHUD : public AHUD
{
	GENERATED_BODY()

public:

	AChatHUD();

	TSharedPtr<class SMyChatWidget> MyUIWidget; // Reference to the main chat widget

	APlayerController* MyPC;

	UFUNCTION(BlueprintCallable, Category = "User")
		void AddMessageBP(const int32 Type, const FString& Username, const FString& Text, const bool Replicate); // A Blueprint function you can use to place messages in the chat box during runtime

protected:

	virtual void PostInitializeComponents() override; // All game elements are created, add our chat box

	virtual void DrawHUD() override; // The HUD is drawn on our screen
};