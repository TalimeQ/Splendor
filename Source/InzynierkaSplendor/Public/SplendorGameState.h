

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerState.h"
#include "ChatHUD.h"
#include "SplendorGameState.generated.h"

UENUM(BlueprintType, Category = "GameState")
enum ECurrentGameState
{
	EPlaying,

	ELastTurn,
	EGameOver,
	EWon,
	EUnknown
};
class ASplendorPlayerState;

/**
 * 
 */
UCLASS()
class INZYNIERKASPLENDOR_API ASplendorGameState : public AGameStateBase
{
	GENERATED_BODY()
private:
	
		// used to easilyDetermineTurnOrder
		TArray<ASplendorPlayerState*> playerTurnOrder;
		ASplendorPlayerState* startingPlayer;
		virtual void BeginPlay() override;
		UPROPERTY(ReplicatedUsing = OnRep_CurrentState)
		TEnumAsByte<enum ECurrentGameState> CurrentState;
		void RandomizeTurnOrder();
		void InitializePlayerArray();
		int currentPlayer = 0;
		
public:
		ASplendorGameState();
		UPROPERTY(Replicated, BlueprintReadWrite, Category = "Game Variables")
			int pointsToWin = 15;
		void NextTurn();
		// Rep notifier 
		UFUNCTION()
		void OnRep_CurrentState();
		UFUNCTION(BlueprintCallable)
		void Initialize();
		UFUNCTION(reliable, server, WithValidation)
		void ServerInitialize();

		UFUNCTION(Server, Reliable, WithValidation) // for player to player rpc you need to first call the message on the server 
			virtual void UserChatRPC(const FSChatMsg& newmessage);
		// first rpc for the server 
		UFUNCTION(NetMulticast, Reliable, WithValidation)
			// then the server calls the function with a multicast that executes on all clients and the server 
			virtual void UserChat(const FSChatMsg& newmessage);
		// second rpc for all the clients 
};
